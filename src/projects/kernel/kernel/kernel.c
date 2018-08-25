/*
 * kernel.c
 *
 * Created by Jean-Pierre Höhmann on 25.08.18.
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

#include <kernel/tty.h>

/*
 * MiViOS Kernel.
 *
 * The main routine for the kernel, this is where the magic happens. This is called early in the boot process, as soon
 * as the stack is set up (which is required for C to be able to run). Everything else is orchestrated from here. This
 * means nothing can be relied upon at the beginning of this function. There is no paging, no segmentation, no
 * interrupt handling, and no memory management. Just some C-code, a stack and the vast and empty kernel space,
 * stretching from horizon to horizon.
 */
void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
}
