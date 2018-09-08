/*
 * calloc.c
 *
 * Created by Jean-Pierre Höhmann on 08.09.18.
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

#include <stdlib.h>
#include <string.h>

/*
 * Allocate and zero-initialize an array.
 *
 * Allocates a block of memory for an array of num elements, each of them size bytes long, and initializes all its
 * bits to zero.
 */
void* calloc(size_t num, size_t size) {
    size_t amount = num * size;
    void* result = malloc(amount);
    memset(result, NULL, amount);
    return result;
}
