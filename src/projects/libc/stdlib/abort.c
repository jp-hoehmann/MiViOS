/*
 * abort.c
 *
 * Created by Jean-Pierre Höhmann on 18-08-25.
 *
 * Copyright 2018 Jean-Pierre Höhmann (@NuvandaPV) <jean-pierre@höhmann.info>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

#include "abort.h"

/*
 * Terminate the current process abnormally.
 *
 * This will trigger a kernel panic, when invoked in the kernel, and terminate the current process, when called from
 * userspace.
 */
__attribute__((__noreturn__))
void abort(void) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#ifdef __is_kernel
    // TODO Add proper kernel panic.
    printf("kernel: panic: abort()\n");
    while (1) {}
    __builtin_unreachable();
#endif // __is_kernel
#ifdef __is_user
    // TODO Abnormally terminate the process as if by SIGABRT.
    printf("abort()\n");
    while (1) {}
    __builtin_unreachable();
#endif // __is_user
#pragma clang diagnostic pop
}
