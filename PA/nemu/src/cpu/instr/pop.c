#include "cpu/instr.h"


static void instr_execute_1op()//操作数为1位
{
	OPERAND t;
	t.data_size=data_size;
	t.sreg=SREG_SS;
	t.addr=cpu.esp;
	t.type=OPR_MEM;
	operand_read(&t);

	opr_src.val = t.val;
	operand_write(&opr_src);

	cpu.esp+=data_size/8;//出栈
	
	
}
make_instr_impl_1op(pop,r,v)

	
