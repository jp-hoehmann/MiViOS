/*
 * finalize-kernel-library.c
 *
 * Created by Jean-Pierre Höhmann on 2018-09-16.
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

#include "finalize-kernel-library.h"

#include <kernel/cpu.h>
#include <kernel/kernel.h>
#include <kernel/ma.h>
#include <kernel/mm.h>
#include <kernel/mmu.h>
#include <kernel/pfa.h>
#include <kernel/tty.h>

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
