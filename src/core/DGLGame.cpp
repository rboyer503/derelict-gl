//
// Created by Rob on 7/26/2018.
//

#include "DGLGame.h"

#include <algorithm>
#include <ctime>
#include <random>

#include "../graphics/OpenGLGraphics.h"
#include "../objects/Square.h"
#include "../utils/UtilityFunctions.h"

using namespace oboe;


DGLGame::DGLGame(AAssetManager *assetManager, uint32_t fontAssetIndex,
                 const SpriteFrameMapInfo &fontFrameMapInfo)
        : mAssetManager(assetManager),
          mSceneManager(new SceneManager()),
          mTextManager(new TextManager(&mFontFrameMapInfo)),
          mMixer(new Mixer()),
          mGameState(new DGLGameState()),
          mFontAssetIndex(fontAssetIndex),
          mFontFrameMapInfo(fontFrameMapInfo),
          mGlobalQuad(
                  std::make_shared<SquareObject>(Vector3(-1.0f, -1.0f, 0.0f), Vector2(2.0f, 2.0f),
                                                 mGlobalTone)) {
    srand(static_cast<unsigned int>(time(0)));

    initAudioStream();
}

DGLGame::~DGLGame() {
    if (mAudioStream)
    {
        mAudioStream->close();
        delete mAudioStream;
    }
}

void DGLGame::onPause(bool force) {
    if (force)
        mForcePaused = true;
    mPaused = true;

    for (auto &sound : mSoundVec)
        sound->pause();

    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->pause();
}

void DGLGame::onResume(bool force) {
    if (mForcePaused && !force)
        return;
    mPaused = mForcePaused = false;

    for (auto &sound : mSoundVec)
        sound->resume();

    mNextFrameMs = nowUptimeMillis();

    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->resume();
}

void DGLGame::onBackPressed() {
    if (mBackPressed)
        return;
    mBackPressed = true;

    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->backPressed();
}

void DGLGame::onSurfaceCreated(std::vector<DGLRawBitmap> &bitmaps) {
    GraphicsIntf->SetClearColor(BLACK);
    GraphicsIntf->SetDepthTest(true);

    loadTextures(bitmaps);
    (*mTextManager).initialize();

    loadDrawList();
    buildShaders();

    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->surfaceCreated();

    mNextFrameMs = nowUptimeMillis();
}

void DGLGame::onSurfaceChanged(int widthInPixels, int heightInPixels) {
    mScreenSizeX = widthInPixels;
    mScreenSizeY = heightInPixels;

    GraphicsIntf->SetViewport(widthInPixels, heightInPixels);

    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->surfaceChanged(widthInPixels, heightInPixels);
}

void DGLGame::onSurfaceDestroyed() {
    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->surfaceDestroyed();

    (*mTextManager).uninitialize();
}

bool DGLGame::onTick() {
    if (mTerminate)
        return true;

    if (mSwitchScene)
    {
        mSwitchScene = false;
        (*mSceneManager).setActiveScene(mNextScene);
        return false;
    }

    static int64_t tickCalls = 0;
    static int64_t totalTicks = 0;

    // Do timing.
    int32_t deltaMs = static_cast<int32_t>(nowUptimeMillis() - mNextFrameMs);
    if (deltaMs < 0)
        return false;

    int32_t ticks = (deltaMs / mFrameDurMs) + 1;
    mNextFrameMs += mFrameDurMs * ticks;

    tickCalls++;
    totalTicks += ticks;
    if (totalTicks >= 100)
    {
        LOGD("Avg. ticks = %f", static_cast<float>(totalTicks) / tickCalls);
        tickCalls = totalTicks = 0;
    }

    if (mFlushTicks)
    {
        mFlushTicks = false;
        return false;
    }

    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->preTicks();

    while (ticks--)
    {
        // Perform game logic that is required every tick.
        if (scene)
        {
            scene->tick();
            if (!mPaused)
                scene->applyPhysics();
        }

        if (!mPaused)
            queueSounds();
    }

    GraphicsIntf->ClearScreen();
    if (scene)
    {
        scene->postTicks();
        scene->render();
        (*mTextManager).render();

        GraphicsIntf->SetDepthTest(false);
        GraphicsIntf->SetBlend(BLEND_MODE_ALPHA);
        (*mGlobalDrawList).updateBuffers();
        if (!(*mGlobalDrawList).isEmpty())
        {
            (*mColorShaderProgram).useProgram();
            (*mGlobalDrawList).bindData(*mColorShaderProgram);
            (*mGlobalDrawList).draw();
        }
        GraphicsIntf->SetBlend(BLEND_MODE_NONE);
        GraphicsIntf->SetDepthTest(true);
    }

    return false;
}

