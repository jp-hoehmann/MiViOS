/*
 * atexit.c
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

#include "atexit.h"

static int atexit_handler_count = 0;

static void (*atexit_handlers[ATEXIT_HANDLER_COUNT_LIMIT])(void);

/*
 * Set function to be executed on exit.
 *
 * The function pointed by func is automatically called without arguments when the program terminates normally. If more
 * than one atexit function has been specified by different calls to this function, they are all executed in reverse
 * order as a stack (i.e. the last function specified is the first to be executed at exit). A single function can be
 * registered to be executed at exit more than once.
 *
 * I maximum of 32 handlers may be registered. If this function is called when this number of handlers is already
 * registered, it will do nothing and return a non-zero value. If the handler is successfully registered, the function
 * will return zero.
 */
int atexit(void (*func)(void)) {
    if (atexit_handler_count == ATEXIT_HANDLER_COUNT_LIMIT) {
        return 1;
    }

    atexit_handlers[atexit_handler_count++] = func;
    return 0;
}

/*
 * Run the atexit handlers.
 */
void run_atexit_handlers(void) {
    for (; atexit_handler_count; atexit_handler_count--) {
        atexit_handlers[atexit_handler_count]();
    }
}
