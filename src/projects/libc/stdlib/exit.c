/*
 * exit.c
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

#include <stdlib.h>

#include "exit.h"
#include "atexit.h"

/*
 * Terminate calling process.
 *
 * This function terminates the process normally, performing the regular cleanup for terminating programs.
 *
 * If status is zero or EXIT_SUCCESS, a successful termination status is returned to the host environment. If status is
 * EXIT_FAILURE, an unsuccessful termination status is returned to the host environment.
 */
__attribute__((__noreturn__))
void exit(int status) {
    run_atexit_handlers();
    _exit(status);
}

/*
 * Terminate calling process quickly.
 *
 * This function terminates the process normally by returning control to the host environment, but without performing
 * any of the regular cleanup tasks for terminating processes (as exit() does). No object destructors, nor functions
 * registered using atexit() are called.
 *
 * If status is zero or EXIT_SUCCESS, a successful termination status is returned to the host environment. If status is
 * EXIT_FAILURE, an unsuccessful termination status is returned to the host environment.
 */
__attribute__((__noreturn__))
void _Exit(int status) {
    _end(status);
}
