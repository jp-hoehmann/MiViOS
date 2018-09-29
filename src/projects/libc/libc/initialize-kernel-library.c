/*
 * initialize-kernel-library.c
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

#include "initialize-kernel-library.h"

/*
 * Initialize the libk.
 */
void initialize_kernel_library(struct libk_info* info) {
     kernel_tty_initialize(info->tty);
     kernel_cpu_initialize(info->cpu);
     kernel_mmu_initialize(info->mmu);
     kernel_pfa_initialize(info->pfa);
     kernel_mm_initialize(info->mm);
     kernel_ma_initialize(info->ma);
     kernel_init_initialize(info->init);
     kernel_initialize(info->kernel);
}
