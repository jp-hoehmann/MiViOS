/*
 * boot.h
 *
 * Created by Jean-Pierre Höhmann on 18-08-29.
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

#ifndef ARCH_I386_BOOT_H
#define ARCH_I386_BOOT_H

#include <kernel/multiboot.h>

#define MULTIBOOT_HEADER_FLAGS MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
#define MULTIBOOT_HEADER_CHECK -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

#define STACK_SIZE 16384

#define MAGIC 0xC0FFEE1511FE92A15E60D4600DC0FFEE

#ifndef __assembler

extern struct multiboot_header _MULTIBOOT_HEADER;

#endif // ! __assembler

#endif // ! ARCH_I386_BOOT_H
