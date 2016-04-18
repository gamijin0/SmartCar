/* CodeWarrior ARM Runtime Support Library

 * Copyright 閿燂拷012 Freescale Semiconductors. All rights reserved.

 *

 * $Date: 2013/02/08 07:14:44 $

 * $Revision: 1.6 $

 */
/*
 *	__arm_start.c	-	entry-point for ARM programs
 *
 */
#include <string.h>

#include <stdlib.h>

//#include <runtime_configuration.h>

#include <mk60dz10.h>
#include <sysint.h>

//_EWL_BEGIN_EXTERN_C

static char *argv[] = { 0 };

//#if __GNUC__
//
//#define __call_static_initializers __init_cpp
//
//#endif

//extern void __call_static_initializers(void);

extern int main(int, char **);

extern void __init_hardware();

extern void __init_user();
//从runtime_congfig文件中拷贝过来
#ifndef SUPPORT_ROM_TO_RAM
#define SUPPORT_ROM_TO_RAM   1
#endif

#ifndef SUPPORT_SEMIHOST_ARGC_ARGV
#define SUPPORT_SEMIHOST_ARGC_ARGV 0
#endif
//从runtime_congfig文件中拷贝过来
//#if SUPPORT_ROM_TO_RAM

//extern void __copy_rom_sections_to_ram(void);

//extern char __S_romp[];

//#endif

static void zero_fill_bss(void)

{
	extern char __START_BSS[];
	extern char __END_BSS[];
	memset(__START_BSS, 0, (__END_BSS - __START_BSS));
}
extern uint32_t __vector_table[];
void gpio_io_init( void )
{
    /* Enable clock gating to all ports */
    SIM_SCGC5 |=   SIM_SCGC5_PORTA_MASK \
                 | SIM_SCGC5_PORTB_MASK \
                 | SIM_SCGC5_PORTC_MASK \
                 | SIM_SCGC5_PORTD_MASK \
                 | SIM_SCGC5_PORTE_MASK;
}
void wdog_disable1(void)
{  
	WDOG_MemMapPtr reg;
	
	reg = WDOG_BASE_PTR;
    /* unlock watchdog */
    reg->UNLOCK = 0xc520;
    reg->UNLOCK = 0xd928;
    /* disable watchdog */
    reg->STCTRLH &= ~(WDOG_STCTRLH_WDOGEN_MASK);
}

/* format of the ROM table info entry ... */
typedef struct RomInfo {
	unsigned long	Source;
	unsigned long	Target;
	unsigned long 	Size;
} RomInfo;

extern RomInfo __S_romp[] __attribute__((weak));		/* linker defined symbol */

/*
 * Routine to flush cache follow the ROM to RAM copy
 */
void __flush_cache(unsigned long dst, unsigned long size)
{
	//TBD
}


/*
 *	Routine to copy a single section from ROM to RAM ...
 */
void __copy_rom_section(unsigned long dst, unsigned long src, unsigned long size)
{
	unsigned long len = size;

	const int size_int = sizeof(int);
	const int mask_int = sizeof(int)-1;

	const int size_short = sizeof(short);
	const int mask_short = sizeof(short)-1;

	const int size_char = sizeof(char);

	if( dst == src || size == 0)
	{
		return;
	}


	while( len > 0)
	{

		if( !(src & mask_int) && !(dst & mask_int) && len >= size_int)
		{
			*((int *)dst)  = *((int*)src);
			dst += size_int;
			src += size_int;
			len -= size_int;
		}
		else if( !(src & mask_short) && !(dst & mask_short) && len >= size_short)
		{
			*((short *)dst)  = *((short*)src);
			dst += size_short;
			src += size_short;
			len -= size_short;
		}
		else
		{
			*((char *)dst)  = *((char*)src);
			dst += size_char;
			src += size_char;
			len -= size_char;
		}
	}
}

/*
 *	Routine that copies all sections the user marked as ROM into
 *	their target RAM addresses ...
 *
 *	__S_romp is defined in the linker command file
 *  It is a table of RomInfo
 *	structures.  The final entry in the table has all-zero
 *	fields.
 */
void __copy_rom_sections_to_ram(void)
{

	int				index;

	if (__S_romp == 0L) return;

	/*
	 *	Go through the entire table, copying sections from ROM to RAM.
	 */
	for (index = 0;
		 __S_romp[index].Source != 0 ||
		 __S_romp[index].Target != 0 ||
		 __S_romp[index].Size != 0;
		 ++index)
	{
		__copy_rom_section( __S_romp[index].Target,
							__S_romp[index].Source,
							__S_romp[index].Size );

		__flush_cache( __S_romp[index].Target, __S_romp[index].Size);


	}
}

void __init_hardware()
{
	SCB_VTOR = (uint32_t)__vector_table; /* Set the interrupt vector table position */
}

void __thumb_startup(void)
{
	//设置看门狗
    wdog_disable1();
    //设置端口时钟门控
    gpio_io_init();
	//
    __init_hardware();
    //初始化全局变量
	zero_fill_bss();
	//拷贝ROM至RAM
#if SUPPORT_ROM_TO_RAM
	if (__S_romp != 0L)
		__copy_rom_sections_to_ram();
#endif
	//静态变量初始化
//	__call_static_initializers();
	//初始化用户变量
//	__init_user();
	//设置系统时钟
	SystemClockSetup(ClockSource_EX50M,CoreClock_96M);
	//sys_pll_init1();
	//进入主程序Main
	exit(main(0, argv));
	//	should never get here
	while (1);
}


//_EWL_END_EXTERN_C

