/*
 * finalize.c
 *
 * Created by Jean-Pierre Höhmann on 2018-09-14.
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

#include <stddef.h>
#include <stdlib.h>

#include "finalize.h"
#include "initialize.h"
#include "stdlib/malloc.h"

#ifdef __is_libk
#include <kernel/cpu.h>
#include <kernel/kernel.h>
#include <kernel/ma.h>
#include <kernel/mm.h>
#include <kernel/mmu.h>
#include <kernel/pfa.h>
#include <kernel/tty.h>
#else // __is_libk
// Stub
#endif // __is_libk

/*
 * Tear down stdlib.
 */
void lib_teardown(void) {
    malloc_teardown();
}

/*
 * Tear down stdio.
 */
void io_teardown(void) {
    // Stub
}

/*
 * No more magic.
 */
void unmagic() {
    free(MAGIC);
}

/*
 * Finalize the libk.
 */
void finalize_kernel_library(int status) {
    kernel_finalize(status);
    kernel_ma_finalize();
    kernel_mm_finalize();
    kernel_pfa_finalize();
    kernel_mmu_finalize();
    kernel_cpu_finalize();
    kernel_tty_finalize();
}

/*
 * Finalize the libc.
 */
void finalize_user_library(int status) {
    // Stub
}

/*
 * Do common finalization.
 */
void teardown(void) {
    unmagic();
    io_teardown();
    lib_teardown();
}

/*
 * Finalize the library.
 */
void finalize_standard_library(int status) {
    teardown();
#ifdef __is_libk
    finalize_kernel_library(status);
#else // __is_libk
    finalize_user_library(status);
#endif // __is_libk
}
