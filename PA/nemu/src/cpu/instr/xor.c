#include "cpu/instr.h"

static void instr_execute_2op()//宏的第二种补全方式
{
	operand_read(&opr_dest);//取目的操作数
	operand_read(&opr_src);//读源操作数
	opr_dest.val=alu_xor(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(xor,r,rm,b)
make_instr_impl_2op(xor,r,rm,v)
make_instr_impl_2op(xor,rm,r,b)
make_instr_impl_2op(xor,rm,r,v)
make_instr_impl_2op(xor,i,a,b)
make_instr_impl_2op(xor,i,a,v)

make_instr_impl_2op(xor,i,rm,v)
make_instr_impl_2op(xor,i,rm,bv)
make_instr_impl_2op(xor,i,rm,b)

