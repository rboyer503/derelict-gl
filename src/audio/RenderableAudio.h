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

#ifndef DGL_RENDERABLEAUDIO_H
#define DGL_RENDERABLEAUDIO_H

#include <cstdint>
#include <memory>
#include <list>


class RenderableAudio
{
public:
    static constexpr int32_t NUM_CHANNELS = 2;

    virtual ~RenderableAudio() = default;

    virtual bool renderAudio(int16_t *audioData, int32_t numFrames) = 0;
};

typedef std::shared_ptr<RenderableAudio> renderable_audio_ptr;
typedef std::list<renderable_audio_ptr> renderable_audio_list;


#endif //DGL_RENDERABLEAUDIO_H
