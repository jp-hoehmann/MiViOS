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

#include "libc.h"
#include "setup.h"
#include "teardown.h"

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
void _initialize_standard_library() {
#ifdef __is_kernel
    initialize_kernel_library();
#endif // __is_kernel
#ifdef __is_user
    initialize_user_library();
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
    union info info,
    uint32_t magic
) {
    switch (magic) {
        case MULTIBOOT_BOOTLOADER_MAGIC:
            // Stub.
            break;
        case MIVIOS_APPLOADER_MAGIC:
            // Stub.
            break;
        default:
            // Disturbance in the force.
            abort();
    }
    _initialize_standard_library();
    setup();
}

/*
 * Finalize the library.
 */
void finalize_standard_library(int status) {
    teardown();
    _finalize_standard_library();
}
