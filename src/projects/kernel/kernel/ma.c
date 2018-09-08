/*
 * ma.c
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

#include <kernel/ma.h>
#include <kernel/mm.h>
#include <kernel/kernel.h>
#include <kernel/mmu.h>

#include <stdlib.h>
#include <stddef.h>

static void* kfbase;
static void* cfbase;
static void* dfbase;
static void* efbase;
static void* ffbase;
static void* gfbase;
static void* sfbase;

static void* kftop;
static void* cftop;
static void* dftop;
static void* eftop;
static void* fftop;
static void* gftop;
static void* sftop;

__attribute__((constructor))
void init(void) {
    kfbase = &_kernel_end;
    cfbase = _c_space_start;
    dfbase = _d_space_start;
    efbase = _e_space_start;
    ffbase = _f_space_start;
    gfbase = _g_space_start;
    sfbase = _s_space_start;

    kftop = _kernel_space_end;
    cftop = _c_space_end;
    dftop = _d_space_end;
    eftop = _e_space_end;
    fftop = _f_space_end;
    gftop = _g_space_end;
    sftop = _s_space_end;
}

void* _alloc_page(size_t pages, void** fbase, void** ftop, void* palloc(uint32_t)) {
    void* d = *fbase;
    for (size_t i = 0; i < pages; i++) {
        palloc(*fbase);
        *fbase += _PAGE_SIZE;
        if (*fbase >= *ftop) {
            abort();
        }
    }
    return d;
}

void* alloc_kpage(size_t pages) {
    return _alloc_page(pages, &kfbase, &kftop, kpalloc);
}
