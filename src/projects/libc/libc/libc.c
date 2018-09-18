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
 * Initialize the library.
 */
void initialize_standard_library(size_t argc, char* argv[], size_t envc, char* envp[]) {
#ifdef __is_kernel
    initialize_kernel_library(argc, argv);
    setup();
#endif // __is_kernel
#ifdef __is_user
    initialize_user_library(argc, argv, envc, envp);
    setup();
#endif // __is_user
}

/*
 * Finalize the library.
 */
void finalize_standard_library(int status) {
#ifdef __is_kernel
    teardown();
    finalize_kernel_library(status);
#endif // __is_kernel
#ifdef __is_user
    teardown();
    finalize_user_library(status);
#endif // __is_user
}
