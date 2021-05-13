#include "cpu/instr.h"

static void instr_execute_2op()//宏的第二种补全方式
{
	operand_read(&opr_dest);//取目的操作数
	operand_read(&opr_src);//读源操作数
	opr_dest.val=alu_sub(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sub,r,rm,b)
make_instr_impl_2op(sub,r,rm,v)
make_instr_impl_2op(sub,rm,r,b)
make_instr_impl_2op(sub,rm,r,v)
make_instr_impl_2op(sub,i,a,b)
make_instr_impl_2op(sub,i,a,v)

make_instr_impl_2op(sub,i,rm,v)
make_instr_impl_2op(sub,i,rm,bv)
make_instr_impl_2op(sub,i,rm,b)

static void instr_execute_1op()//宏的第二种补全方式
{
	operand_read(&opr_src);//读源操作数
	int temp=cpu.eflags.CF;
	opr_src.val=alu_sub(0x00000001,sign_ext(opr_src.val,opr_src.data_size),data_size);
	cpu.eflags.CF=temp;//dec不影响CF的值 
	operand_write(&opr_src);
}
make_instr_impl_1op(dec,rm,v)
make_instr_impl_1op(dec,r,v)
