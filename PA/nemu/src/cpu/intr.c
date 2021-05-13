#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

#define PUSH(x,y)\
cpu.esp-=4;\
vaddr_write(cpu.esp,SREG_SS,y,x);

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	uint32_t addr=cpu.idtr.base+intr_no*8;
	uint32_t desp[2];
	desp[0]=laddr_read(addr,4);
	desp[1]=laddr_read(addr+4,4);
	GateDesc gatedesc;
	memcpy(&gatedesc,desp,8);
	PUSH(cpu.eflags.val,4);
	PUSH(cpu.cs.val,2);
	PUSH(cpu.eip,4);
	if(gatedesc.type==14)
		cpu.eflags.IF=0;
	else
		cpu.eflags.IF=1;
	
	cpu.cs.val=gatedesc.selector;
	cpu.cs.base=0;
	cpu.cs.limit=0xFFFFF;
	uint32_t temp=gatedesc.offset_31_16;// 防止溢出
	uint32_t temp1=gatedesc.offset_15_0;
	cpu.eip=(temp<<16)+temp1;

#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
