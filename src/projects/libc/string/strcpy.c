/*
 * strcpy.c
 *
 * Created by Jean-Pierre Höhmann on 02.09.18.
 *
 * Copyright 2018 Jean-Pierre Höhmann (@NuvandaPV) <jean-pierre@höhmann.info>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>

/*
 * Copy a string.
 *
 * Copies the C string pointed by source into the array pointed by destination, including the terminating null
 * character (and stopping at that point). To avoid overflows, the size of the array pointed by destination shall be
 * long enough to contain the same C string as source (including the terminating null character), and should not
 * overlap in memory with source.
 */
char* strcpy(char* restrict dststr, const char* restrict srcstr) {
    unsigned char* dst = (unsigned char*) dststr;
    const unsigned char* src = (const unsigned char*) srcstr;
    for (size_t i = 0; dst[i] = src[i]; i++) {}
    return dststr;
}
