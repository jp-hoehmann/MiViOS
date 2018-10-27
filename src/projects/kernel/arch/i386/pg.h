/*
 * pd.h
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

#ifndef ARCH_I386_PD_H
#define ARCH_I386_PD_H

/*
 * Flags for page table and page directory.
 */

// Present.
#define P (1 << 0)

// Read/Write.
#define R (1 << 1)

// User/Supervisor.
#define U (1 << 2)

// Write Through.
#define W (1 << 3)

// Cache Disabled.
#define C (1 << 4)

// Dirty.
#define D (1 << 6)

// Page Size.
#define S (1 << 7)

// Global.
#define G (1 << 8)

// Page directory entry for identity mapped 4MB kernel page.
#define KERNEL_HUGE_PAGE (P | R | S | G)

// Page directory entry for kernel page table.
#define KERNEL_PAGE_TABLE (P | G)

// Page directory entry for application page table.
#define USER_PAGE_TABLE (P | U)

// Page table entry for regular kernel page.
#define KERNEL_DATA_PAGE (P | R | G)

// Page table entry for application code page.
#define USER_CODE_PAGE (P | U)

// Page table entry for application data page.
#define USER_DATA_PAGE (P | R | U)

// Dummy kernel page table entry.
#define KERNEL_DUMMY_PAGE G

// Dummy application page table entry.
#define USER_DUMMY_PAGE U

/*
 * Control register flags.
 */

// Paging.
#define PG (1 << 31)

// Page Size Extension.
#define PSE (1 << 4)

// Page Global Enabled.
#define PGE (1 << 7)

// Flags for CR0.
#define CR0 PG

// Flags for CR4.
#define CR4 (PSE | PGE)

/*
 * Architecture specific information about the pageing.
 */

// The number of entries in the page directory.
#define PD_LENGTH 1024

// The number of entries in each page table.
#define PT_LENGTH 1024

// The size of each page in bytes.
#define PAGE_SIZE 4096

// The size of the memory controlled by each page directory entry.
#define HUGE_SIZE (PAGE_SIZE * PT_LENGTH)

// The total number of pages that can be mapped.
#define PAGE_COUNT (PD_LENGTH * PT_LENGTH)

// The size of each page table entry.
#define ENTRY_SIZE 4

/*
 * Information about the virtual memory architecture.
 */

// The number of the first page directory entry for the kernel.
#define KERNEL_PD_START 0

// The number of page directory entries for the kernel.
#define KERNEL_PD_LENGTH (PD_LENGTH >> 5)

// The number of the last page directory entry for the kernel.
#define KERNEL_PD_END (KERNEL_PD_START + KERNEL_PD_LENGTH - 1)

// The number of the first page directory entry for the user space.
#define USER_PD_START (KERNEL_PD_END + 1)

// The number of page directory entries for the user space.
#define USER_PD_LENGTH (PD_LENGTH - KERNEL_PD_LENGTH)

// The number of the last page directory entry for the user space.
#define USER_PD_END (USER_PD_START + USER_PD_LENGTH - 1)

// The number of the first page table entry for the kernel. The kernel starts with a huge page, so this is a purely
// theoretical number.
#define KERNEL_PT_START (KERNEL_PD_START * PT_LENGTH)

// The number of page table entries for the kernel. This is the theoretical maximal number of page table entries for
// the kernel. The actual  of page table entries for the kernel will be lower due to huge pages.
#define KERNEL_PT_LENGTH (KERNEL_PD_LENGTH * PT_LENGTH)

// The number of the last page table entry for the kernel. This as a theoretical number that counts all page table
// entries, even the ones that do not exist due to huge pages. Thus it can be turned into a pointer into memory by
// simply bit-shifting it.
#define KERNEL_PT_END (KERNEL_PT_START + KERNEL_PT_LENGTH - 1)

// The number of the first page table entry for the user space. This as a theoretical number that counts all page table
// entries, even the ones that do not exist due to huge pages. Thus it can be turned into a pointer into memory by
// simply bit-shifting it.
#define USER_PT_START (USER_PD_START * PT_LENGTH)

// The number of page table entries for the user space. This as a theoretical number that counts all page table
// entries, even the ones that do not exist due to huge pages. Thus it can be turned into a pointer into memory by
// simply bit-shifting it.
#define USER_PT_LENGTH (USER_PD_LENGTH * PT_LENGTH)

// The number of the last page table entry for the user space. This as a theoretical number that counts all page table
// entries, even the ones that do not exist due to huge pages. Thus it can be turned into a pointer into memory by
// simply bit-shifting it.
#define USER_PT_END (USER_PT_START + USER_PT_LENGTH - 1)

// The number of the first page table entry for the user stack.
#define S_PT_START USER_PT_START

// The number of page table entries for the user stack.
#define S_PT_LENGTH 72

// The number of the last page table entry for the user stack.
#define S_PT_END (S_PT_START + S_PT_LENGTH - 1)

// The number of the first page table entry for the user binary.
#define B_PT_START (S_PT_END + 1)

