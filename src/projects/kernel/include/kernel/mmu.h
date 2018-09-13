/*
 * mmu.h
 *
 * Created by Jean-Pierre Höhmann on 18-08-29.
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

#ifndef _KERNEL_MMU_H
#define _KERNEL_MMU_H 1

#include <stdint.h>

extern uint32_t _KERNEL_DATA_PAGE;
extern uint32_t _USER_CODE_PAGE;
extern uint32_t _USER_DATA_PAGE;

extern void* _kernel_space_start;
extern void* _kernel_space_end;
extern void* _user_space_start;
extern void* _user_space_end;
extern void* _c_space_start;
extern void* _c_space_end;
extern void* _d_space_start;
extern void* _d_space_end;
extern void* _e_space_start;
extern void* _e_space_end;
extern void* _f_space_start;
extern void* _f_space_end;
extern void* _g_space_start;
extern void* _g_space_end;
extern void* _s_space_start;
extern void* _s_space_end;

extern uint32_t _PAGE_SIZE;
extern uint32_t _KERNEL_SPACE_SIZE;
extern uint32_t _USER_SPACE_SIZE;
extern uint32_t _C_SPACE_SIZE;
extern uint32_t _D_SPACE_SIZE;
extern uint32_t _E_SPACE_SIZE;
extern uint32_t _F_SPACE_SIZE;
extern uint32_t _G_SPACE_SIZE;
extern uint32_t _S_SPACE_SIZE;

static uint32_t watermark;

void memory_initialize(void);

#endif // _KERNEL_MMU_H
