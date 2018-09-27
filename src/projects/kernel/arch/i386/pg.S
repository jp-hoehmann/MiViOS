#
# pg.S
#
# Created by Jean-Pierre Höhmann on 18-08-29.
#
# Copyright 2018 Jean-Pierre Höhmann (@NuvandaPV) <jean-pierre@höhmann.info>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#include "pg.h"

.section .data

#
# Globals used to implement page frame and memory allocation.
#

# Flags for a page table entry for a new data page for the kernel.
#
.align 4
.global _KERNEL_DATA_PAGE
.type _KERNEL_DATA_PAGE, @object
_KERNEL_DATA_PAGE:
.long KERNEL_DATA_PAGE
.size _KERNEL_DATA_PAGE, . - _KERNEL_DATA_PAGE

# Flags for a page table entry for a new code page for an application.
#
.align 4
.global _USER_CODE_PAGE
.type _USER_CODE_PAGE, @object
_USER_CODE_PAGE:
.long USER_CODE_PAGE
.size _USER_CODE_PAGE, . - _USER_CODE_PAGE

# Flags for a page table entry for a new data page for an application.
#
.align 4
.global _USER_DATA_PAGE
.type _USER_DATA_PAGE, @object
_USER_DATA_PAGE:
.long USER_DATA_PAGE
.size _USER_DATA_PAGE, . - _USER_DATA_PAGE

# Pointer to the start of the kernel space.
#
.align 4
.global _kernel_space_start
.type _kernel_space_start, @object
_kernel_space_start:
.long KERNEL_SPACE_START
.size _kernel_space_start, . - _kernel_space_start

# Pointer to the end of the kernel space.
#
.align 4
.global _kernel_space_end
.type _kernel_space_end, @object
_kernel_space_end:
.long KERNEL_SPACE_END
.size _kernel_space_end, . - _kernel_space_end

# Pointer to the start of the PD.
#
.align 4
.global _pg_start
.type _pg_start, @object
_pg_start:
.long PG_START
.size _pg_start, . - _pg_start

# Pointer to the end of the PTs.
#
.align 4
.global _pg_end
.type _pg_end, @object
_pg_end:
.long PG_END
.size _pg_end, . - _pg_end

# Pointer to the start of the user space.
#
.align 4
.global _user_space_start
.type _user_space_start, @object
_user_space_start:
.long USER_SPACE_START
.size _user_space_start, . - _user_space_start

# Pointer to the end of the user space.
#
.align 4
.global _user_space_end
.type _user_space_end, @object
_user_space_end:
.long USER_SPACE_END
.size _user_space_end, . - _user_space_end

# Pointer to the start of the user stack space.
#
.align 4
.global _s_space_start
.type _s_space_start, @object
_s_space_start:
.long S_SPACE_START
.size _s_space_start, . - _s_space_start

# Pointer to the end of the user stack space.
#
.align 4
.global _s_space_end
.type _s_space_end, @object
_s_space_end:
.long S_SPACE_END
.size _s_space_end, . - _s_space_end

# Pointer to the start of the user code space.
#
.align 4
.global _b_space_start
.type _b_space_start, @object
_b_space_start:
.long B_SPACE_START
.size _b_space_start, . - _b_space_start

# Pointer to the end of the user code space.
#
.align 4
.global _b_space_end
.type _b_space_end, @object
_b_space_end:
.long B_SPACE_END
.size _b_space_end, . - _b_space_end

# Pointer to the start of the user extra data space.
#
.align 4
.global _e_space_start
.type _e_space_start, @object
_e_space_start:
.long E_SPACE_START
.size _e_space_start, . - _e_space_start

# Pointer to the end of the user extra data space.
#
.align 4
.global _e_space_end
.type _e_space_end, @object
_e_space_end:
.long E_SPACE_END
.size _e_space_end, . - _e_space_end

# Pointer to the start of the user file data space.
#
.align 4
.global _f_space_start
.type _f_space_start, @object
_f_space_start:
.long F_SPACE_START
.size _f_space_start, . - _f_space_start

# Pointer to the end of the user file data space.
#
.align 4
.global _f_space_end
.type _f_space_end, @object
_f_space_end:
.long F_SPACE_END
.size _f_space_end, . - _f_space_end

