#include "cpu/instr.h"
#include "cpu/intr.h"
#include "device/port_io.h"
#define PUSH(x)\
cpu.esp-=data_size/8;\
vaddr_write(cpu.esp,SREG_SS,data_size/8,x);

make_instr_func(pusha)
{
	uint32_t temp=cpu.esp;
	PUSH(cpu.eax);
	PUSH(cpu.ecx);
	PUSH(cpu.edx);
	PUSH(cpu.ebx);
	PUSH(temp);
	PUSH(cpu.ebp);
	PUSH(cpu.esi);
	PUSH(cpu.edi);
	return 1;	
}
#define POP(x)\
vaddr_write(x,SREG_SS,data_size/8,cpu.esp);\
cpu.esp+=data_size/8;

make_instr_func(popa)
{
	POP(cpu.edi);
	POP(cpu.esi);
	POP(cpu.ebp);
	cpu.esp+=data_size/8;
	POP(cpu.ebx);
	POP(cpu.edx);
	POP(cpu.ecx);
	POP(cpu.eax);
	return 1;	
}

make_instr_func(int_)
{
	uint8_t intr_no=instr_fetch(cpu.eip+1, 1);
	raise_sw_intr(intr_no);
	return 0;
}

make_instr_func(lidt)
{
	int len=1;
	OPERAND r;
	len+=modrm_rm(eip+1,&r);
	uint32_t addr=r.addr;
	cpu.idtr.limit=laddr_read(addr,2);
	cpu.idtr.base=laddr_read(addr+2,4);
	return len;
}

make_instr_func(sti)
{
	cpu.eflags.IF=1;
	return 1;
}

make_instr_func(cli)
{
	cpu.eflags.IF=0;
	return 1;
}

#define Pop(x,y)\
x=vaddr_read(cpu.esp,SREG_SS,y);\
cpu.esp+=4;

make_instr_func(iret)
{
	Pop(cpu.eip,4);
	Pop(cpu.cs.val,2);
	Pop(cpu.eflags.val,4);
	return 0;
}

make_instr_func(in_v)
{
	uint16_t temp=cpu.edx;
	uint32_t val=pio_read(temp,4);
	cpu.eax=val;
	return 1;
}
make_instr_func(in_b)
{
	uint16_t temp=cpu.edx;
	uint8_t val=pio_read(temp,1);
	cpu.eax=val;
	return 1;
}

make_instr_func(out_b)
{
	uint16_t temp=cpu.edx;
	uint8_t val=cpu.eax;
	pio_write(temp,1,val);
	return 1;
}
make_instr_func(out_v)
{
	uint16_t temp=cpu.edx;
	uint32_t val=cpu.eax;
	pio_write(temp,4,val);
	return 1;
}




