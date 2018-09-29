/*
 * libc.c
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

#include <stdlib.h>
#include <kernel/file.h>
#include <kernel/init.h>

#include "libc.h"
#include "setup.h"
#include "teardown.h"
#include "initialize-kernel-library.h"
#include "initialize-user-library.h"

#ifdef __is_kernel
#include "initialize-kernel-library.h"
#include "finalize-kernel-library.h"
#endif // __is_kernel

#ifdef __is_user
#include "initialize-user-library.h"
#include "finalize-user-library.h"
#endif // __is_user

/*
 * Internal initialization routine.
 */
void _initialize_standard_library(struct libc_info* libc_info, struct libk_info* libk_info) {
#ifdef __is_kernel
    initialize_kernel_library(libk_info);
#endif // __is_kernel
#ifdef __is_user
    initialize_user_library(libc_info);
#endif // __is_user
}

/*
 * Internal finalization routine.
 */
void _finalize_standard_library() {
#ifdef __is_kernel
    finalize_kernel_library();
#endif // __is_kernel
#ifdef __is_user
    finalize_user_library();
#endif // __is_user
}

/*
 * Initialize the library.
 *
 * This will initialize the library. Among its tasks is the parsing of arguments and environment. For this purpose it
 * gets passed four pointers, through which it returns the parsed data, so it can be passed to main(), or
 * kernel_main(), respectively. The last two arguments it gets are a magic integer and a data structure. The magic
 * integer determines how the structure is interpreted, the structure itself contains all the information provided by
 * the bootloader or operating system, respectively.
 */
void initialize_standard_library(
    size_t* argc_ptr,
    char*** argv_ptr,
    size_t* envc_ptr,
    char*** envp_ptr,
    uint32_t magic,
    union info* info
) {
    char* args = NULL;

    struct file env = (struct file) {
        .cmd        = NULL,
        .start      = NULL,
        .length     = 0
    };

    struct file bin = (struct file) {
        .cmd        = NULL,
        .start      = NULL,
        .length     = 0
    };

    struct file f = (struct file) {
        .cmd        = NULL,
        .start      = NULL,
        .length     = 0
    };

    switch (magic) {
        case MULTIBOOT_BOOTLOADER_MAGIC:
            args = (char*) info->multiboot.cmdline;

            // FIXME This relies on the order of the modules instead of their names.
            env = (struct file) {
                .cmd        = (char*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[0].cmdline,
                .start      = (void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[0].mod_start,
                .length     = ((void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[0].mod_end)
                              - ((void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[0].mod_start)
            };

            // FIXME This relies on the order of the modules instead of their names.
            bin = (struct file) {
                .cmd        = (char*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[1].cmdline,
                .start      = (void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[1].mod_start,
                .length     = ((void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[1].mod_end)
                              - ((void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[1].mod_start)
            };

            // FIXME This relies on the order of the modules instead of their names.
            f = (struct file) {
                .cmd        = (char*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[2].cmdline,
                .start      = (void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[2].mod_start,
                .length     = ((void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[2].mod_end)
                              - ((void*) ((struct multiboot_mod_list*) info->multiboot.mods_addr)[2].mod_start)
            };

            break;

        case MIVIOS_APPLOADER_MAGIC:
            args = info->mivios.args;

            env = (struct file) {
                .cmd        = info->mivios.env_name,
                .start      = (void*) info->mivios.env_start,
                .length     = info->mivios.env_end - ((void*) info->mivios.env_start)
            };

            break;

        default:
            ((void) 0);
    }

    struct cpu_info cpu_info = (struct cpu_info) {};

    struct init_info init_info = (struct init_info) {
        .bin    = bin,
        .f      = f
    };

    struct kernel_info kernel_info = (struct kernel_info) {
        .args   = args,
        .env    = env
    };

    struct ma_info ma_info = (struct ma_info) {};

    struct mm_info mm_info = (struct mm_info) {};

    struct mmu_info mmu_info = (struct mmu_info) {};

    struct pfa_info pfa_info = (struct pfa_info) {};

    struct tty_info tty_info = (struct tty_info) {};

    struct libc_info libc_info = (struct libc_info) {};

    struct libk_info libk_info = (struct libk_info) {
        .tty        = &tty_info,
        .cpu        = &cpu_info,
        .mmu        = &mmu_info,
        .pfa        = &pfa_info,
        .mm         = &mm_info,
        .ma         = &ma_info,
        .init       = &init_info,
        .kernel     = &kernel_info
    };

    _initialize_standard_library(&libc_info, &libk_info);
    setup(argc_ptr, argv_ptr, envc_ptr, envp_ptr, args, &env);
}

/*
 * Finalize the library.
 */
void finalize_standard_library(int status) {
    teardown();
    _finalize_standard_library();
}
