#include "cpu/instr.h"

static void instr_execute_1op()//操作数为1个
{
	operand_read(&opr_src);//取源操作数的地址
	cpu.esp-=data_size/8;//入栈，把esp向下分配一个位置

	opr_dest.addr=cpu.esp;
	opr_dest.data_size=data_size;
	opr_dest.type=OPR_MEM;

	operand_read(&opr_dest);
	opr_dest.val=sign_ext(opr_src.val,opr_src.data_size);
	operand_write(&opr_dest);
	
}
make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,i,b)
make_instr_impl_1op(push,i,v)

make_instr_func(call_near)//e8
{
	OPERAND imm,temp;
	imm.addr=eip+1;
	imm.sreg=SREG_CS;
	imm.type=OPR_IMM;
	imm.data_size=data_size;
	operand_read(&imm);
	int offset=sign_ext(imm.val,data_size);
	print_asm_1("call", "", 1 + data_size / 8, &imm);
	cpu.eip+=offset;//偏移
        
	temp.type=OPR_MEM;
	temp.val=eip+1+data_size/8;
	temp.data_size=data_size;
	cpu.esp-=data_size/8;//分配字节
	temp.addr=cpu.esp;
	temp.sreg=SREG_SS;
	operand_write(&temp);//存储返回地址，即本来下一条指令的地址

	return 1+data_size/8;
}

make_instr_func(call_near_indirect)//ff
{
	OPERAND imm,temp;
	imm.data_size=data_size;
	int len=modrm_rm(eip+1,&imm);
	imm.sreg=SREG_CS;
	operand_read(&imm);
	
	print_asm_1("call", "", 1 + len, &imm);

        cpu.eip=sign_ext(imm.val,data_size);

	temp.type=OPR_MEM;
	temp.val=eip+1+len;
	temp.data_size=data_size;
	cpu.esp-=data_size/8;//分配字节
	temp.addr=cpu.esp;
	temp.sreg=SREG_SS;
	operand_write(&temp);//存储返回地址，即本来下一条指令的地址

	return 0;
}



make_instr_func(ret_near)//c3
{
	OPERAND temp;
	temp.type=OPR_MEM;//读出内存
	temp.addr=cpu.esp;//取出地址
	temp.sreg=SREG_SS;
	temp.data_size=data_size;
	operand_read(&temp);

	print_asm_1("ret", "", 1 + data_size / 8, &temp);

	cpu.eip=temp.val;
	
	cpu.esp+=data_size/8;
	return 0;
}

make_instr_func(ret_near_imm16)//c2
{
	OPERAND temp;
	temp.val=instr_fetch(eip+1,1);
	
	temp.data_size=8*temp.val;
	temp.addr=cpu.esp;
	temp.sreg=SREG_SS;
	temp.type=OPR_MEM;


	print_asm_1("ret_imm16", "", 3, &temp);

	operand_read(&temp);
	cpu.eip=temp.val;

	cpu.esp+=temp.data_size/8;
	
	
	return 0;
}



make_instr_func(lea)//8d
{
	OPERAND r,rm;
	int len=1;
	r.data_size=32;//?
	rm.data_size=data_size;
	len+= modrm_r_rm(eip+1, &rm, &r);//r和rm位置不能换，按地址读，eip+1是rm,rm之后才是sib
	rm.val=r.addr;//加载有效地址
	rm.sreg=SREG_CS;
	r.sreg=SREG_CS;
	operand_write(&rm);
	print_asm_2("lea", "", len, &r,&rm);
	
	return len;
}

make_instr_func(leave)//c9
{
	cpu.esp=cpu.ebp;//mov %ebp to esp

	OPERAND temp;
	temp.type=OPR_MEM;//读出内存
	temp.addr=cpu.esp;//取出地址
	temp.data_size=data_size;
	temp.sreg=SREG_SS;
	operand_read(&temp);
	cpu.ebp=temp.val;
	cpu.esp+=data_size/8;//pop %ebp

	print_asm_1("leave", "", 1 + data_size / 8, &temp);
	return 1;
}





