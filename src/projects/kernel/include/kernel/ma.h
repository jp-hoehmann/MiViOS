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

struct ma_info {
    // Stub
};

void kernel_ma_initialize(struct ma_info* info);

void kernel_ma_finalize(void);

void* alloc_kpage(size_t pages);

void* alloc_bpage(size_t pages);

void* alloc_cpage(size_t pages);

void* alloc_dpage(size_t pages);

void* alloc_epage(size_t pages);

void* alloc_fpage(size_t pages);

void* alloc_gpage(size_t pages);

void* alloc_spage(size_t pages);

void free_kpage(void* start, size_t pages);

void free_bpage(void* start, size_t pages);

void free_cpage(void* start, size_t pages);

void free_dpage(void* start, size_t pages);

void free_epage(void* start, size_t pages);

void free_fpage(void* start, size_t pages);

void free_gpage(void* start, size_t pages);

void free_spage(void* start, size_t pages);

#endif // ! _KERNEL_MA_H
