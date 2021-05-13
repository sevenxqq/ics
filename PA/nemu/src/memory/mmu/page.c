#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	uint32_t dir=laddr>>22;
	uint32_t page=(laddr>>12)-(dir<<10);
	uint32_t offset=laddr-(dir<<22)-(page<<12);
	PDE pde;
	pde.val=paddr_read((cpu.cr3.pdbr<<12)+(dir<<2),4);
	//assert(pde.present==1);
	PTE pte;
	pte.val=paddr_read((pde.page_frame<<12)+(page<<2),4);
	//assert(pte.present==1);
	uint32_t addr=(pte.page_frame<<12)+offset;
	return addr;
	
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
