/*
 * kernel.c
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
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include <kernel/tty.h>
#include <kernel/cpu.h>
#include <kernel/mmu.h>

/*
 * Initialize the kernel.
 */
void kernel_initialize(size_t argc, char* args[]) {
    // Stub
}

/*
 * Finalize the kernel.
 */
void kernel_finalize(int status) {
    // Stub
}

/*
 * Print a warning.
 */
void kwarn(char* warn) {
    printf("kernel: warn:  %s\n", warn);
}

/*
 * Panic with an error.
 */
__attribute__((__noreturn__))
void kerror(char* err) {
    printf("kernel: error: %s\n", err);
    abort();
}

/*
 * MiViOS Kernel.
 *
 * This is called as soon as the libk is fully operational.
 */
int kernel_main(size_t argc, char* args[]) {
	char* ptr = (char*) calloc(72, 1);
	strcpy(ptr, "Hello, kernel World!");
	puts(ptr);
	return 0;
}
