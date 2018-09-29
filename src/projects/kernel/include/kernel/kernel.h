/*
 * kernel.h
 *
 * Created by Jean-Pierre Höhmann on 18-09-08.
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

#ifndef _KERNEL_KERNEL_H
#define _KERNEL_KERNEL_H

#include <stddef.h>
#include <kernel/file.h>

struct kernel_info {
    char* args;
    struct file env;
};

extern void _kernel_start;
extern void _kernel_end;

void kernel_initialize(struct kernel_info* info);

void kernel_finalize(void);

void kdebug(char* dbg);

void kinfo(char* info);

void kwarn(char* warn);

__attribute__((__noreturn__))
void kerror(char* err);

int kernel_main(size_t argc, char* argv[], size_t envc, char* envp[]);

#endif // ! _KERNEL_KERNEL_H
