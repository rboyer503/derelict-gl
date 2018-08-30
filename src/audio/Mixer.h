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

#ifndef DGL_MIXER_H
#define DGL_MIXER_H

#include "SoundRecording.h"
#include "RenderableAudio.h"


class Mixer : public RenderableAudio
{
public:
    static constexpr int32_t MAX_FRAMES = 512;

    Mixer() { mMixBuffer.reserve(MAX_FRAMES * NUM_CHANNELS); }

    void addTrack(const renderable_audio_ptr &track) { mTrackList.push_back(track); }
    void removeTrack(const renderable_audio_ptr &track) { mTrackList.remove(track); }
    void removeAllTracks() { mTrackList.clear(); }

    bool renderAudio(int16_t *audioData, int32_t numFrames);

private:
    std::vector<int16_t> mMixBuffer;
    renderable_audio_list mTrackList;
};


#endif //DGL_MIXER_H
