/*
 * Copyright 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Modified July 10, 2018 by Derelict Vessel Dev for "Fourth Realm".
 * Original from Oboe RhythmGame sample.
 */

#ifndef DGL_SOUNDRECORDING_H
#define DGL_SOUNDRECORDING_H

#include <cstdint>
#include <memory>
#include <vector>

#include <android/asset_manager.h>

#include "RenderableAudio.h"
#include "SoundMetadata.h"


class SoundRecording : public RenderableAudio
{
public:
    explicit SoundRecording(SoundMetadata *soundMetadata, const int16_t *sourceData,
                            int32_t numFrames)
            : mSoundMetadata(soundMetadata),
              mData(sourceData),
              mTotalFrames(numFrames) {}

    bool renderAudio(int16_t *targetData, int32_t numFrames);
    void resetPlayHead() { mReadFrameIndex = 0; }
    void setPlaying(bool isPlaying) {
        mIsPlaying = isPlaying;
        resetPlayHead();
    }
    bool isPlaying() const { return mIsPlaying; }
    void setLooping(bool isLooping) { mIsLooping = isLooping; }
    void pause() { mIsPaused = true; }
    void resume() { mIsPaused = false; }
    SoundMetadata *getSoundMetadata() { return mSoundMetadata; }

    static bool loadFromAssets(AAssetManager *assetManager, SoundMetadata *soundMetadata,
                               std::vector<std::shared_ptr<SoundRecording> > &soundVec);

private:
    SoundMetadata *mSoundMetadata = nullptr;
    int32_t mReadFrameIndex = 0;
    const int16_t *mData = nullptr;
    int32_t mTotalFrames = 0;
    bool mIsPlaying = false;
    bool mIsLooping = false;
    bool mIsPaused = false;
};

typedef std::shared_ptr<SoundRecording> sound_recording_ptr;
typedef std::vector<sound_recording_ptr> sound_recording_vec;


#endif //DGL_SOUNDRECORDING_H
