#ifndef _CACHE_H_
#define _CACHE_H_
#define CACHE_ENABLED


#include  "nemu.h"
#include "memory/mmu/segment.h"
#include "memory/mmu/page.h"
#include "memory/mmu/tlb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	bool valid_bit;//1位有效位
	uint32_t flag ;//实际是19位标志位
	uint8_t data[64];//64byte存储空间
	
}CacheLine;

extern  CacheLine cache[1024];
void init_cache();
uint32_t cache_read(paddr_t paddr, size_t len, CacheLine * cache); 
void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine * cache);

#endif