# Pointer to the start of the user generic data space.
#
.align 4
.global _g_space_start
.type _g_space_start, @object
_g_space_start:
.long G_SPACE_START
.size _g_space_start, . - _g_space_start

# Pointer to the end of the user generic data space.
#
.align 4
.global _g_space_end
.type _g_space_end, @object
_g_space_end:
.long G_SPACE_END
.size _g_space_end, . - _g_space_end

# Page size in bytes.
#
.align 4
.global _PAGE_SIZE
.type _PAGE_SIZE, @object
_PAGE_SIZE:
.long PAGE_SIZE
.size _PAGE_SIZE, . - _PAGE_SIZE

# Kernel space size in bytes.
#
.align 4
.global _KERNEL_SPACE_SIZE
.type _KERNEL_SPACE_SIZE, @object
_KERNEL_SPACE_SIZE:
.long KERNEL_SPACE_SIZE
.size _KERNEL_SPACE_SIZE, . - _KERNEL_SPACE_SIZE

# Combined size of page directory and page tables in bytes.
#
.align 4
.global _PG_SIZE
.type _PG_SIZE, @object
_PG_SIZE:
.long PG_SIZE
.size _PG_SIZE, . - _PG_SIZE

# User space size in bytes.
#
.align 4
.global _USER_SPACE_SIZE
.type _USER_SPACE_SIZE, @object
_USER_SPACE_SIZE:
.long USER_SPACE_SIZE
.size _USER_SPACE_SIZE, . - _USER_SPACE_SIZE

# User stack space size in bytes.
#
.align 4
.global _S_SPACE_SIZE
.type _S_SPACE_SIZE, @object
_S_SPACE_SIZE:
.long S_SPACE_SIZE
.size _S_SPACE_SIZE, . - _S_SPACE_SIZE

# User code space size in bytes.
#
.align 4
.global _B_SPACE_SIZE
.type _B_SPACE_SIZE, @object
_B_SPACE_SIZE:
.long B_SPACE_SIZE
.size _B_SPACE_SIZE, . - _B_SPACE_SIZE

# User extra data space size in bytes.
#
.align 4
.global _E_SPACE_SIZE
.type _E_SPACE_SIZE, @object
_E_SPACE_SIZE:
.long E_SPACE_SIZE
.size _E_SPACE_SIZE, . - _E_SPACE_SIZE

# User file data space size in bytes.
#
.align 4
.global _F_SPACE_SIZE
.type _F_SPACE_SIZE, @object
_F_SPACE_SIZE:
.long F_SPACE_SIZE
.size _F_SPACE_SIZE, . - _F_SPACE_SIZE

# User generic data space size in bytes.
#
.align 4
.global _G_SPACE_SIZE
.type _G_SPACE_SIZE, @object
_G_SPACE_SIZE:
.long G_SPACE_SIZE
.size _G_SPACE_SIZE, . - _G_SPACE_SIZE

.section .text

# Generate a new page directory at a given 4MB-aligned address.
#
# This will take a 4MB-aligned address pointing to the first free 4MB block after the kernel. A full page directory
# will be written at that address. All memory before the address will be identity paged as kernel space with huge
# pages, the rest of the first half of the page directory is then filled with page tables for kernel pages, except for
# the 511th page, which is a huge page pointing to the 4MB block that contains the page directory. The other
# half of the page directory is filled with page tables for user pages, so that applications can be loaded at
# 0x80000000. The actual page tables the directory entries point to are created within the 4MB block, positioned so an
# index into the page directory that will find a page table entry will also point to the corresponding page when used
# as an index into the 4MB block. The actual page tables will be filled with dummmy entries, that have the flags they
# will later use, but without a present flag or a memory address.
#
.global _pg_install
.type _pg_install, @function
_pg_install:
    push %ebp                                                           # Enter the function and
    movl %esp, %ebp                                                     # store %ebx, because the
    push %ebx                                                           # routine will clobber it.

    movl 8(%ebp), %ebx                                                  # Load base pointer.
    movl $0, %ecx                                                       # Load counter.
    movl %ebx, %edx                                                     # Calculate the number of huge pages that need
    shrl $22, %edx                                                      # to be identity mapped for the kernel.
