/*
 * strcmp.c
 *
 * Created by Jean-Pierre Höhmann on 26.08.18.
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
 * Compare two strings.
 *
 * This function starts comparing the first character of each string. If they are equal to each other, it continues
 * with the following pairs until the characters differ or until a terminating null-character is reached. This function
 * performs a binary comparison of the characters, without taking into account locale-specific rules.
 */
int strcmp(const char* astr, const char* bstr) {
    const unsigned char* a = (const unsigned char*) astr;
    const unsigned char* b = (const unsigned char*) bstr;
    for (size_t i = 0; a[i] && b[i]; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}
