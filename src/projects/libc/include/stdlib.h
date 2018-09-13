/*
 * stdlib.h
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

#ifndef _STDLIB_H
#define _STDLIB_H 1

#include "sys/cdefs.h"

#include <stddef.h>

/*
 * Stdlib interface.
 */

#define NULL 0

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

__attribute__((__noreturn__))
void abort(void);

void* alloc_page(size_t);

void free_page(void*, size_t);

void* malloc(size_t);

void* calloc(size_t, size_t);

void* realloc(void*, size_t);

void free(void*);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _STDLIB_H
