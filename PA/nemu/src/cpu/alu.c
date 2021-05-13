#include "cpu/cpu.h"

void set_PF(uint32_t sum)
{
	int count=0;
	sum&=0xFF;//PF测试的是低8位
	while(sum>0)
	{
		if(sum%2==1)
			count++;
		sum/=2;
	}
	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;
	
}
void set_CF_add(uint32_t result, uint32_t src, size_t data_size) 
{
	result = sign_ext(result, data_size);//符号扩展
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	cpu.eflags.CF = result < src;
}
void set_SF(uint32_t result, size_t data_size) 
{
	result = sign_ext(result, data_size);
	cpu.eflags.SF = sign(result);
}
void set_ZF(uint32_t sum)
{
	if(sum==0)//根据结果是否为0来确定ZF；
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;
}
void set_OF_add(uint32_t result, uint32_t src, uint32_t dest, size_t data_size) 
{
	switch(data_size) 
	{
	case 8:
	result = sign_ext(result&0xFF, 8);
	src = sign_ext(src & 0xFF, 8);
	dest = sign_ext(dest & 0xFF, 8);
	break;
	case 16:
	result = sign_ext(result&0xFFFF, 16);
	src = sign_ext(src & 0xFFFF, 16);
	dest = sign_ext(dest & 0xFFFF, 16);
	break;
	default: break;// do nothing
	}
	if(sign(src) == sign(dest))//加法溢出，两个加数符号相同，和符号与他们不同
	 {
		if(sign(src) != sign(result))
			cpu.eflags.OF = 1;
		else
			cpu.eflags.OF = 0;
	} 
	else {
	cpu.eflags.OF = 0;
}
}
uint32_t set_return(uint32_t sum,size_t data_size)
{
	sum&=(0xFFFFFFFF>>(32-data_size));
	return sum;
}




uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
return __ref_alu_add(src, dest, data_size);
#else
    //data_size指的是数据的位数
    //判断输入的数据类型是几位的
	uint32_t sum=dest+src;
	sum=set_return (sum,data_size);
	set_PF(sum);
	set_CF_add(sum,src,data_size);
	set_ZF(sum);
	set_SF(sum,data_size);
	set_OF_add(sum,src,dest,data_size);
    return sum;	

	printf("\e[0;31mPlease implement me at add/alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

void set_CF_adc(uint32_t sum,uint32_t src,uint32_t dest,uint32_t data_size)
{
	sum = sign_ext(sum, data_size);//符号扩展
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	if(cpu.eflags.CF)
		cpu.eflags.CF = (sum <= src);//无符号数用时钟来类比，之前的add不能转一圈，现在若CF=1,则至多能转一圈，达到相等；
	else
		cpu.eflags.CF = (sum <src);

}

	


uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
return __ref_alu_adc(src, dest, data_size);
   
#else
    	uint32_t sum=dest+src+cpu.eflags.CF;
	
	set_CF_adc(sum,dest,src,data_size);
	set_OF_add(sum,dest,src,data_size);//两个加数分四种情况去讨论，发现和原来的add并没有什么区别，以后出问题的话可以在更改；
	sum=set_return (sum,data_size);
	set_PF(sum);
	set_ZF(sum);
	set_SF(sum,data_size);
	
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

void set_CF_sub(uint32_t result,uint32_t dest,uint32_t src,size_t data_size)
{
	uint32_t a;
	dest=sign_ext(dest&(0XFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	a=dest<src;
	cpu.eflags.CF=a;
}
void set_OF_sub(uint32_t result, uint32_t src, uint32_t dest, size_t data_size) 
{
	switch(data_size) 
	{
	case 8:
	result = sign_ext(result&0xFF, 8);
	src = sign_ext(src & 0xFF, 8);
	dest = sign_ext(dest & 0xFF, 8);
	break;
	case 16:
	result = sign_ext(result&0xFFFF, 16);
	src = sign_ext(src & 0xFFFF, 16);
	dest = sign_ext(dest & 0xFFFF, 16);
	break;
	default: break;// do nothing
	}
	if(sign(src) != sign(dest))//只有两者符号不同时，才有可能溢出
	 {
		if(sign(src) == sign(result))//若溢出，则结果与减数符号一致
			cpu.eflags.OF = 1;
		else
			cpu.eflags.OF = 0;
	} 
	else 
	{
		cpu.eflags.OF = 0;
	}
	
}
uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{

#ifdef NEMU_REF_ALU
    
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t sum=dest-src;
	sum=set_return (sum,data_size);
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);
	set_CF_sub(sum,dest,src,data_size);
	set_OF_sub(sum,src,dest,data_size);
	return sum;
	
#endif
}

void set_CF_sbb(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	uint32_t a;
	dest=sign_ext(dest&(0XFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF)
	{
		a=dest<=src;//本来够减的不用借位，由于CF=1,而产生借位;
	}
	else
		a=dest<src;
	cpu.eflags.CF=a;
}
uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{

#ifdef NEMU_REF_ALU
    
	return __ref_alu_sbb(src, dest, data_size);
#else
	uint32_t sum=dest-src-cpu.eflags.CF;
	sum=set_return (sum,data_size);
	set_CF_sbb(sum,src,dest,data_size);
	set_OF_sub(sum,src,dest,data_size);
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);
	return sum;
#endif
}

void set_COF(uint32_t src,uint32_t dest, size_t data_size,uint64_t sum)
{
	cpu.eflags.CF=1;cpu.eflags.OF=1;
	switch(data_size)
	{
		case 8:sum&=(0xFF00);break;//保留高8位，为0则不溢出，否则溢出
			
		case 16:sum&=(0xFFFF0000);break;//保留高16位，低位置0
	
		case 32:sum&=0xFFFFFFFF00000000;break;//低32位置0

	}
	if(sum==0)
	{
		cpu.eflags.CF=0;cpu.eflags.OF=0;
	}
			

}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	src=set_return(src,data_size);
	dest=set_return(dest,data_size);//数据位数截断
	uint64_t src1=src,dest1=dest;//转换到64位，不然乘法时所得是先截断得到32位，再转换成64位
	uint64_t sum =dest1*src1;
	set_COF(src,dest,data_size,sum);//CF和OF一起设置
	/*set_ZF(sum);这些标志位没有定义
	set_PF(sum);
	set_SF(sum,data_size);*/
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	int64_t sum=(int64_t) dest*src;//imul对标志位不进行测试
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	  if(src==0)
	{	assert(0);return 0;
	}
	uint32_t sum=dest/src;
	return sum;//标志位没有定义
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	if(src==0)//除数为0,直接跳出
	{	assert(0);return 0;
	}
	int32_t sum=dest/src;
	return sum;//i386手册标志位没有定义
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	uint32_t sum=dest%src;
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	int32_t sum=dest%src;
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	dest=set_return(dest,data_size);//分别对dest,src进行截断
	src=set_return(src,data_size);
	uint32_t sum=dest&src;
	sum=set_return(sum,data_size);
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);//没有进行CF和OF的测试
	return sum;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	dest=set_return(dest,data_size);//分别对dest,src进行截断
	src=set_return(src,data_size);
	uint32_t sum=dest^src;
	sum=set_return(sum,data_size);
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);//没有进行CF和OF的测试
	return sum;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	dest=set_return(dest,data_size);//分别对dest,src进行截断
	src=set_return(src,data_size);
	uint32_t sum=dest|src;
	sum=set_return(sum,data_size);
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);//没有进行CF和OF的测试
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

