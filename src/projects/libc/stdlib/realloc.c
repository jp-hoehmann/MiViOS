/*
 * realloc.c
 *
 * Created by Jean-Pierre Höhmann on 09.09.18.
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
 * Reallocate a memory block.
 *
 * Changes the size of the memory block pointed to by ptr. The function may move the memory block to a new location
 * (whose address is returned by the function). The content of the memory block is preserved up to the lesser of the
 * new and old sizes, even if the block is moved to a new location. If the new size is larger, the value of the newly
 * allocated portion is indeterminate. In case that ptr is a null pointer, the function behaves like malloc, assigning
 * a new block of size bytes and returning a pointer to its beginning.
 */
void* realloc(void* ptr, size_t size) {
    // TODO Implement a memory allocation scheme that allows reusing the old memory where possible.
    void* result = malloc(size);

    // Not sure if this can go horribly wrong somehow, actually.
    memcpy(result, ptr, size);

    // FIXME Unimplemented
    free(ptr);

    // Here, sorry.
    return result;
}
