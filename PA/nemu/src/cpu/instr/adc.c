#include "cpu/instr.h"

static void instr_execute_2op()//宏的第二种补全方式
{
	operand_read(&opr_dest);//取目的操作数
	operand_read(&opr_src);//读源操作数
	opr_dest.val=alu_adc(sign_ext(opr_src.val,opr_src.data_size),sign_ext(opr_dest.val,opr_dest.data_size),data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(adc,r,rm,b)
make_instr_impl_2op(adc,r,rm,v)
make_instr_impl_2op(adc,rm,r,b)
make_instr_impl_2op(adc,rm,r,v)
make_instr_impl_2op(adc,i,a,b)
make_instr_impl_2op(adc,i,a,v)

make_instr_impl_2op(adc,i,rm,v)
make_instr_impl_2op(adc,i,rm,bv)
make_instr_impl_2op(adc,i,rm,b)


