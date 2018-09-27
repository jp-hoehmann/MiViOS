/*
 * tss.h
 *
 * Created by Jean-Pierre Höhmann on 2018-09-27.
 *
 * Copyright 2018 Jean-Pierre Höhmann (@NuvandaPV) <jean-pierre@höhmann.info>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARCH_I386_TSS_H
#define ARCH_I386_TSS_H

// Stub.

#ifndef __assembler

#include <stdint.h>

extern uint16_t _tss_start;
extern void _tss_end;
extern uint32_t _isr_stack_bottom;
extern void _isr_stack_top;
extern void _tss_set(void*, uint16_t*);

#endif // ! __assembler

#endif // ! ARCH_I386_TSS_H
