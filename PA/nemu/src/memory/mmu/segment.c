#include "cpu/cpu.h"
#include "memory/memory.h"
#include "cpu/reg.h"
// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	//load_sreg(sreg);//装载段寄存器
	return cpu.segReg[sreg].base+offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	cpu.segReg[sreg].limit=0xfffff;
	cpu.segReg[sreg].base=0;
}
