/* 
 * CS:APP Data Lab 
 * 
 * <徐佳美181860117>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
	//用折半查找
	int result=0;
	int num1=!!((x>>16)^0x0);// 判断前16位有没有1
	//num1=1,移24位，=0,移8位
	int num2=!!((x>>(8+(num1<<4)))^0x0);
	int a=4+(num2<<3)+(num1<<4);
	//如果num1,2,=00,shift4,==01,shift 12,==10,shift,20,==11,shift28
       int num3=!!((x>>a)^0x0);
	int b=(num1<<4)+(num2<<3)+(num3<<2)+2;
	//num1,2,3==000,shift 2;==001,shift 6;......
	int num4=!!((x>>b)^0x0);
	int c=(num1<<4)+(num2<<3)+(num3<<2)+(num4<<1)+1;
	int num5=!!((x>>c)^0x0);
	int d=(num1<<4)+(num2<<3)+(num3<<2)+(num4<<1)+num5;
	int e=!!(x^0);//x==0,e=0,x!=0,e=1;
	result=e<<d;
	return result;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int a,e,result;// 注意声明语句必须放在所有未声明语句之前；
	// 0&num=0;-1&num=num;
	e = !!(x ^ 0);//x==0,e=0,x!=0,e=1
	a=!e;
	a=~a+1;//last e=0,now a=-1;last e=1,now a =0;
	e=~e+1;//last e=0,now e=0;last e=1,now e=-1;
	result=(e&y)+(a&z);//注意加上括号
  	return result;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
	int negx=~x+1;//利用补码正数和负数的特殊性(按位取反再加1），与操作后只有最低位的1被保留
	int newx=x&negx;
	return newx;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
	int result = (x >> 15);//如果是正数，16-31位都为0,负数则为1
	result = !((result>>16)^result);//前者是符号位
  	return result;
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
	int a1=0x49,a2=0x24,a3=0x92;//八格为1单位处理
	int result=(a1<<24)+(a2<<16)+(a3<<8)+a1;
 	return result;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
	//1 byte=8 bit
	int result,count=n<<3,t1,t2;
	t1= (x >> count) & 0xff;//取出要删去的字节
	t2=(c<<count);//要加入的
	t1=~t1+1;//因为是要减去所以取反
	result=x+(t1<<count)+t2;
  	return  result;
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
	int a=!(x^y);
       return a;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
	int a,c,d,e;// 注意声明语句必须放在所有未声明语句之前；
	a = x >> 31;//取到符号位
	e = !(x ^ 0);//防止其他高位的干扰
	 c = (~(0x0));//c=-1
	d = (!a) & (!e);
	c=c+e+d+d;
	return c;
    
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
	int result,frac;
	result=(x>>1)+(x>>3);//整数部分，5/8=1/2+1/8
	frac = ((((x & 1) << 2) + (x & 7))&15);//小数部分0.x1,0.x3x2x1;把他们相加的和变成4位bit,相加后小数点在第一位后，后面还有三位
       return result+((frac >> 3) & 1) + (  (!!(frac & 7))  &   (result >> 31)  );//和frac,小数点前一位是要直接加进去的，小数点后一位要根据符号
	//如果是正数，根据int取下整，直接舍掉;如果是负数，且小数位有值，说明之前多了1,负数加1,真值减1

}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
	int result,A,B,C,D;//1 bite = 8bit
	A=x&0xff;//1-8 bit
	x>>=8;
	B=x&0xff;//9-16
	x>>=8;
	C=x&0xff;//17-24
	x>>=8;
	D=x&0xff;//25-32
	result=(A<<24)|(B<<16)|(C<<8)|D;
  	return result;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
	//f2i =float to int把浮点数转换成整型
	int exp,exp_sig,frac,frac2;//定义阶码，阶，尾数，尾数对应的真值
	unsigned is_nan_inf= uf & 0x7fffffff;//判断是否是nan,inf
	unsigned sign=uf&0x80000000;//得到符号位
	if((is_nan_inf> 0x7f800000)||(is_nan_inf>0x7f000000) )//是nan或者无穷
		return 0x80000000u;
	//计算该浮点数的值
	 exp=uf&0x7f800000;//得到阶码，注意后23位为尾数域
  	 frac=uf&0x007fffff;//得到尾数
  	 frac2=frac+0x008fffff;//尾数对应的真值
  	 exp_sig=((exp>>23)-127);//32位 int的偏置常数为127
  	 if(exp==0)//阶码为0,真值为0
   			 return 0;
  	 else if(exp_sig<=-1&&exp_sig>=-126)//数字太小了，转成int之后被舍掉，真值为0
    			return 0;
 	 else if(exp==31&&frac==0&&sign!=0)//超出负int
          		return 0x80000000u;
 	 else if(exp_sig>=31)//超出正int的最大值
   		       return 0x80000000u;//超出int表示范围
  	else if(exp_sig<=23)
   		frac2=frac2>>(23-exp);
  	else
   		frac2=frac2<<(exp-23);
  	if(sign==0)
    		return frac2;
  	else
    		return -frac2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	unsigned is_nan_inf= uf & 0x7fffffff;//为方便之后判断是正无穷还是负无穷，去掉了符号位
	unsigned num = uf & 0x7f800000;//去除尾数域
	unsigned sign = uf & 0x80000000;//确定符号位
	if(is_nan_inf> 0x7f800000) 
		return uf;//判断是不是nan,即阶码为全1,尾数不为0
	else if(is_nan_inf> 0x7f000000) 
		return sign + 0x7f800000;//判断是否无穷，即阶码全为1,尾数为0
	else if(num == 0) 
		return sign + (uf << 1);
	else return uf + 0x800000;//已经是规格化数，加上隐藏位1


}
