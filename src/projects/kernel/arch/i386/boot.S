#
# boot.S
#
# Created by Jean-Pierre Höhmann on 18-08-25.
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
# Set up everything the kernel needs to execute on i386.
#

# Align loaded modules on page boundaries.
#
.set ALIGN, 1<<0

# Provide memory map.
#
.set MEMINFO, 1<<1

# This is the Multiboot 'flag' field.
#
.set FLAGS, ALIGN | MEMINFO

# Magic letting bootloader find the header.
#
.set MAGIC, 0x1BADB002

# Checksum of the above.
#
.set CHECKSUM, -(MAGIC + FLAGS)

# Multiboot header.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text

# The kernel entry point.
#
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp                                               # Set up the stack,
    call _init                                                          # call the global constructors,
    call kernel_main                                                    # and transfer control to the kernel.
    cli                                                                 # If the kernel unexpectedly returns,
1:                                                                      # disable interrupts and halt the system,
    hlt                                                                 # halt the system again, if it wakes back up
    jmp 1b                                                              # due to a non-maskable interrupt.

.size _start, . - _start

.end
