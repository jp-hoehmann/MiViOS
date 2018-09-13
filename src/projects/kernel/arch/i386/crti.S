#
# crti.S
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
# Constructor magic for i386.
#

.section .init

# Global constructor header.
#
# This acts as the header for the global constructor. It is combined with some GCC magic and a footer to make the
# complete global constructor.
#
.global _init
.type _init, @function
_init:
	push %ebp                                                           # Set up
	movl %esp, %ebp                                                     # the stack.

.section .fini

# Global destructor header.
#
# This acts as the header for the global destructor. It is combined with some GCC magic and a footer to make the
# complete global destructor.
#
.global _fini
.type _fini, @function
_fini:
	push %ebp                                                           # Set up
	movl %esp, %ebp                                                     # the stack.
