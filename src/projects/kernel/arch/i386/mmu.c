/*
 * mmu.c
 *
 * Created by Jean-Pierre Höhmann on 29.08.18.
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

#include <kernel/mmu.h>

#include "boot.h"
#include "pd.h"

static uint32_t memory_used = 0;

/*
 * Set up the MMU.
 */
void memory_initialize(void) {
    _pd_set(&_kernel_end);
    _pg_set();
    memory_used = &_kernel_end + _PAGE_DIRECTORY_SIZE;
}

/*
 * Allocate a page frame.
 *
 * This will allocate a given physical page to a given virtual page using given flags, returning a pointer to the
 * newly mapped memory. The physical page is specified as a 32-bit unsigned int, that would point to the page, were it
 * identity mapped. The virtual page is specified as a 32-bit unsigned int, that would point to the new page, were it
 * already mapped in the desired way.
 */
void* _pfalloc(uint32_t flags, uint32_t virt, uint32_t phys) {
    *(uint32_t*) (_PAGE_DIRECTORY + (virt >> 10)) = phys | flags;
    return (void*) virt;
}

/*
 * Allocate a page frame.
 *
 * This will allocate a given virtual page using given flags, returning a pointer to the newly mapped memory. The
 * virtual page is specified as a 32-bit unsigned int, that would point to the new page, were it already mapped as
 * desired.
 */
void* pfalloc(uint32_t flags, uint32_t virt) {
    void* result = _pfalloc(flags, virt, memory_used);
    memory_used += _PAGE_SIZE;
    return result;
}

