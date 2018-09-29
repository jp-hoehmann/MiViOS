/*
 * mivios.h
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

/*
 * Mivios header file.
 */

#ifndef _KERNEL_MIVIOS_H
#define _KERNEL_MIVIOS_H

// This should be in %eax.
#define MIVIOS_APPLOADER_MAGIC 0x600DB007

/*
 * Information structure passed to applications loaded by mivios.
 */
struct
    __attribute__((__packed__))
    __attribute__((__aligned__(4)))
mivios_info {
    char* args;
    char* env_name;
    char* env_start;
    void* env_end;
};

#endif // ! _KERNEL_MIVIOS_H
