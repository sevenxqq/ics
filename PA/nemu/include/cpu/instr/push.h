#ifndef __INSTR_PUSH_H__
#define __INSTR_PUSH_H__

make_instr_func(push_r_v);
make_instr_func(push_rm_v);
make_instr_func(push_i_b);
make_instr_func(push_i_v);
make_instr_func(call_near);
make_instr_func(call_near_indirect);
make_instr_func(ret_near);
make_instr_func(ret_near_imm16);
make_instr_func(lea);
make_instr_func(leave);
#endif
