/*
 * setup.c
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

#include <stdlib.h>
#include <string.h>

#include "setup.h"
#include "../stdlib/malloc.h"

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
 * Do common initializations.
 */
void setup(void) {
    lib_setup();
    io_setup();
    magic();
}
