/*
 * Common.cpp
 *
 * Copyright 2017 Amazon.com, Inc. or its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Common.h"

#include <algorithm>
#include <climits>
#include <chrono>
#include <functional>
#include <random>
#include <vector>

namespace alexaClientSDK {
namespace acl {
namespace test {

std::string createRandomAlphabetString(int stringSize) {
    // First, let's efficiently generate random numbers of the appropriate size.
    std::vector<uint8_t> vec(stringSize);
    std::independent_bits_engine<std::default_random_engine, CHAR_BIT, uint8_t> engine;
    std::random_device rd;
    engine.seed(
        rd() + std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
                   .count());
    std::generate(begin(vec), end(vec), std::ref(engine));

    // Now perform a modulo, bounding them within [a,z].
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = static_cast<uint8_t>('a' + (vec[i] % 26));
    }

    /// Convert the data into a std::string.
    char* dataBegin = reinterpret_cast<char*>(&vec[0]);

    return std::string(dataBegin, stringSize);
}

int generateRandomNumber(int min, int max) {
    if (min > max) {
        std::swap(min, max);
    }

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

}  // namespace test
}  // namespace acl
}  // namespace alexaClientSDK
