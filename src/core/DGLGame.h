//
// Created by Rob on 7/26/2018.
//

#ifndef DGL_DGLGAME_H
#define DGL_DGLGAME_H

#include <memory>
#include <vector>

#include <android/asset_manager.h>
#include <oboe/Oboe.h>

#include "../audio/Mixer.h"
#include "../audio/SoundMetadata.h"
#include "../core/SceneManager.h"
#include "../data/GameData.h"
#include "../graphics/IGraphics.h"
#include "../input/Input.h"
#include "../objects/Square.h"
#include "../physics/PhysicsEngine.h"
#include "../programs/ColorShaderProgram.h"
#include "../text/TextManager.h"


class DGLGameState
{
    game_data_vec mGameDataVec;

public:
    virtual ~DGLGameState() {}

    void addGameData(const game_data_ptr &gameData) { mGameDataVec.push_back(gameData); }

    game_data_ptr &operator[](size_t index) { return mGameDataVec[index]; }
    const game_data_ptr &operator[](size_t index) const { return mGameDataVec[index]; }
};

typedef std::unique_ptr<DGLGameState> game_state_ptr;


class DGLGame : public oboe::AudioStreamCallback
{
    static constexpr int BUFFER_SIZE_IN_BURSTS = 2;
    static constexpr int SAMPLE_RATE_HZ = 48000;

protected:
    AAssetManager *mAssetManager{nullptr};

    std::unique_ptr<SceneManager> mSceneManager;
    std::unique_ptr<TextManager> mTextManager;

    // Audio-related members.
    std::unique_ptr<Mixer> mMixer;
    oboe::AudioStream *mAudioStream{nullptr};
    sound_recording_vec mSoundVec;
    SoundClassStats mSoundClassStats[SOUND_CLASS_MAX] = {{0}};

    // Game state.
    bool mPaused = false;
    uint32_t mNextScene = 0;
    bool mSwitchScene = false;
    game_state_ptr mGameState;

    // Graphics.
    int mScreenSizeX;
    int mScreenSizeY;
    std::vector<unsigned int> mTextureIds;
    const uint32_t mFontAssetIndex = 0;
    const SpriteFrameMapInfo mFontFrameMapInfo;
    DGLColor mGlobalTone = TRANSPARENT;
    square_ptr mGlobalQuad;
    std::unique_ptr<DrawList> mGlobalDrawList;
    std::unique_ptr<ColorShaderProgram> mColorShaderProgram;

    // Timing.
    int32_t mFrameDurMs = 10;
    int64_t mNextFrameMs = 0;
    bool mFlushTicks = true;

public:
    explicit DGLGame(AAssetManager *assetManager, uint32_t fontAssetIndex,
                     const SpriteFrameMapInfo &fontFrameMapInfo);
    virtual ~DGLGame();

    void onPause();
    void onResume();
    void onSurfaceCreated(std::vector<DGLRawBitmap> &bitmaps);
    void onSurfaceChanged(int widthInPixels, int heightInPixels);
    void onSurfaceDestroyed();
    void onTick();
    void onTouchInput(eInputEvent event, int x, int y);
    void onRotationInput(double azimuth, double pitch, double roll);

    // Inherited from oboe::AudioStreamCallback
    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    DGLGameState &getGameState() { return *mGameState; }
    int getScreenSizeX() const { return mScreenSizeX; }
    int getScreenSizeY() const { return mScreenSizeY; }
    const std::vector<unsigned int> &getTextureIds() const { return mTextureIds; }

    void triggerSceneSwitch(uint32_t sceneIndex) {
        mSwitchScene = true;
        mNextScene = sceneIndex;
    }
    void flushTicks() {
        mFlushTicks = true;
    }

    uint32_t getSoundClassOffset(eSoundClass soundClass) const;
    uint32_t getNumSounds(eSoundClass soundClass = SOUND_CLASS_ANY) const;
    uint32_t getNumSoundsPlaying(eSoundClass soundClass = SOUND_CLASS_ANY) const;
    uint32_t getNumSoundsQueued(eSoundClass soundClass = SOUND_CLASS_ANY) const;
    bool scheduleSound(int soundIndex, uint32_t ticksToStart);
    void playSound(int soundIndex, bool looping);
    void stopSound(int soundIndex);
    float getSoundVolume(int soundIndex) const {
        return mSoundVec[soundIndex]->getSoundMetadata()->mVolume;
    }
    void setSoundVolume(int soundIndex, float volume) {
        mSoundVec[soundIndex]->getSoundMetadata()->mVolume = volume;
    }

    void loadSounds(sound_metadata_vec &soundMetadataVec);
    void stopAllSounds();
    void unloadAllSounds();

    std::unique_ptr<TextObject>
    buildTextObject(std::string text, uint32_t maxLength, eTextJustifyMode justifyMode, Vector3 pos,
                    Vector2 size, DGLColor color, bool active);
    void loadTextObjects(const text_object_vec &textObjectVec);
    void unloadTextObjects();

    void updateGlobalTone(DGLColor tone) {
        mGlobalTone = tone;
        mGlobalQuad->setColor(tone);
    }

private:
    void initAudioStream();
    void loadTextures(std::vector<DGLRawBitmap> &bitmaps);
    void queueSounds();
    void loadDrawList();
    void buildShaders();

};


#endif //DGL_DGLGAME_H
