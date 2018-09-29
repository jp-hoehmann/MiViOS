/*
 * mm.c
 *
 * Created by Jean-Pierre Höhmann on 18-09-02.
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

#include <kernel/mm.h>
#include <kernel/pfa.h>
#include <kernel/mmu.h>

/*
 * Initialize the memory manager.
 */
void kernel_mm_initialize(struct mm_info* info) {
    ((void) 0);
}

/*
 * Finalize the memory manager.
 */
void kernel_mm_finalize(void) {
    ((void) 0);
}

/*
 * Allocate a kernel page.
 *
 * This will allocate a kernel page at the given virtual address, returning a pointer to the page.
 */
void* kpalloc(uint32_t addr) {
    return pfalloc(_KERNEL_DATA_PAGE, addr);
}

/*
 * Allocate a user code page.
 *
 * This will allocate a user code page at the given virtual address, returning a pointer to the page.
 */
void* cpalloc(uint32_t addr) {
    return pfalloc(_USER_CODE_PAGE, addr);
}

/*
 * Allocate a user data page.
 *
 * This will allocate a user data page at the given virtual address, returning a pointer to the page.
 */
void* dpalloc(uint32_t addr) {
    return pfalloc(_USER_DATA_PAGE, addr);
}

/*
 * Free a kernel page.
 *
 * This will free a kernel page, once implemented.
 */
int kpfree(uint32_t addr) {
    // FIXME Unimplemented
    return pffree(addr);
}

/*
 * Free a user code page.
 *
 * This will free a user code page, once implemented.
 */
int cpfree(uint32_t addr) {
    // FIXME Unimplemented
    return pffree(addr);
}

/*
 * Free a user data page.
 *
 * This will free a user data page, once implemented.
 */
int dpfree(uint32_t addr) {
    // FIXME Unimplemented
    return pffree(addr);
}
