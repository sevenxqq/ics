#include "cpu/instr.h"

static void instr_execute_2op()//宏的第二种补全方式
{
	operand_read(&opr_dest);//取目的操作数
	operand_read(&opr_src);//读源操作数
	opr_dest.val=alu_add(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(add,r,rm,b)
make_instr_impl_2op(add,r,rm,v)
make_instr_impl_2op(add,rm,r,b)
make_instr_impl_2op(add,rm,r,v)
make_instr_impl_2op(add,i,a,b)
make_instr_impl_2op(add,i,a,v)


make_instr_impl_2op(add,i,rm,v)
make_instr_impl_2op(add,i,rm,bv)
make_instr_impl_2op(add,i,rm,b)

static void instr_execute_1op()//1个操作数
{
	operand_read(&opr_src);//取 源操作数，不要写成目的操作数了
	int temp=cpu.eflags.CF;
	opr_src.val=alu_add(0x00000001,sign_ext(opr_src.val,opr_src.data_size),data_size);
	cpu.eflags.CF=temp;//自增不影响CF的值，但add会影响
	operand_write(&opr_src);
}
make_instr_impl_1op(inc,rm,v)
make_instr_impl_1op(inc,r,v)
