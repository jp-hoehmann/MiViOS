/*
 * memmove.h
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
 * Move a block of memory safely to a new location that overlaps the old one.
 *
 * Copies the values of size bytes from the location pointed to by srcptr to the memory block pointed to by dstptr,
 * returning dstptr. Copying takes place as if an intermediate buffer were used, allowing the destination and source to
 * overlap. The underlying type of the objects pointed to by both the srcptr and dstptr pointers are irrelevant for
 * this function; The result is a binary copy of the data. The function does not check for any terminating null
 * character in srcptr - it always copies exactly size bytes. To avoid overflows, the size of the arrays pointed to by
 * both the dstptr and srcptr parameters, shall be at least size bytes.
 */
void* memmove(void* dstptr, const void* srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (size_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}
