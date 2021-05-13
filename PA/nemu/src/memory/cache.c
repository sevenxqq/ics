#include "memory/cache.h"
#include "memory/memory.h"

CacheLine cache[1024];
extern uint32_t hw_mem_read(paddr_t paddr, size_t len);
extern void hw_mem_write(paddr_t paddr, size_t len, uint32_t data);


void init_cache()//初始化有效位为0
{
	for(int i=0;i<1024;i++)
		{
			 cache[i].valid_bit=0;cache[i].flag=0;
		}
}

 uint32_t cache_read(paddr_t paddr, size_t len, CacheLine * cache)
{
	//根据paddr找到标记、组号、与块内地址 
	uint32_t tag=paddr>>13;//标记
	uint32_t addr_in=paddr-((paddr>>6)<<6);//块内地址
	uint32_t group=(paddr-(tag<<13)-addr_in)>>6;//cache组号
	int lealine=group<<3;//起始行号
	int num=1025;//判断是否能从cache里读取,若能读取num应该在0-1023之间
	for(int i=lealine;i<lealine+8;i++)//组内一个个比标记
	{
		if(cache[i].flag==tag)//标记位相同
		{
			if(cache[i].valid_bit==1)//有效位
			{
				num=i;
				break;
			}
		}
	}
	uint32_t ret = 0;
	uint8_t res[4];//定义一个数组来存结果,之后再复制到ret
	if(num<1025)//命中用块内地址开始读数据
	{
		
		int left=64-addr_in;//在该行剩下的字节数
		if(left>=len)//数据不跨行
		{
			for(int j=addr_in;j<addr_in+len;j++)
				res[j-addr_in]=cache[num].data[j];
			memcpy(&ret, &res, len);
		}
		
		else//跨行
		{
			switch(len)
			{
			case 2:{res[0]=cache[num].data[63];res[1]=cache[num+1].data[0];}
			case 4:
			{
				switch(left)
				{
				case 1:{res[0]=cache[num].data[63];res[1]=cache[num+1].data[0];res[2]=cache[num+1].data[1];res[3]=cache[num+1].data[2];}
				case 2:{res[0]=cache[num].data[62];res[1]=cache[num].data[63];res[2]=cache[num+1].data[0];res[3]=cache[num+1].data[1];}
				case 3:{res[0]=cache[num].data[61];res[1]=cache[num].data[62];res[2]=cache[num+1].data[63];res[3]=cache[num+1].data[0];}
				}
			}
			}
			
			memcpy(&ret, &res, len);ret=hw_mem_read(paddr, len);
		}
	}
	else//不命中
	{
		//去主存中读取,再把内容写进cache
		ret=hw_mem_read(paddr, len);//
		int if_group_full=1;//判断组是否满了
		for(int i=lealine;i<lealine+8;i++)
		{
			if(cache[i].valid_bit==0)//组内是盘就能占
			{
				cache[i].valid_bit=1;cache[i].flag=tag;
				paddr-=addr_in;
				memcpy(&(cache[i].data[0]),hw_mem+paddr,64);
				if_group_full=0;
				break;
			}
		}
		
		if(if_group_full==1)//组满了，随机替换一行
		{
			int rand1=rand()%8;
			rand1+=lealine;
			cache[rand1].flag=tag;cache[rand1].valid_bit=1;
			paddr-=addr_in;
			memcpy(&(cache[rand1].data[0]),hw_mem+paddr,64);
		}
	}
	
	return ret;
	
}

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine * cache)//这个是外界输入了数据所有写
{
	//根据paddr找到标记、组号、与块内地址 
	uint32_t tag=paddr>>13;//标记
	uint32_t addr_in=paddr-((paddr>>6)<<6);//块内地址
	uint32_t group=(paddr-(tag<<13)-addr_in)>>6;//cache组号
	int lealine=group<<3;//起始行号
	int num=1025;
	for(int i=lealine;i<lealine+8;i++)//组内一个个比标记
	{
		if(cache[i].flag==tag)//标记位相同
		{
			
			if(cache[i].valid_bit==1)//有效位
			{
				num=i;
				break;
			}
		}
	}
	if(num<1025)//命中,全写法，同时写cache和主存
	{
		hw_mem_write(paddr,len,data);//写内存
		//写cache呢,把整个主存一块都存进去。
		paddr-=addr_in;
		int left=64-addr_in;//在该行剩下的字节数
		if(left>=len)
		memcpy(&(cache[num].data[0]),hw_mem+paddr,64);
		else
		{
			switch(len)
			{
			case 2:{cache[num].data[63]=data&&0xff;cache[num+1].data[0]=(data>>8)&&0xff;}
			case 4:
			{
				switch(left)
				{
				case 1:{cache[num].data[63]=data&&0xff;cache[num+1].data[0]=(data>>8)&&0xff;cache[num+1].data[1]=(data>>16)&&0xff;cache[num+1].data[2]=(data>>24)&&0xff;}
				case 2:{cache[num].data[62]=data&&0xff;cache[num].data[63]=(data>>8)&&0xff;cache[num+1].data[0]=(data>>16)&&0xff;cache[num+1].data[1]=(data>>24)&&0xff;}
				case 3:{cache[num].data[61]=data&&0xff;cache[num].data[62]=(data>>8)&&0xff;cache[num+1].data[63]=(data>>16)&&0xff;cache[num+1].data[0]=(data>>24)&&0xff;}
				}
			}
			}
			
		}
	}
	else//不命中,非写分配，仅更新主存单元而不装入cache
	{
		hw_mem_write(paddr,len,data);//写内存	
	}
}
