void set_CF_sal(uint32_t dest,uint32_t src,size_t data_size) 
{
	int count=0;cpu.eflags.CF=0;//先将CF的值设置为0
	while(count<src)
	{
		dest = sign_ext(dest&(0xFFFFFFFF>>(32-data_size)), data_size);//符号扩展
		cpu.eflags.CF=sign(dest);//最高位移到CF，注意移位过程中CF是不断在更新的，对于OF，它则是移出的第一位；
		dest=dest<<1;//每次左移1位,别忘了赋值 
		count++;
	}
}
uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
    
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t sum=dest<<src;
	sum = set_return (sum,data_size);//不要忘了将返回值赋给结果sum
	set_CF_sal(dest,src,data_size);     
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);
	//这里没有对OF位进行设置
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}
uint32_t set_CF_shr(uint32_t src,uint32_t dest,size_t data_size) 
{
	src=set_return(src,data_size);//src进行截断，避免高于data_size位有无效数据
	dest=set_return(dest,data_size);//对dest进行截断，避免高位影响
	uint32_t sum=dest;//对dest进行扩展，保留符号位
	int count=0;cpu.eflags.CF=0;//先将CF的值设置为0
	while(count<src)
	{
		cpu.eflags.CF=sum%2;//最低位移到CF，注意移位过程中CF是不断在更新的，对于OF，它则是移出的第一位；
		sum>>=1;//每次除以2,别忘了赋值 
		count++;
	}
	sum = set_return (sum,data_size);//不要忘了将返回值赋给结果sum
	return sum;
}
uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	
	uint32_t sum;
	sum=set_CF_shr(src,dest,data_size);
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);
	//这里没有对OF位进行设置
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t set_CF_sar(uint32_t src,uint32_t dest,size_t data_size)
{
	src=set_return(src,data_size);//src进行截断，避免高于data_size位有无效数据
	dest=set_return(dest,data_size);//对dest进行截断，避免高位影响
	int32_t sum=sign_ext(dest,data_size);//对dest进行扩展，保留符号位
	int count=0;//计数
	while(count<src)
	{
		cpu.eflags.CF=sum%2;//右移，移出的低位到CF,低位对2取余就能得到
		sum>>=1;//第一次写的时候忽略了要把sum定义成带符号，而造成错误
		count++;
	}
	
	sum =sum&(0xFFFFFFFF>>(32-data_size));//截断，不要忘了将返回值赋给结果sum，
	return sum;
}
uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	int32_t sum;
	sum=set_CF_sar(src,dest,data_size); //考虑到符号位，定义和返回都是带符号类型 
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);
	//这里没有对OF位进行设置
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}




uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
    
	return __ref_alu_sal(src, dest, data_size);
#else
	uint32_t sum=dest<<src;
	sum = set_return (sum,data_size);//不要忘了将返回值赋给结果sum
	set_CF_sal(dest,src,data_size);   //这个函数写在shl之上
	set_ZF(sum);
	set_PF(sum);
	set_SF(sum,data_size);
	//这里没有对OF位进行设置
	return sum;
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}