1:
    movl %ecx, %eax                                                     # Calculate the address of the current block as
    shll $22, %eax                                                      # counter * 4MiB.
    orl $KERNEL_HUGE_PAGE, %eax                                         # Add flags.
    movl %eax, (%ebx, %ecx, 4)                                          # Store the entry in the page directory.
    incl %ecx                                                           # Increment the counter.
    cmp %edx, %ecx                                                      # Check if enough blocks have been mapped for
    jne 1b                                                              # the kernel and rerun the loop if necessary.
1:
    movl %ecx, %eax                                                     # Calculate the offset for the page table for
    shll $12, %eax                                                      # the current entry as counter * 4KiB.
    orl %ebx, %eax                                                      # Add base to get the address for the table.
    orl $KERNEL_PAGE_TABLE, %eax                                        # Add flags.
    movl %eax, (%ebx, %ecx, 4)                                          # Store the entry in the page directory.
    incl %ecx                                                           # Increment the counter.
    cmp $KERNEL_PD_END, %ecx                                            # Check if enough page tables have been mapped
    jne 1b                                                              # for the kernel.

    movl %ebx, %eax                                                     # Load pointer to page directory.
    orl $KERNEL_HUGE_PAGE, %eax                                         # Add flags.
    movl %eax, (%ebx, %ecx, 4)                                          # Store the self-referencing entry in the dir.
    incl %ecx                                                           # Increment the counter.
1:
    movl %ecx, %eax                                                     #
    shll $12, %eax                                                      # This is basically the same thing as above,
    orl %ebx, %eax                                                      # except it is user page tables this time and
    orl $USER_PAGE_TABLE, %eax                                          # goes all the way to the end of the directory
    movl %eax, (%ebx, %ecx, 4)                                          # instead of some arbitrary cutoff in the
    incl %ecx                                                           # middle. It would be nicer to have this be a
    cmp $PD_LENGTH, %ecx                                                # f() called twice, but eh, this is asm.
    jne 1b                                                              #

    movl $KERNEL_DUMMY_PAGE, %eax                                       # Load flags for an unused kernel page.
    movl %ebx, %ecx                                                     # Calc num of table entries not needed at the
    shrl $12, %ecx                                                      # start due to huge pages.
    movl $KERNEL_PD_END, %edx                                           # Calculate the number of page table entries
    shll $10, %edx                                                      # to be made for the kernel.
    call pt_fill                                                        # Call pt_fill().

    movl $USER_DUMMY_PAGE, %eax                                         # Load flags for an unused user page.
    addl $PT_LENGTH, %ecx                                               # Skip 1024 entries (there's a huge page here).
    movl $PAGE_COUNT, %edx                                              # Load the total number of page tables to be
    call pt_fill                                                        # made and call pt_fill() again.

    popl %ebx                                                           # Restore %ebx,
    popl %ebp                                                           # leave the function
    ret                                                                 # and return.
.size _pg_install, . - _pg_install

# Turn on paging.
#
# This will enable paging. It is passed a pointer to a previously set up page directory.
#
.global _pg_set
.type _pg_set, @function
_pg_set:
    push %ebp                                                           # Set up
    movl %esp, %ebp                                                     # the stack.

    movl %cr4, %eax                                                     # Load control register 4,
    orl $CR4, %eax                                                      # set the flags for advanced paging options
    movl %eax, %cr4                                                     # and store the value back in CR4.
    movl 8(%ebp), %eax                                                  # Load the pointer to the page directory
    movl %eax, %cr3                                                     # and store it in CR3.
    movl %cr0, %eax                                                     # Load control register 0,
    orl $CR0, %eax                                                      # Set the flags for basic paging options,
    movl %eax, %cr0                                                     # and store the valoe back in CR0.

    popl %ebp                                                           # Leave the function
    ret                                                                 # and return to the caller.
.size _pg_set, . - _pg_set

# Generate dummy page table entries.
#
# This will take a page table entry in %eax, a pointer in %ebx and a count in %edx and will fill %eax %edx times
# starting form %ebx. It will do so by recursively running itself passing the current index in %ecx.
#
pt_fill:
    movl %eax, (%ebx, %ecx, 4)                                          # Write page table entry.
    incl %ecx                                                           # Move to the next entry.
    cmp %edx, %ecx                                                      # If more entries should be written,
    jne pt_fill                                                         # recurse, otherwise return
    ret                                                                 # to the caller.

.end
