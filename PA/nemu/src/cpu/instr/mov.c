#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_2op(mov, r, rm, b)
make_instr_impl_2op(mov, r, rm, v)
make_instr_impl_2op(mov, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)

make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
        operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_r2c_l)
{
	int len=2;
	OPERAND r,temp;
	r.data_size=data_size;
	temp.data_size=32;
	len += modrm_r_rm(eip + 1, &temp, &r);
	r.type=OPR_REG;
	temp.type=OPR_CREG;
	operand_read(&r);
	temp.val=sign_ext(r.val,data_size);
	operand_write(&temp);
	print_asm_2("mov", "", len, &r, &temp);
	return len;
}

make_instr_func(mov_c2r_l)
{
	int len=1;
	OPERAND r,temp;
	r.data_size=32;
	temp.data_size=32;
	len += modrm_r_rm(eip + 1, &r, &temp);
	r.type=OPR_REG;
	temp.type=OPR_CREG;
	operand_read(&temp);
	r.val=sign_ext(temp.val,data_size);
	operand_write(&r);
	print_asm_2("mov", "", len, &temp, &r);
	return len;
}

make_instr_func(mov_rm2s_w)
{
	int len=1;
	OPERAND r,temp;
	r.data_size=16;
	temp.data_size=16;
	len += modrm_r_rm(eip + 1, &r, &temp);
	operand_read(&temp);
	r.val=sign_ext(temp.val,data_size);
	operand_write(&r);
	load_sreg(r.addr);
	print_asm_2("mov", "", len, &temp, &r);
	return len;
}

make_instr_func(lgdt)
{
	int len=1;
	OPERAND r;
	len+=modrm_rm(eip+1,&r);
	uint32_t addr=r.addr;
	cpu.gdtr.limit=laddr_read(addr,2);
	/*if(data_size==16)
		cpu.gdtr.base=laddr_read(addr+2,3);
	else*/
		cpu.gdtr.base=laddr_read(addr+2,4);
	return len;
}





