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
 * Modified July 2, 2018 by Derelict Vessel Dev for "Fourth Realm".
 * Original from Oboe RhythmGame sample.
 */

#ifndef DGL_UTILITYFUNCTIONS_H
#define DGL_UTILITYFUNCTIONS_H

#include <stdint.h>

constexpr int64_t kMillisecondsInSecond = 1000;
constexpr int64_t kNanosecondsInMillisecond = 1000000;


int64_t nowUptimeMillis();
float randomFloat(float a, float b);

constexpr int64_t convertFramesToMillis(const int64_t frames, const int sampleRate) {
    return (int64_t) (((double) frames / sampleRate) * kMillisecondsInSecond);
}


#endif //DGL_UTILITYFUNCTIONS_H
