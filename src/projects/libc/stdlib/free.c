/*
 * free.c
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

/*
 * Deallocate a memory block.
 *
 * A block of memory previously allocated by a call to malloc, calloc or realloc is deallocated, making it available
 * again for further allocations.
 */
void free(void* ptr) {
    // TODO Implement a memory allocation scheme that can actually support this.
}