void DGLGame::onTouchInput(eInputEvent event, int x, int y) {
    Vector2 pos(static_cast<float>(x - (mScreenSizeX / 2)) / (mScreenSizeX / 2),
                static_cast<float>(y - (mScreenSizeY / 2)) / (mScreenSizeY / 2));
    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
    {
        if (!scene->applyTouchInput(event, pos))
            scene->touchInput(event, pos);
    }
}

void DGLGame::onRotationInput(double azimuth, double pitch, double roll) {
    scene_ptr scene = (*mSceneManager).getActiveScene();
    if (scene)
        scene->rotationInput(azimuth, pitch, roll);
}

DataCallbackResult
DGLGame::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    int numBatches = numFrames / Mixer::MAX_FRAMES;
    int excessFrames = numFrames % Mixer::MAX_FRAMES;
    int16_t *audioDataPtr = static_cast<int16_t *>(audioData);

    for (int i = 0; i < numBatches; ++i)
    {
        (*mMixer).renderAudio(audioDataPtr, Mixer::MAX_FRAMES);
        audioDataPtr += Mixer::MAX_FRAMES * RenderableAudio::NUM_CHANNELS;
    }

    (*mMixer).renderAudio(audioDataPtr, excessFrames);

    return DataCallbackResult::Continue;
}

bool DGLGame::scheduleSound(int soundIndex, uint32_t ticksToStart) {
    if (!mSoundVec[soundIndex]->isPlaying())
    {
        mSoundVec[soundIndex]->getSoundMetadata()->mTicksToStart = ticksToStart;
        return true;
    }

    return false;
}

void DGLGame::playSound(int soundIndex, bool looping) {
    mSoundVec[soundIndex]->setPlaying(true);
    mSoundVec[soundIndex]->setLooping(looping);
}

void DGLGame::stopSound(int soundIndex) {
    mSoundVec[soundIndex]->setPlaying(false);
}

void DGLGame::loadSounds(sound_metadata_vec &soundMetadataVec) {
    eSoundClass currSoundClass = SOUND_CLASS_ANY;

    // Load the raw PCM data files into memory.
    for (SoundMetadata &sm : soundMetadataVec)
    {
        if (SoundRecording::loadFromAssets(mAssetManager, &sm, mSoundVec))
        {
            (*mMixer).addTrack(mSoundVec.back());

            // Track the offset of the first sound of each sound class.
            if (currSoundClass != sm.mSoundClass)
            {
                currSoundClass = sm.mSoundClass;
                mSoundClassStats[sm.mSoundClass].mOffset = mSoundClassStats[SOUND_CLASS_ANY].mCount;
            }

            // Track count of each sound class and total of all sound classes.
            mSoundClassStats[sm.mSoundClass].mCount++;
            mSoundClassStats[SOUND_CLASS_ANY].mCount++;
        }
        else
        {
            LOGE("Failed to load sound asset: %s", sm.mAssetName);
        }
    }
}

void DGLGame::stopAllSounds() {
    for (auto &sound : mSoundVec)
    {
        SoundMetadata *sm = sound->getSoundMetadata();
        sm->mTicksToStart = 0;
        sound->setPlaying(false);
    }
}

void DGLGame::unloadAllSounds() {
    stopAllSounds();
    (*mMixer).removeAllTracks();
    mSoundVec.clear();
    for (int i = 0; i < SOUND_CLASS_MAX; ++i)
        mSoundClassStats[i] = {0};
}

