/*
 * ma.h
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

#ifndef _KERNEL_MA_H
#define _KERNEL_MA_H

#include <stddef.h>

void kernel_ma_initialize(void);

void kernel_ma_finalize(void);

void* alloc_kpage(size_t);

void* alloc_cpage(size_t);

void* alloc_dpage(size_t);

void* alloc_epage(size_t);

void* alloc_fpage(size_t);

void* alloc_gpage(size_t);

void* alloc_spage(size_t);

void free_kpage(void*, size_t);

void free_cpage(void*, size_t);

void free_dpage(void*, size_t);

void free_epage(void*, size_t);

void free_fpage(void*, size_t);

void free_gpage(void*, size_t);

void free_spage(void*, size_t);

#endif // ! _KERNEL_MA_H
