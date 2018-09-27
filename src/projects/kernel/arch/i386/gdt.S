#
# gdt.S
#
# Created by Jean-Pierre Höhmann on 18-08-26.
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

#include "gdt.h"

.section .data

# Empty GDT with six entries
#
# Entries:
# * Null entry
# * Supervisor code
# * Supervisor data
# * User code
# * User data
# * TSS
#
.align 8
.global _gdt_start
.type _gdt_start, @object
_gdt_start:
.quad 0x0000000000000000
.quad 0x00CF9A000000FFFF
.quad 0x00CF92000000FFFF
.quad 0x00CFFA000000FFFF
.quad 0x00CFF2000000FFFF
.quad 0x0000000000000000
.global _gdt_end
.type _gdt_end, @notype
_gdt_end:

.section .text

# Set the GDT frome a given pointer and size (on the stack in that order).
#
.global _gdt_set
.type _gdt_set, @function
_gdt_set:
    push %ebp                                                           # Set up the stack.
    movl %esp, %ebp                                                     #
    movl 8(%ebp), %eax                                                  # Put the GDT pointer on the stack.
    push %eax                                                           #
    movw 12(%ebp), %ax                                                  # Put the size on the stack as a 16 bit value
    push %ax                                                            # directly below the GDT pointer.
    lgdt (%esp)                                                         # Load the GDT using the 6 bytes just written.
    ljmp $0x08, $x                                                      # Long jump into the supervisor code segment
x:
    movw $0x10, %ax                                                     # Load the supervisor data segment, as data
    movw %ax, %ds                                                       # (d, e, f, and g) and stack (s) segments.
    movw %ax, %es                                                       #
    movw %ax, %fs                                                       # Kernel code: 0b 0000000000001 0 00
    movw %ax, %gs                                                       # (index 1, segmentation on, ring 0)
    movw %ax, %ss                                                       # Kernel data: 0b 0000000000010 0 00
    movl %ebp, %esp                                                     #
    pop %ebp                                                            # Restore the stack and return.
    ret                                                                 #
.size _gdt_set, . - _gdt_set

.end
