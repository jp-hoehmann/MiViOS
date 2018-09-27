/*
 * cpu.c
 *
 * Created by Jean-Pierre Höhmann on 18-08-26.
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

#include <kernel/cpu.h>
#include <kernel/kernel.h>
#include <stdlib.h>

#include "gdt.h"
#include "tss.h"

/*
 * Encode a GDT-Entry at a given pointer from a given gdt_entry.
 */
void encode_gdt_entry(uint8_t* dst, struct gdt_entry src) {
    if ((src.limit > 65536) && (src.limit & 0xFFF) != 0xFFF) {
        kerror("Invalid GDT entry limit!");
    }

    // Adjust granularity if required. Set 32-bit-mode for all entries except the null entry.
    if (src.limit > 65536) {
        src.limit >>= 12;
        dst[6] = 0xC0;
    } else {
        dst[6] = src.type == 0x00 ? 0x00 : 0x40;
    }

    // Encode the limit.
    dst[0] = src.limit & 0xFF;
    dst[1] = src.limit >> 8 & 0xFF;
    dst[6] = src.limit >> 16 & 0xF;

    // Encode the base.
    dst[2] = src.base & 0xFF;
    dst[3] = src.base >> 8 & 0xFF;
    dst[4] = src.base >> 16 & 0xFF;
    dst[7] = src.base >> 24 & 0xFF;

    // Encode the type.
    dst[5] = src.type;
}

/*
 * Initialize CPU-specific features.
 */
void kernel_cpu_initialize(void) {
    // Null.
    encode_gdt_entry((uint8_t*) (&_gdt_start)[0], (struct gdt_entry) {
        .base   = 0x00000000,
        .limit  = 0x00000000,
        .type   = 0x00
    });

    // Kernel code.
    encode_gdt_entry((uint8_t*) (&_gdt_start)[1], (struct gdt_entry) {
        .base   = 0x00000000,
        .limit  = 0xFFFFFFFF,
        .type   = 0x9A
    });

    // Kernel data.
    encode_gdt_entry((uint8_t*) (&_gdt_start)[2], (struct gdt_entry) {
        .base   = 0x00000000,
        .limit  = 0xFFFFFFFF,
        .type   = 0x92
    });

    // User code.
    encode_gdt_entry((uint8_t*) (&_gdt_start)[3], (struct gdt_entry) {
        .base   = 0x00000000,
        .limit  = 0xFFFFFFFF,
        .type   = 0xFA
    });

    // User data.
    encode_gdt_entry((uint8_t*) (&_gdt_start)[4], (struct gdt_entry) {
        .base   = 0x00000000,
        .limit  = 0xFFFFFFFF,
        .type   = 0xF2
    });

    // TSS.
    encode_gdt_entry((uint8_t*) (&_gdt_start)[5], (struct gdt_entry) {
        .base   = (uint32_t) &_tss_start,
        .limit  = ((void*) &_tss_end) - ((void*) &_tss_start),
        .type   = 0x89
    });

    _tss_set(&_isr_stack_top, &_tss_start);
    _gdt_set(&_gdt_start, ((void*) &_gdt_end) - ((void*) &_gdt_start));
}

/*
 * Finalize CPU-specific features.
 */
void kernel_cpu_finalize(void) {
    // Stub
}
