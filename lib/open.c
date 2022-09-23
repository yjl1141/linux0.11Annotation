/*
 *  linux/lib/open.c
 *
 *  (C) 1991  Linus Torvalds
 */

#define __LIBRARY__
#include <unistd.h>
#include <stdarg.h>

int open(const char * filename, int flag, ...)
{
	register int res;
	va_list arg;//char*

	va_start(arg,flag);//arg指向栈上flag后第一个参数
	__asm__("int $0x80"   //系统调用
		:"=a" (res)      //res赋给eax
		:"0" (__NR_open),"b" (filename),"c" (flag),  //eax=5，ebx=filename ecx=flag，edx=
		"d" (va_arg(arg,int))); //d=第一个参数，arg++
	if (res>=0)
		return res;
	errno = -res;
	return -1;
}
