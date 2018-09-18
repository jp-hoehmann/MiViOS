#
# crt0.S
#
# Created by Jean-Pierre Höhmann on 2018-09-13.
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
# Set up everything the application needs to execute on i386.
#

.section .data

# Userspace magic.
.align 16
.global _MAGIC
.type _MAGIC, @object
_MAGIC:
.octa 0xC0FEFEF029E091E029E091EF02C0FEFE
.size _MAGIC, . - _MAGIC

.section .text

# Process entry point.
#
# This initializes the libc, runs the global constructors and launches the application, passing its exit code to
# exit().
#
.global _start
.type _start, @function
_start:
    popl %eax
    movl $0, %eax
    movl %eax, %ebp
    push %eax
    push %ebp
    movl %esp, %ebp
    subl $24, %esp

    movl 8(%ebp), %edi
    movl 12(%ebp), %esi
    movl 16(%ebp), %edx
    movl 20(%ebp), %ecx
    movl %edi, (%esp)
    movl %esi, 4(%esp)
    movl %edx, 8(%esp)
    movl %ecx, 12(%esp)
    call initialize_standard_library
    call _init
    call main

    movl %eax, (%esp)
    call exit
.size _start, . - _start

# Terminate the process.
#
# This runs the global destructors, finalizes the libc and passes control back to the operating system.
#
.global _exit
.type _exit, @function
_exit:
    push %ebp
    movl %esp, %ebp
    subl $24, %esp

    movl 8(%ebp), %eax
    movl %eax, (%esp)
    call _fini
    call finalize_standard_library
    call _end
.size _exit, . - _exit

# Return to the operating system.
#
# This returns control to the operating system (which will halt the machine).
#
.global _end
.type _end, @function
_end:
    push %ebp
    movl %esp, %ebp
    subl $24, %esp
1:
    jmp 1b
.size _end, . - _end
