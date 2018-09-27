#
# tss.S
#
# Created by Jean-Pierre Höhmann on 2018-09-27.
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

#include "tss.h"

.section .data

# TSS that sets %ss to 0x10.
#
.global _tss_start
.type _tss_start, @object
_tss_start:
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0010
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.short 0x0000, 0x0000
.global _tss_end
.type _tss_end, @notype
_tss_end:

.section .bss

# Stack for ISRs.
#
.align 16
.global _isr_stack_bottom
.type _isr_stack_bottom, @notype
_isr_stack_bottom:
.skip 65536
.global _isr_stack_top
.type _isr_stack_top, @notype
_isr_stack_top:

.section .text

# Set the TSS.
#
# This will take a pointer to an empty stack and a pointer to a TSS (on the stack in that order). It will populate the
# stack with a NULL return pointer, and add the pointer to the top of that stack to the TSS.
#
.global _tss_set
.type _tss_set, @function
_tss_set:
    push %ebp
    movl %esp, %ebp
    subl $8, %esp

    movl 8(%ebp), %edx
    movl $0, %eax
    subl $4, %edx
    movl %eax, (%edx)

    movl 12(%ebp), %eax
    movl %edx, 4(%eax)

    addl $8, %esp
    popl %ebp
    ret
.size _tss_set, . - _tss_set

.end
