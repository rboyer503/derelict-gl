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

#include "Mixer.h"

#include <algorithm>
#include <functional>


bool Mixer::renderAudio(int16_t *audioData, int32_t numFrames) {
    int32_t audioDataSize = numFrames * NUM_CHANNELS;
    std::fill(audioData, audioData + audioDataSize, 0);

    for (auto &track : mTrackList)
    {
        if (track->renderAudio(mMixBuffer.data(), numFrames))
        {
            std::transform(audioData, audioData + audioDataSize, mMixBuffer.begin(), audioData,
                           std::plus<int16_t>());
        }
    }

    return true;
}
