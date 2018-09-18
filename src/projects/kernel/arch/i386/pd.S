#
# pd.S
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

#
# Flags for page table and page directory.
#

# Present.
#
.set P, 1 << 0

# Read/Write.
#
.set R, 1 << 1

# User/Supervisor.
#
.set U, 1 << 2

# Write Through.
#
.set W, 1 << 3

# Cache Disabled.
#
.set C, 1 << 4

# Dirty.
#
.set D, 1 << 6

# Page Size.
#
.set S, 1 << 7

# Global.
#
.set G, 1 << 8

# Page directory entry for identity mapped 4MB kernel page.
#
.set KERNEL_HUGE_PAGE, P | R | S | G

# Page directory entry for kernel page table.
#
.set KERNEL_PAGE_TABLE, P | G

# Page directory entry for application page table.
#
.set USER_PAGE_TABLE, P | U

# Page table entry for regular kernel page.
#
.set KERNEL_DATA_PAGE, P | R | G

# Page table entry for application code page.
#
.set USER_CODE_PAGE, P | U

# Page table entry for application data page.
#
.set USER_DATA_PAGE, P | R | U

# Dummy kernel page table entry.
#
.set KERNEL_DUMMY_PAGE, G

# Dummy application page table entry.
#
.set USER_DUMMY_PAGE, U

#
# Control register flags.
#

# Paging.
#
.set PG, 1 << 31

# Page Size Extension.
#
.set PSE, 1 << 4

# Page Global Enabled.
#
.set PGE, 1 << 7

# Flags for CR0.
#
.set CR0, PG

# Flags for CR4.
#
.set CR4, PSE | PGE

#
# Architecture specific information about the pageing.
#

# The number of entries in the page directory.
#
.set PAGE_DIR_LENGTH, 1024

# The number of entries in each page table.
#
.set PAGE_TABLE_LENGTH, 1024

# The size of each page in bytes.
#
.set PAGE_SIZE, 4096

# The size of the memory controlled by each page directory entry.
#
.set HUGE_SIZE, PAGE_SIZE * PAGE_TABLE_LENGTH

# The total number of pages that can be mapped.
#
.set PAGE_COUNT, PAGE_DIR_LENGTH * PAGE_TABLE_LENGTH

# The size of each page table entry.
#
.set ENTRY_SIZE, 4

#
# Information about the virtual memory architecture.
#

# The number of the first page directory entry for the kernel.
#
.set KERNEL_PAGE_DIR_START, 0

# The number of page directory entries for the kernel.
#
.set KERNEL_PAGE_DIR_LENGTH, PAGE_DIR_LENGTH >> 1

# The number of the last page directory entry for the kernel.
#
.set KERNEL_PAGE_DIR_END, KERNEL_PAGE_DIR_START + KERNEL_PAGE_DIR_LENGTH - 1

# The number of the first page directory entry for the user space.
#
.set USER_PAGE_DIR_START, KERNEL_PAGE_DIR_END + 1

# The number of page directory entries for the user space.
#
.set USER_PAGE_DIR_LENGTH, PAGE_DIR_LENGTH >> 1

# The number of the last page directory entry for the user space.
#
.set USER_PAGE_DIR_END, USER_PAGE_DIR_START + USER_PAGE_DIR_LENGTH - 1

# The number of the first page directory entry for the user binary.
#
.set B_PAGE_DIR_START, USER_PAGE_DIR_START

# The number of page directory entries for the user binary.
#
.set B_PAGE_DIR_LENGTH, USER_PAGE_DIR_LENGTH >> 2

# The number of the last page directory entry for the user binary.
#
.set B_PAGE_DIR_END, B_PAGE_DIR_START + B_PAGE_DIR_LENGTH - 1

# The number of the first page directory entry for user extra data.
#
.set E_PAGE_DIR_START, B_PAGE_DIR_END + 1

# The number of page directory entries for user extra data.
#
.set E_PAGE_DIR_LENGTH, USER_PAGE_DIR_LENGTH >> 3

# The number of the last page directory entry for user extra data.
#
.set E_PAGE_DIR_END, E_PAGE_DIR_START + E_PAGE_DIR_LENGTH - 1

# The number of the first page directory entry for user file data.
#
.set F_PAGE_DIR_START, E_PAGE_DIR_END + 1

