/*
 * mmu.c
 *
 * Created by Jean-Pierre Höhmann on 18-08-29.
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
#include <kernel/kernel.h>

/*
 * Initialize the MMU.
 */
void kernel_mmu_initialize(struct mmu_info* info) {
    _pg_install(&_kernel_end);
    _pg_set(&_kernel_end);
}

/*
 * Finalize the MMU.
 */
void kernel_mmu_finalize(void) {
    ((void) 0);
}
