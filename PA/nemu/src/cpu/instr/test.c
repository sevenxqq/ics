#include "cpu/instr.h"

static void instr_execute_2op()//宏的第二种补全方式
{
	operand_read(&opr_dest);//取目的操作数
	operand_read(&opr_src);//读源操作数
	int temp=opr_dest.val;
	alu_and(opr_src.val,temp,data_size);
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
//test指令将两个操作数进行与运算，仅改变标志位，不回送结果
}
make_instr_impl_2op(test,r,rm,v)
make_instr_impl_2op(test,r,rm,b)
make_instr_impl_2op(test,i,rm,b)
make_instr_impl_2op(test,i,rm,v)
make_instr_impl_2op(test,i,a,b)
make_instr_impl_2op(test,i,a,v)
