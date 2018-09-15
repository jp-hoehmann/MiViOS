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

.section .bss

# Reserve a stack for the initial thread.
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .data

# Kernel magic.
.align 16
.global _MAGIC
.type _MAGIC, @object
_MAGIC:
.octa 0xC0FFEE1511FE92A15E60D4600DC0FFEE
.size _MAGIC, . - _MAGIC

.section .text

# The kernel entry point.
#
# This initializes the libk, runs the global constructors and launches the kernel, passing its exit code to exit().
#
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp                                               # Set up the stack,
    movl $0, %eax                                                       # by loading its position,
    movl %eax, %ebp                                                     # and storing a NULL
    push %eax                                                           # return address and
    push %ebp                                                           # base pointer.
    movl %esp, %ebp                                                     # Add a new stack frame and
    subl $40, %esp                                                      # make room for local variables.

    movl $0, %eax                                                       # Store two empty
    movl %eax, 32(%esp)                                                 # strings for args
    movl %eax, 36(%esp)                                                 # and envp, respectively.
    leal 32(%esp), %eax                                                 # Create a
    movl %eax, 24(%esp)                                                 # pointer
    leal 36(%esp), %eax                                                 # to each
    movl %eax, 28(%esp)                                                 # string.
    leal 24(%esp), %eax                                                 # Create
    movl %eax, 16(%esp)                                                 # pointers
    leal 28(%esp), %eax                                                 # to the
    movl %eax, 20(%esp)                                                 # pointers.

    movl $0, %edi                                                       # Initialize argc
    movl 16(%esp), %esi                                                 # and envc to
    movl $0, %edx                                                       # zero, and argv
    movl 20(%esp), %ecx                                                 # and envp each
    movl %edi, (%esp)                                                   # to an array of
    movl %esi, 4(%esp)                                                  # strings containing
    movl %edx, 8(%esp)                                                  # a single empty
    movl %ecx, 12(%esp)                                                 # string.

    call initialize_standard_library                                    # Initialize everything things necessary for the
    call _init                                                          # library to work, call the global constructors,
    call kernel_main                                                    # and transfer control to the kernel.

    movl %eax, (%esp)                                                   # Call exit() with the result
    call exit                                                           # of kernel_main().
.size _start, . - _start

# Terminate the operating system.
#
# This runs the global destructors, finalizes the libc and halts the machine.
#
.global _exit
.type _exit, @function
_exit:
    push %ebp                                                           # Set up a new stack
    movl %esp, %ebp                                                     # frame and make room
    subl $24, %esp                                                      # for local variables.

    movl 8(%ebp), %eax                                                  # Load the status
    movl %eax, (%esp)                                                   # parameter and
    call _fini                                                          # use it to call
    call finalize_standard_library                                      # _fini(), finalize_standard_library()
    call _end                                                           # and _end().
.size _exit, . - _exit

# Halt the machine.
#
# This halts the machine, after all work is completed.
#
.global _end
.type _end, @function
_end:
    push %ebp                                                           # Set up a
    movl %esp, %ebp                                                     # new stack
    subl $8, %esp                                                       # frame.

    cli                                                                 # Disable interrupts.
1:
    hlt                                                                 # Halt the system and halt again if it wakes
    jmp 1b                                                              # back up due to a non-maskable interrupt.
.size _end, . - _end

.end
