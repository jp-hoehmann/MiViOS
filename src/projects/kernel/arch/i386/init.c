/*
 * init.c
 *
 * Created by Jean-Pierre Höhmann on 2018-09-29.
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
#include <kernel/init.h>
#include <kernel/ma.h>

#include "pg.h"

static struct file bin;
static struct file f;

void kernel_init_initialize(struct init_info* info) {
    bin     = info->bin;
    f       = info->f;
}

void kernel_init_finalize() {
    ((void) 0);
}

int _run_init(void* b, void* f, void* g) {
    return 0;
}

/*
 * Run the initial user space application.
 *
 * This will run the first – and (in lieu of multitasking) only – user space application.
 */
int run_init(char* args, struct file env) {
    return _run_init(
        memcpy(alloc_bpage(bin.length / PAGE_SIZE + 1), bin.start, bin.length),
        memcpy(alloc_fpage(f.length / PAGE_SIZE + 1), f.start, f.length),
        memcpy(alloc_gpage(env.length / PAGE_SIZE + 1), env.start, env.length));
}