# The number of page directory entries for user file data.
#
.set F_PAGE_DIR_LENGTH, USER_PAGE_DIR_LENGTH >> 3

# The number of the last page directory entry for user file data.
#
.set F_PAGE_DIR_END, F_PAGE_DIR_START + F_PAGE_DIR_LENGTH - 1

# The number of the first page directory entry for user generic data.
#
.set G_PAGE_DIR_START, F_PAGE_DIR_END + 1

# The number of page directory entries for user generic data.
#
.set G_PAGE_DIR_LENGTH, USER_PAGE_DIR_LENGTH >> 3

# The number of the last page directory entry for user generic data.
#
.set G_PAGE_DIR_END, G_PAGE_DIR_START + G_PAGE_DIR_LENGTH - 1

# The number of the first page directory entry for the user stack.
#
.set S_PAGE_DIR_START, G_PAGE_DIR_END + 1

# The number of page directory entries for the user stack.
#
.set S_PAGE_DIR_LENGTH, USER_PAGE_DIR_LENGTH >> 3

# The number of the last page directory entry for the user stack.
#
.set S_PAGE_DIR_END, S_PAGE_DIR_START + S_PAGE_DIR_LENGTH - 1

# The number of the first unused page directory entry in the user space.
#
.set U_PAGE_DIR_START, S_PAGE_DIR_END + 1

# The number of the last unused page directory entry in the user space.
#
.set U_PAGE_DIR_END, USER_PAGE_DIR_END

# The number of unused page directory entries in the user space.
#
.set U_PAGE_DIR_LENGTH, U_PAGE_DIR_END - U_PAGE_DIR_START + 1

#
# Pointers to and sizes of places of interest in virtual memory space.
#

# Pointer to the start of kernel space.
#
.set KERNEL_SPACE_START, KERNEL_PAGE_DIR_START * HUGE_SIZE

# Size of the kernel space.
#
.set KERNEL_SPACE_SIZE, KERNEL_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the kernel space.
#
.set KERNEL_SPACE_END, KERNEL_SPACE_START + KERNEL_SPACE_SIZE

# Pointer to the end of the page tables.
#
.set PAGE_DIR_END, KERNEL_SPACE_END

# The amount of physical memory used for page management (continuous, directly following the kernel).
#
.set PAGE_DIR_SIZE, PAGE_COUNT * ENTRY_SIZE

# Pointer to the start of the page directory.
#
.set PAGE_DIR_START, PAGE_DIR_END - PAGE_DIR_SIZE

# Pointer to the start of the user space.
#
.set USER_SPACE_START, USER_PAGE_DIR_START * HUGE_SIZE

# Size of the user space.
#
.set USER_SPACE_SIZE, USER_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the user space.
#
.set USER_SPACE_END, USER_SPACE_START + USER_SPACE_SIZE

# Pointer to the start of the user code space.
#
.set B_SPACE_START, B_PAGE_DIR_START * HUGE_SIZE

# Size of the user code space.
#
.set B_SPACE_SIZE, B_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the user code space.
#
.set B_SPACE_END, B_SPACE_START + B_SPACE_SIZE

# Pointer to the start of the user extra data space.
#
.set E_SPACE_START, E_PAGE_DIR_START * HUGE_SIZE

# Size of the user extra data space.
#
.set E_SPACE_SIZE, E_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the user extra data space.
#
.set E_SPACE_END, E_SPACE_START + E_SPACE_SIZE

# Pointer to the start of the user file data space.
#
.set F_SPACE_START, F_PAGE_DIR_START * HUGE_SIZE

# Size of the user file data space.
#
.set F_SPACE_SIZE, F_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the user file data space.
#
.set F_SPACE_END, F_SPACE_START + F_SPACE_SIZE

# Pointer to the start of the user generic data space.
#
.set G_SPACE_START, G_PAGE_DIR_START * HUGE_SIZE

# Size of the user generic data space.
#
.set G_SPACE_SIZE, G_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the user generic data space.
#
.set G_SPACE_END, G_SPACE_START + G_SPACE_SIZE

# Pointer to the start of the user stack space.
#
.set S_SPACE_START, S_PAGE_DIR_START * HUGE_SIZE

