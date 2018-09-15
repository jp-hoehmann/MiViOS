/*
 * pfa.c
 *
 * Created by Jean-Pierre Höhmann on 18-09-08.
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

#include "pd.h"

#include <kernel/pfa.h>
#include <kernel/mmu.h>
#include <kernel/kernel.h>

static uint32_t watermark;

/*
 * Initialize the page frame allocator.
 */
void kernel_pfa_initialize(void) {
    watermark = &_kernel_end + _PAGE_DIR_SIZE;
}

/*
 * Finalize the page frame allocator.
 */
void kernel_pfa_finalize(void) {
    // Stub
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
    *(uint32_t*) (_page_dir_start + (virt >> 10)) = phys | flags;
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
    void* result = _pfalloc(flags, virt, watermark);
    watermark += _PAGE_SIZE;
    return result;
}

/*
 * Free a page frame.
 *
 * This will free a given page frame, once implemented.
 */
int _pffree(uint32_t virt) {
    // Meh.
    return 0;
}

/*
 * Free a page frame.
 *
 * This will free a given page frame, once implemented.
 */
int pffree(uint32_t virt) {
    // FIXME Unimplemented.
    return _pffree(virt);
}
