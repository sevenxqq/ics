#include "cpu/instr.h"

static void instr_execute_2op()//宏的第二种补全方式
{
	operand_read(&opr_dest);//取目的操作数
	operand_read(&opr_src);//读源操作数
	opr_dest.val=alu_sbb(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sbb,r,rm,b)
make_instr_impl_2op(sbb,r,rm,v)
make_instr_impl_2op(sbb,rm,r,b)
make_instr_impl_2op(sbb,rm,r,v)
make_instr_impl_2op(sbb,i,a,b)
make_instr_impl_2op(sbb,i,a,v)

make_instr_impl_2op(sbb,i,rm,v)
make_instr_impl_2op(sbb,i,rm,bv)
make_instr_impl_2op(sbb,i,rm,b)