# Size of the user stack space.
#
.set S_SPACE_SIZE, S_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the user stack space.
#
.set S_SPACE_END, S_SPACE_START + S_SPACE_SIZE

# Pointer to the start of the unused user space.
#
.set U_SPACE_START, U_PAGE_DIR_START * HUGE_SIZE

# Size of the unused user space.
#
.set U_SPACE_SIZE, U_PAGE_DIR_LENGTH * HUGE_SIZE

# Pointer to the end of the unused user space.
#
.set U_SPACE_END, U_SPACE_START + U_SPACE_SIZE

#
# Globals used to implement page frame and memory allocation.
#

.section .data
.align 4

# Flags for a page table entry for a new data page for the kernel.
#
.global _KERNEL_DATA_PAGE
.type _KERNEL_DATA_PAGE, @object
_KERNEL_DATA_PAGE:
.long KERNEL_DATA_PAGE
.size _KERNEL_DATA_PAGE, . - _KERNEL_DATA_PAGE

# Flags for a page table entry for a new code page for an application.
#
.global _USER_CODE_PAGE
.type _USER_CODE_PAGE, @object
_USER_CODE_PAGE:
.long USER_CODE_PAGE
.size _USER_CODE_PAGE, . - _USER_CODE_PAGE

# Flags for a page table entry for a new data page for an application.
#
.global _USER_DATA_PAGE
.type _USER_DATA_PAGE, @object
_USER_DATA_PAGE:
.long USER_DATA_PAGE
.size _USER_DATA_PAGE, . - _USER_DATA_PAGE

# Pointer to the start of the kernel space.
#
.global _kernel_space_start
.type _kernel_space_start, @object
_kernel_space_start:
.long KERNEL_SPACE_START
.size _kernel_space_start, . - _kernel_space_start

# Pointer to the end of the kernel space.
#
.global _kernel_space_end
.type _kernel_space_end, @object
_kernel_space_end:
.long KERNEL_SPACE_END
.size _kernel_space_end, . - _kernel_space_end

# Pointer to the start of the PD.
#
.global _page_dir_start
.type _page_dir_start, @object
_page_dir_start:
.long PAGE_DIR_START
.size _page_dir_start, . - _page_dir_start

# Pointer to the end of the PTs.
#
.global _page_dir_end
.type _page_dir_end, @object
_page_dir_end:
.long PAGE_DIR_END
.size _page_dir_end, . - _page_dir_end

# Pointer to the start of the user space.
#
.global _user_space_start
.type _user_space_start, @object
_user_space_start:
.long USER_SPACE_START
.size _user_space_start, . - _user_space_start

# Pointer to the end of the user space.
#
.global _user_space_end
.type _user_space_end, @object
_user_space_end:
.long USER_SPACE_END
.size _user_space_end, . - _user_space_end

# Pointer to the start of the user code space.
#
.global _b_space_start
.type _b_space_start, @object
_b_space_start:
.long B_SPACE_START
.size _b_space_start, . - _b_space_start

# Pointer to the end of the user code space.
#
.global _b_space_end
.type _b_space_end, @object
_b_space_end:
.long B_SPACE_END
.size _b_space_end, . - _b_space_end

# Pointer to the start of the user extra data space.
#
.global _e_space_start
.type _e_space_start, @object
_e_space_start:
.long E_SPACE_START
.size _e_space_start, . - _e_space_start

# Pointer to the end of the user extra data space.
#
.global _e_space_end
.type _e_space_end, @object
_e_space_end:
.long E_SPACE_END
.size _e_space_end, . - _e_space_end

# Pointer to the start of the user file data space.
#
.global _f_space_start
.type _f_space_start, @object
_f_space_start:
.long F_SPACE_START
.size _f_space_start, . - _f_space_start

# Pointer to the end of the user file data space.
#
.global _f_space_end
.type _f_space_end, @object
_f_space_end:
.long F_SPACE_END
.size _f_space_end, . - _f_space_end

# Pointer to the start of the user generic data space.
#
.global _g_space_start
.type _g_space_start, @object
_g_space_start:
.long G_SPACE_START
.size _g_space_start, . - _g_space_start

# Pointer to the end of the user generic data space.
#
.global _g_space_end
.type _g_space_end, @object
_g_space_end:
.long G_SPACE_END
.size _g_space_end, . - _g_space_end

