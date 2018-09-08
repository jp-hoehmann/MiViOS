/*
 * malloc.c
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

static void* freebase = 0;
static void* freetop = 0;

static size_t PAGE_SIZE = 0;

/*
 * Allocate a memory block.
 *
 * Allocates a block of size bytes of memory, returning a pointer to the beginning of the block. The content of the
 * newly allocated block of memory is not initialized, remaining with indeterminate values.
 */
void* malloc(size_t size) {
    if (!freebase) {
        // First run of malloc(), let's get some memory.
        freebase = alloc_page(1);

        // Hack to determine the page size (can't just #define it, since it is potentially dependent on the
        // architecture).
        freetop = alloc_page(1);
        PAGE_SIZE = freetop - freebase;
        freetop += PAGE_SIZE;
    }

    void* result = freebase;
    freebase += size;
    if (freebase >= freetop) {
        freetop = alloc_page(((freebase - freetop) / PAGE_SIZE) + 1) + PAGE_SIZE;
    }
    return result;
}