std::unique_ptr<TextObject>
DGLGame::buildTextObject(std::string text, uint32_t maxLength, eTextJustifyMode justifyMode,
                         Vector3 pos, Vector2 size, DGLColor color, bool active) {
    return (*mTextManager).buildTextObject(text, maxLength, justifyMode, pos, size, color, active);
}

void DGLGame::loadTextObjects(const text_object_vec &textObjectVec) {
    for (auto &text : textObjectVec)
        (*mTextManager).addTextObject(text);
}

void DGLGame::unloadTextObjects() {
    (*mTextManager).removeAllTextObjects();
}

uint32_t DGLGame::getSoundClassOffset(eSoundClass soundClass) const {
    return mSoundClassStats[soundClass].mOffset;
}

uint32_t DGLGame::getNumSounds(eSoundClass soundClass /* = SOUND_CLASS_ANY */) const {
    return mSoundClassStats[soundClass].mCount;
}

uint32_t DGLGame::getNumSoundsPlaying(eSoundClass soundClass /* = SOUND_CLASS_ANY */) const {
    uint32_t count = 0;
    for (const sound_recording_ptr &sr : mSoundVec)
    {
        if (sr->isPlaying() &&
            ((soundClass == SOUND_CLASS_ANY) ||
             (soundClass == sr->getSoundMetadata()->mSoundClass)))
            ++count;
    }
    return count;
}

uint32_t DGLGame::getNumSoundsQueued(eSoundClass soundClass /* = SOUND_CLASS_ANY */) const {
    uint32_t count = 0;
    for (const sound_recording_ptr &sr : mSoundVec)
    {
        const SoundMetadata *sm = sr->getSoundMetadata();
        if ((sm->mTicksToStart > 0) &&
            ((soundClass == SOUND_CLASS_ANY) || (soundClass == sm->mSoundClass)))
            ++count;
    }
    return count;
}

void DGLGame::initAudioStream() {
    // Create a builder to build the audio stream.
    AudioStreamBuilder builder;
    builder.setFormat(AudioFormat::I16);
    builder.setChannelCount(RenderableAudio::NUM_CHANNELS);
    builder.setSampleRate(SAMPLE_RATE_HZ);
    builder.setCallback(this);
    builder.setPerformanceMode(PerformanceMode::PowerSaving);
    builder.setSharingMode(SharingMode::Exclusive);

    Result result = builder.openStream(&mAudioStream);
    if (result != Result::OK)
    {
        LOGE("Failed to open stream. Error: %s", convertToText(result));
    }

    // Reduce stream latency by setting the buffer size to a multiple of the burst size.
    auto setBufferSizeResult = mAudioStream->setBufferSizeInFrames(
            mAudioStream->getFramesPerBurst() * BUFFER_SIZE_IN_BURSTS);
    if (setBufferSizeResult != Result::OK)
    {
        LOGW("Failed to set buffer size. Error: %s", convertToText(setBufferSizeResult.error()));
    }

    result = mAudioStream->requestStart();
    if (result != Result::OK)
    {
        LOGE("Failed to start stream. Error: %s", convertToText(result));
    }
}

void DGLGame::loadTextures(std::vector<DGLRawBitmap> &bitmaps) {
    for (DGLRawBitmap &bitmap : bitmaps)
        mTextureIds.push_back(GraphicsIntf->LoadTexture(bitmap));

    (*mTextManager).setFontTextureId(mTextureIds[mFontAssetIndex]);
}

void DGLGame::queueSounds() {
    for (sound_recording_ptr &sr : mSoundVec)
    {
        SoundMetadata *sm = sr->getSoundMetadata();
        if (sm->mTicksToStart > 0)
        {
            if (--(sm->mTicksToStart) == 0)
            {
                sr->setPlaying(true);
            }
        }
    }
}

void DGLGame::loadDrawList() {
    mGlobalDrawList.reset(new DrawList({ATTR_POSITION, ATTR_COLOR}, true));
    (*mGlobalDrawList).addGameObject(mGlobalQuad);
    (*mGlobalDrawList).buildBuffers();
}

void DGLGame::buildShaders() {
    mColorShaderProgram.reset(new ColorShaderProgram());
}