# Pointer to the start of the user stack space.
#
.global _s_space_start
.type _s_space_start, @object
_s_space_start:
.long S_SPACE_START
.size _s_space_start, . - _s_space_start

# Pointer to the end of the user stack space.
#
.global _s_space_end
.type _s_space_end, @object
_s_space_end:
.long S_SPACE_END
.size _s_space_end, . - _s_space_end

# Page size in bytes.
#
.global _PAGE_SIZE
.type _PAGE_SIZE, @object
_PAGE_SIZE:
.long PAGE_SIZE
.size _PAGE_SIZE, . - _PAGE_SIZE

# Kernel space size in bytes.
#
.global _KERNEL_SPACE_SIZE
.type _KERNEL_SPACE_SIZE, @object
_KERNEL_SPACE_SIZE:
.long KERNEL_SPACE_SIZE
.size _KERNEL_SPACE_SIZE, . - _KERNEL_SPACE_SIZE

# Combined size of page directory and page tables in bytes.
#
.global _PAGE_DIR_SIZE
.type _PAGE_DIR_SIZE, @object
_PAGE_DIR_SIZE:
.long PAGE_DIR_SIZE
.size _PAGE_DIR_SIZE, . - _PAGE_DIR_SIZE

# User space size in bytes.
#
.global _USER_SPACE_SIZE
.type _USER_SPACE_SIZE, @object
_USER_SPACE_SIZE:
.long USER_SPACE_SIZE
.size _USER_SPACE_SIZE, . - _USER_SPACE_SIZE

# User code space size in bytes.
#
.global _B_SPACE_SIZE
.type _B_SPACE_SIZE, @object
_B_SPACE_SIZE:
.long B_SPACE_SIZE
.size _B_SPACE_SIZE, . - _B_SPACE_SIZE

# User extra data space size in bytes.
#
.global _E_SPACE_SIZE
.type _E_SPACE_SIZE, @object
_E_SPACE_SIZE:
.long E_SPACE_SIZE
.size _E_SPACE_SIZE, . - _E_SPACE_SIZE

# User file data space size in bytes.
#
.global _F_SPACE_SIZE
.type _F_SPACE_SIZE, @object
_F_SPACE_SIZE:
.long F_SPACE_SIZE
.size _F_SPACE_SIZE, . - _F_SPACE_SIZE

# User generic data space size in bytes.
#
.global _G_SPACE_SIZE
.type _G_SPACE_SIZE, @object
_G_SPACE_SIZE:
.long G_SPACE_SIZE
.size _G_SPACE_SIZE, . - _G_SPACE_SIZE

# User stack space size in bytes.
#
.global _S_SPACE_SIZE
.type _S_SPACE_SIZE, @object
_S_SPACE_SIZE:
.long S_SPACE_SIZE
.size _S_SPACE_SIZE, . - _S_SPACE_SIZE

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
.global _pd_set
.type _pd_set, @function
_pd_set:
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
    cmp $KERNEL_PAGE_DIR_END, %ecx                                      # Check if enough page tables have been mapped
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
    cmp $PAGE_DIR_LENGTH, %ecx                                          # f() called twice, but eh, this is asm.
    jne 1b                                                              #

    movl $KERNEL_DUMMY_PAGE, %eax                                       # Load flags for an unused kernel page.
    movl %ebx, %ecx                                                     # Calc num of table entries not needed at the
    shrl $12, %ecx                                                      # start due to huge pages.
    movl $KERNEL_PAGE_DIR_END, %edx                                     # Calculate the number of page table entries
    shll $10, %edx                                                      # to be made for the kernel.
    call pt_fill                                                        # Call pt_fill().

    movl $USER_DUMMY_PAGE, %eax                                         # Load flags for an unused user page.
    addl $PAGE_TABLE_LENGTH, %ecx                                       # Skip 1024 entries (there's a huge page here).
    movl $PAGE_COUNT, %edx                                              # Load the total number of page tables to be
    call pt_fill                                                        # made and call pt_fill() again.

    popl %ebx                                                           # Restore %ebx,
    popl %ebp                                                           # leave the function
    ret                                                                 # and return.
.size _pd_set, . - _pd_set

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
.size _pd_set, . - _pd_set

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
