#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE) // number of page tables to cover the vmem

PDE *get_updir();

void create_video_mapping()
{

	/* TODO: create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */

	PDE* updir =get_updir();
	int pde_index=0xa0000>>22;
	PTE vmem_pte[NR_PTE] align_to_page;
	PTE* vmem_pte_addr=(PTE*) va_to_pa(vmem_pte);
	updir[pde_index].val=make_pde(vmem_pte_addr);

	for(uint32_t vmem_addr=VMEM_ADDR;vmem_addr<VMEM_ADDR+SCR_SIZE;vmem_addr+=PAGE_SIZE)
	{
		int pte_index=vmem_addr>>12;
		vmem_pte[pte_index].val=make_pte(vmem_addr);
	}
}

void video_mapping_write_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		buf[i] = i;
	}
}

void video_mapping_read_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		assert(buf[i] == i);
	}
}

void video_mapping_clear()
{
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}
