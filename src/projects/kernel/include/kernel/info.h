/*
 * info.h
 *
 * Created by Jean-Pierre Höhmann on 2018-09-28.
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

#include <kernel/mivios.h>
#include <kernel/multiboot.h>

/*
 * Dummy information structure.
 *
 * This is a fallback, which is used when an unknown magic value is passed.
 */
struct dummy_info { };

/*
 * Generic information structure.
 *
 * This defines the structure passed into _start() through %ebx. It is a union of structures, one of which will be the
 * one that is actually passed. There is one structure for each supported bootloader, which is used when loading the
 * kernel from that loader, as well as one structure for Mivios itself, which is used when loading an application from
 * Mivios. Each structure is identified by a magic value. The magic value is passed through %eax, so the libc can judge
 * what kind of data was actually passed.
 */
union info {
    struct mivios_info;
    struct multiboot_info;
    struct dummy_info;
};
