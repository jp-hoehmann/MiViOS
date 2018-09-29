/*
 * ma.c
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

#include <kernel/ma.h>
#include <kernel/mm.h>
#include <kernel/kernel.h>
#include <kernel/mmu.h>

#include <stdlib.h>
#include <stddef.h>

static void* kfbase;
static void* bfbase;
static void* efbase;
static void* ffbase;
static void* gfbase;
static void* sfbase;

static void* kftop;
static void* bftop;
static void* eftop;
static void* fftop;
static void* gftop;
static void* sftop;

/*
 * Initialize the memory allocator.
 */
void kernel_ma_initialize(struct ma_info* info) {
    kfbase = &_kernel_end;
    bfbase = _b_space_start;
    efbase = _e_space_start;
    ffbase = _f_space_start;
    gfbase = _g_space_start;
    sfbase = _s_space_start;

    kftop = _kernel_space_end;
    bftop = _b_space_end;
    eftop = _e_space_end;
    fftop = _f_space_end;
    gftop = _g_space_end;
    sftop = _s_space_end;
}

/*
 * Finalize the memory allocator.
 */
void kernel_ma_finalize(void) {
    ((void) 0);
}

void* _alloc_page(size_t pages, void** fbase, void** ftop, void* palloc(uint32_t)) {
    void* result = *fbase;
    for (size_t i = 0; i < pages; i++) {
        palloc(*fbase);
        *fbase += _PAGE_SIZE;
        if (*fbase >= *ftop) {
            abort();
        }
    }
    return result;
}

/*
 * Allocate a given number of kernel data pages.
 *
 * This will allocate pages consecutive kernel data pages, returning a pointer to the start of the newly mapped memory.
 */
void* alloc_kpage(size_t pages) {
    return _alloc_page(pages, &kfbase, &kftop, kpalloc);
}

/*
 * Allocate a given number of user binary pages.
 *
 * This will allocate pages consecutive user binary pages, returning a pointer to the start of the newly mapped memory.
 */
void* alloc_bpage(size_t pages) {
    // Since there is no execute prevention, this can just use data pages.
    return alloc_dpage(pages);
}

/*
 * Allocate a given number of user code pages.
 *
 * This will allocate pages consecutive user code pages, returning a pointer to the start of the newly mapped memory.
 */
void* alloc_cpage(size_t pages) {
    // User code space and user data space have been combined into user binary space.
    return _alloc_page(pages, &bfbase, &bftop, cpalloc);
}

/*
 * Allocate a given number of user data pages.
 *
 * This will allocate pages consecutive user data pages, returning a pointer to the start of the newly mapped memory.
 */
void* alloc_dpage(size_t pages) {
    // User code space and user data space have been combined into user binary space.
    return _alloc_page(pages, &bfbase, &bftop, dpalloc);
}

/*
 * Allocate a given number of user extra data pages.
 *
 * This will allocate pages consecutive user extra data pages, returning a pointer to the start of the newly mapped
 * memory.
 */
void* alloc_epage(size_t pages) {
    return _alloc_page(pages, &efbase, &eftop, dpalloc);
}

/*
 * Allocate a given number of user file data pages.
 *
 * This will allocate pages consecutive user file data pages, returning a pointer to the start of the newly mapped
 * memory.
 */
void* alloc_fpage(size_t pages) {
    return _alloc_page(pages, &ffbase, &fftop, dpalloc);
}

/*
 * Allocate a given number of user generic data pages.
 *
 * This will allocate pages consecutive user generic data pages, returning a pointer to the start of the newly mapped
 * memory.
 */
void* alloc_gpage(size_t pages) {
    return _alloc_page(pages, &gfbase, &gftop, dpalloc);
}

/*
 * Allocate a given number of user stack pages.
 *
 * This will allocate pages consecutive user stack pages, returning a pointer to the start of the newly mapped memory.
 */
void* alloc_spage(size_t pages) {
    return _alloc_page(pages, &sfbase, &sftop, dpalloc);
}

/*
 * Free a given number of kernel data pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive kernel data pages starting at start.
 */
void free_kpage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}

/*
 * Free a given number of user binary pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive user binary pages starting at start.
 */
void free_bpage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}

/*
 * Free a given number of user code pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive user code pages starting at start.
 */
void free_cpage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}

/*
 * Free a given number of user data pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive user data pages starting at start.
 */
void free_dpage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}

/*
 * Free a given number of user extra data pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive user extra data pages starting at start.
 */
void free_epage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}

/*
 * Free a given number of user file data pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive user file data pages starting at start.
 */
void free_fpage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}

/*
 * Free a given number of user generic data pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive user generic data pages starting at start.
 */
void free_gpage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}

/*
 * Free a given number of user stack pages starting from a given address.
 *
 * Once properly implemented, this will free pages consecutive user stack pages starting at start.
 */
void free_spage(void* start, size_t pages) {
    // TODO Implement
    ((void) 0);
}
