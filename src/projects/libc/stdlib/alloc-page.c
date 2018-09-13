/*
 * alloc-page.c
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

#include <stdlib.h>

#ifdef __is_libk
#include <kernel/ma.h>
#endif // __is_libk

/*
 * Allocate a given number of consecutive pages and return a pointer to the first one.
 */
void* alloc_page(size_t pages) {
#ifdef __is_libk
    alloc_kpage(pages);
#else // __is_libk
    // TODO Make a syscall to alloc_epage() here.
#endif // __is_libk
}
