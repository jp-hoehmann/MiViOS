#
# pd.S
#
# Created by Jean-Pierre Höhmann on 29.08.18.
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
.set P, 1<<0

# Read/Write.
#
.set R, 1<<1

# User/Supervisor.
#
.set U, 1<<2

# Write Through.
#
.set W, 1<<3

# Cache Disabled.
#
.set C, 1<<4

# Dirty.
#
.set D, 1<<6

# Page Size.
#
.set S, 1<<7

# Global.
#
.set G, 1<<8

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

# Last page directory entry for the kernel.
#
.set KERNEL_PAGE_DIR_END, 511

#
# Control register flags.
#

# Paging.
#
.set PG, 1<<31

# Page Size Extension.
#
.set PSE, 1<<4

# Page Global Enabled.
#
.set PGE, 1<<7

# Flags for CR0.
#
.set CR0, PG

# Flags for CR4.
#
.set CR4, PSE | PGE

#
# Architecture specific information about the pageing.
#

# The size of each page in bytes.
#
.set PAGE_SIZE, 0x1000

# The location in virtual memory the PD will be mapped to (assumed to be followed by the page tables).
#
.set PAGE_DIRECTORY, 0x7fc00000

# The amount of physical memory used for page management (continuous, directly following the kernel).
#
.set PAGE_DIRECTORY_SIZE, 0x400000

#
# Globals used to implement kpalloc(), cpalloc() and dpalloc().
#

.section .data
.align 4

# Flags for a page table entry for a new data page for the kernel.
#
.global _KERNEL_DATA_PAGE
.type _KERNEL_DATA_PAGE, @object
_KERNEL_DATA_PAGE:
.long KERNEL_DATA_PAGE

# Flags for a page table entry for a new code page for an application.
#
.global _USER_CODE_PAGE
.type _USER_CODE_PAGE, @object
_USER_CODE_PAGE:
.long USER_CODE_PAGE

# Flags for a page table entry for a new data page for an application.
#
.global _USER_DATA_PAGE
.type _USER_DATA_PAGE, @object
_USER_DATA_PAGE:
.long USER_DATA_PAGE

# Page size in bytes.
#
.global _PAGE_SIZE
.type _PAGE_SIZE, @object
_PAGE_SIZE:
.long PAGE_SIZE

# Pointer to PD and PT.
#
.global _PAGE_DIRECTORY
.type _PAGE_DIRECTORY, @object
_PAGE_DIRECTORY:
.long PAGE_DIRECTORY

# Combined size of page directory and page tables in bytes.
#
.global _PAGE_DIRECTORY_SIZE
.type _PAGE_DIRECTORY_SIZE, @object
_PAGE_DIRECTORY_SIZE:
.long PAGE_DIRECTORY_SIZE

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
    movl 4(%esp), %ebx                                                  # Load base pointer.
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
    cmp $0x400, %ecx                                                    # f() called twice, but eh, this is asm.
    jne 1b                                                              #

    movl $KERNEL_DUMMY_PAGE, %eax                                       # Load flags for an unused kernel page.
    movl %ebx, %ecx                                                     # Calc num of table entries not needed at the
    shrl $12, %ecx                                                      # start due to huge pages.
    movl $KERNEL_PAGE_DIR_END, %edx                                     # Calculate the number of page table entries
    shll $10, %edx                                                      # to be made for the kernel.
    call pt_fill                                                        # Call pt_fill().

    movl $USER_DUMMY_PAGE, %eax                                         # Load flags for an unused user page.
    addl $0x400, %ecx                                                   # Skip 1024 entries (there's a huge page here).
    movl $0x100000, %edx                                                # Load the total number of page tables to be
    call pt_fill                                                        # made and call pt_fill() again.

    ret

# Turn on paging.
#
.global _pg_set
.type _pg_set, @function
_pg_set:
    movl %cr4, %eax                                                     # Load control register 4,
    orl $CR4, %eax                                                      # set the flags for advanced paging options
    movl %eax, %cr4                                                     # and store the value back in CR4.
    movl %ebx, %cr3                                                     # Point CR3 to the page directory.
    movl %cr0, %eax                                                     # Load control register 0,
    orl $CR0, %eax                                                      # Set the flags for basic paging options,
    movl %eax, %cr0                                                     # and store the valoe back in CR0.
    ret

# Generate dummy page table entries.
#
# This will take a page table entry in %eax, a pointer in %ebx and a count in %edx and will fill %eax %edx times
# starting form %ebx. It will do so by recursively running itself passing the current index in %ecx.
#
pt_fill:
    movl %eax, (%ebx, %ecx, 4)                                          # Write page table entry.
    incl %ecx                                                           # Move to the next entry.
    cmp %edx, %ecx                                                      # If more entries should be written,
    jne pt_fill                                                         # recurse, otherwise return.
    ret
