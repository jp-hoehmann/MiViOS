/*
 * initialize-standard-library.c
 *
 * Created by Jean-Pierre Höhmann on 2018-09-13.
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
#include <string.h>

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

void* MAGIC;

/*
 * Setup stdlib.
 */
void lib_setup(void) {
    malloc_setup();
}

/*
 * Setup stdio.
 */
void io_setup(void) {
    // Stub
}

/*
 * This is magic.
 */
void magic(void) {
    MAGIC = malloc(16);
    memcpy(MAGIC, &_MAGIC, 16);
}

/*
 * Initialize the libk.
 */
void initialize_kernel_library(size_t argc, char* argv[]) {
    kernel_tty_initialize();
    kernel_cpu_initialize();
    kernel_mmu_initialize();
    kernel_pfa_initialize();
    kernel_mm_initialize();
    kernel_ma_initialize();
    kernel_initialize(argc, argv);
}

/*
 * Initialize the libc.
 */
void initialize_user_library(size_t argc, char* argv[], size_t envc, char* envp[]) {
    // Stub
}

/*
 * Do common initializations.
 */
void setup(void) {
    lib_setup();
    io_setup();
    magic();
}

/*
 * Initialize the library.
 */
void initialize_standard_library(size_t argc, char* argv[], size_t envc, char* envp[]) {
#ifdef __is_libk
    initialize_kernel_library(argc, argv);
#else // __is_libk
    initialize_user_library(argc, argv, envc, envp);
#endif // __is_libk
    setup();
}
