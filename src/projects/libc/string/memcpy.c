/*
 * memcpy.c
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

#include <string.h>

/*
 * Copy a block of memory.
 *
 * Copies the values of size bytes from the location pointed to by srcptr directly to the memory block pointed to by
 * dstptr, returning dstptr. The underlying type of the objects pointed to by both the srcptr and dstptr pointers are
 * irrelevant for this function; The result is a binary copy of the data. The function does not check for any
 * terminating null characters in srcptr - it always copies exactly size bytes. To avoid overflows, the size of the
 * arrays pointed to by both the dstptr and srcptr parameters, shall be at least size bytes, and should not overlap.
 * For overlapping memory blocks, memmove() should be used.
 */
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}
