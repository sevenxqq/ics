#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "nemu.h"
#include "cpu/cpu.h"
#include "cpu/fpu.h"
#include "cpu/modrm.h"
#include "cpu/operand.h"
#include "cpu/instr_helper.h"
#include "memory/memory.h"
#include <stdio.h>
#include <cpu-ref/instr_ref.h>


extern uint8_t data_size;

#include "cpu/instr/mov.h"
#include "cpu/instr/jmp.h"
#include "cpu/instr/shift.h"
#include "cpu/instr/flags.h"
#include "cpu/instr/group.h"
#include "cpu/instr/special.h"
#include "cpu/instr/x87.h"

/* TODO: add more instructions here */
#include "cpu/instr/cmp.h"
#include "cpu/instr/push.h"
#include "cpu/instr/add.h"
#include "cpu/instr/test.h"
#include "cpu/instr/jcc.h"
#include "cpu/instr/or.h"
#include "cpu/instr/sub.h"
#include "cpu/instr/adc.h"
#include "cpu/instr/sbb.h"
#include "cpu/instr/and.h"
#include "cpu/instr/xor.h"
#include "cpu/instr/pop.h"
#include "cpu/instr/setcc.h"
#include "cpu/instr/mul.h"
#include "cpu/instr/pa4.h"

#endif
