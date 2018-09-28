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

#include "boot.h"

#
# Set up everything the kernel needs to execute on i386.
#

.section .multiboot

# Multiboot header.
.align 4
.global _MULTIBOOT_HEADER
.type _MULTIBOOT_HEADER, @object
_MULTIBOOT_HEADER:
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long MULTIBOOT_HEADER_CHECK
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.size _MULTIBOOT_HEADER, . - _MULTIBOOT_HEADER

.section .bss

# Reserve a stack for the initial thread.
.align 16
stack_bottom:
.skip STACK_SIZE
stack_top:

.section .data

# Kernel magic.
.align 16
.global _MAGIC
.type _MAGIC, @object
_MAGIC:
.octa MAGIC
.size _MAGIC, . - _MAGIC

.section .text

# The kernel entry point.
#
# This initializes the libk, runs the global constructors and launches the kernel, passing its exit code to exit().
#
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp                                               # Set up the stack, by loading
    movl $0, %ebp                                                       # its position and storing
    pushl $0                                                            # a NULL return address
    pushl %ebp                                                          # and base pointer.
    pushl $0                                                            # Clear the
    popf                                                                # EFLAGS.
    movl %esp, %ebp                                                     # Add a new stack frame and
    subl $40, %esp                                                      # make room for local variables.

    movl $0, 36(%esp)                                                   # Initialize argc
    movl $0, 32(%esp)                                                   # and envc to zero
    movl $0, 28(%esp)                                                   # and argv and envp
    movl $0, 24(%esp)                                                   # to NULL.
    leal 36(%esp), %edi                                                 # Load pointers to
    leal 32(%esp), %esi                                                 # argc, argv, envc
    leal 28(%esp), %edx                                                 # and envp.
    leal 24(%esp), %ecx                                                 #
    movl %ebx, 20(%esp)                                                 # Initialize the library,
    movl %eax, 16(%esp)                                                 # passing the pointers,
    movl %ecx, 12(%esp)                                                 # along with the info
    movl %edx, 8(%esp)                                                  # structure and magic
    movl %esi, 4(%esp)                                                  # value from the
    movl %edi, (%esp)                                                   # bootloader.
    call initialize_standard_library                                    #

    call _init                                                          # Call global constructors.

    movl 36(%esp), %edi                                                 # Load the values
    movl 32(%esp), %esi                                                 # for argc, argv,
    movl 28(%esp), %edx                                                 # envc and envp,
    movl 24(%esp), %ecx                                                 # that were populated
    movl %ecx, 12(%esp)                                                 # during library
    movl %edx, 8(%esp)                                                  # initialization
    movl %esi, 4(%esp)                                                  # and pass them
    movl %edi, (%esp)                                                   # into the main
    call kernel_main                                                    # kernel.

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
