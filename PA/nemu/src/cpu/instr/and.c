#include "cpu/instr.h"

static void instr_execute_2op()//两个操作数
{
	operand_read(&opr_dest);//取目的操作数
	operand_read(&opr_src);//读源操作数
	opr_dest.val=alu_and(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
	operand_write(&opr_dest);
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
}

make_instr_impl_2op(and,r,rm,b)
make_instr_impl_2op(and,r,rm,v)
make_instr_impl_2op(and,rm,r,b)
make_instr_impl_2op(and,rm,r,v)
make_instr_impl_2op(and,i,a,b)
make_instr_impl_2op(and,i,a,v)

make_instr_impl_2op(and,i,rm,v)
make_instr_impl_2op(and,i,rm,bv)
make_instr_impl_2op(and,i,rm,b)