// The number of page table entries for the user binary.
#define B_PT_LENGTH (32768 - S_PT_LENGTH)

// The number of the last page table entry for the user binary.
#define B_PT_END (B_PT_START + B_PT_LENGTH - 1)

// The number of the first page table entry for user extra data.
#define E_PT_START (B_PT_END + 1)

// The number of page table entries for user extra data.
#define E_PT_LENGTH 65536

// The number of the last page table entry for user extra data.
#define E_PT_END (E_PT_START + E_PT_LENGTH - 1)

// The number of the first page table entry for user file data.
#define F_PT_START (E_PT_END + 1)

// The number of page table entries for user file data.
#define F_PT_LENGTH 65536

// The number of the last page table entry for user file data.
#define F_PT_END (F_PT_START + F_PT_LENGTH - 1)

// The number of the first page table entry for user generic data.
#define G_PT_START (F_PT_END + 1)

// The number of page table entries for user generic data.
#define G_PT_LENGTH 65536

// The number of the last page table entry for user generic data.
#define G_PT_END (G_PT_START + G_PT_LENGTH - 1)

// The number of the first unused page table entry in the user space.
#define U_PT_START (G_PT_END + 1)

// The number of the last unused page table entry in the user space.
#define U_PT_END USER_PT_END

// The number of unused page table entries in the user space.
#define U_PT_LENGTH (U_PT_END - U_PT_START + 1)

/*
 * Pointers to and sizes of places of interest in virtual memory space.
 */

// Pointer to the start of kernel space.
#define KERNEL_SPACE_START (KERNEL_PD_START * HUGE_SIZE)

// Size of the kernel space.
#define KERNEL_SPACE_SIZE (KERNEL_PD_LENGTH * HUGE_SIZE)

// Pointer to the end of the kernel space.
#define KERNEL_SPACE_END (KERNEL_SPACE_START + KERNEL_SPACE_SIZE)

// Pointer to the end of the page tables.
#define PG_END KERNEL_SPACE_END

// The amount of physical memory used for page management (continuous, directly following the kernel).
#define PG_SIZE (PAGE_COUNT * ENTRY_SIZE)

// Pointer to the start of the page directory.
#define PG_START (PG_END - PG_SIZE)

// Pointer to the start of the user space.
#define USER_SPACE_START (USER_PD_START * HUGE_SIZE)

// Size of the user space.
#define USER_SPACE_SIZE (USER_PD_LENGTH * HUGE_SIZE)

// Pointer to the end of the user space.
#define USER_SPACE_END (USER_SPACE_START + USER_SPACE_SIZE)

// Pointer to the start of the user stack space.
#define S_SPACE_START (S_PT_START * PAGE_SIZE)

// Size of the user stack space.
#define S_SPACE_SIZE (S_PT_LENGTH * PAGE_SIZE)

// Pointer to the end of the user stack space.
#define S_SPACE_END (S_SPACE_START + S_SPACE_SIZE)

// Pointer to the start of the user code space.
#define B_SPACE_START (B_PT_START * PAGE_SIZE)

// Size of the user code space.
#define B_SPACE_SIZE (B_PT_LENGTH * PAGE_SIZE)

// Pointer to the end of the user code space.
#define B_SPACE_END (B_SPACE_START + B_SPACE_SIZE)

// Pointer to the start of the user extra data space.
#define E_SPACE_START (E_PT_START * PAGE_SIZE)

// Size of the user extra data space.
#define E_SPACE_SIZE (E_PT_LENGTH * PAGE_SIZE)

// Pointer to the end of the user extra data space.
#define E_SPACE_END (E_SPACE_START + E_SPACE_SIZE)

// Pointer to the start of the user file data space.
#define F_SPACE_START (F_PT_START * PAGE_SIZE)

// Size of the user file data space.
#define F_SPACE_SIZE (F_PT_LENGTH * PAGE_SIZE)

// Pointer to the end of the user file data space.
#define F_SPACE_END (F_SPACE_START + F_SPACE_SIZE)

// Pointer to the start of the user generic data space.
#define G_SPACE_START (G_PT_START * PAGE_SIZE)

// Size of the user generic data space.
#define G_SPACE_SIZE (G_PT_LENGTH * PAGE_SIZE)

// Pointer to the end of the user generic data space.
#define G_SPACE_END (G_SPACE_START + G_SPACE_SIZE)

// Pointer to the start of the unused user space.
#define U_SPACE_START (U_PT_START * PAGE_SIZE)

// Size of the unused user space.
#define U_SPACE_SIZE (U_PT_LENGTH * PAGE_SIZE)

// Pointer to the end of the unused user space.
#define U_SPACE_END (U_SPACE_START + U_SPACE_SIZE)

#ifndef __assembler

#include <stdint.h>

extern uint32_t _pg_start;
extern uint32_t _PG_SIZE;

extern void _pg_install(uint32_t);
extern void _pg_set(uint32_t);

#endif // ! __assembler

#endif // ! ARCH_I386_PD_H
