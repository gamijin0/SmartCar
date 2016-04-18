/*HEADER**********************************************************************
*
* Copyright 2011 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*    This file contains the exception vector table and flash configuration.
*
*
*END************************************************************************/

//#include <includes.h>
#include "vectors.h"
typedef unsigned long int   uint32_t;



extern uint32_t __vector_table[];
extern unsigned long _estack;
extern void __thumb_startup(void);

/* Configuration values for flash controller */
#define CONFIG_1        (uint32_t)0xffffffff
#define CONFIG_2        (uint32_t)0xffffffff
#define CONFIG_3        (uint32_t)0xffffffff
#define CONFIG_4        (uint32_t)0xfffffffe



void (* const InterruptVector[])() __attribute__ ((section(".vectortable"))) =
{
    /* Processor exceptions */
	VECTOR_000,           //初始化SP
	VECTOR_001,           //初始化PC
	VECTOR_002,
	VECTOR_003,
	VECTOR_004,
	VECTOR_005,
	VECTOR_006,
	VECTOR_007,
	VECTOR_008,
	VECTOR_009,
	VECTOR_010,
	VECTOR_011,
	VECTOR_012,
	VECTOR_013,
	VECTOR_014,
	VECTOR_015,
	VECTOR_016,
	VECTOR_017,
	VECTOR_018,
	VECTOR_019,
	VECTOR_020,
	VECTOR_021,
	VECTOR_022,
	VECTOR_023,
	VECTOR_024,
	VECTOR_025,
	VECTOR_026,
	VECTOR_027,
	VECTOR_028,
	VECTOR_029,
	VECTOR_030,
	VECTOR_031,
	VECTOR_032,
	VECTOR_033,
	VECTOR_034,
	VECTOR_035,
	VECTOR_036,
	VECTOR_037,
	VECTOR_038,
	VECTOR_039,
	VECTOR_040,
	VECTOR_041,
	VECTOR_042,
	VECTOR_043,
	VECTOR_044,
	VECTOR_045,
	VECTOR_046,
	VECTOR_047,
	VECTOR_048,
	VECTOR_049,
	VECTOR_050,
	VECTOR_051,
	VECTOR_052,
	VECTOR_053,
	VECTOR_054,
	VECTOR_055,
	VECTOR_056,
	VECTOR_057,
	VECTOR_058,
	VECTOR_059,
	VECTOR_060,
	VECTOR_061,
	VECTOR_062,
	VECTOR_063,
	VECTOR_064,
	VECTOR_065,
	VECTOR_066,
	VECTOR_067,
	VECTOR_068,
	VECTOR_069,
	VECTOR_070,
	VECTOR_071,
	VECTOR_072,
	VECTOR_073,
	VECTOR_074,
	VECTOR_075,
	VECTOR_076,
	VECTOR_077,
	VECTOR_078,
	VECTOR_079,
	VECTOR_080,
	VECTOR_081,
	VECTOR_082,
	VECTOR_083,
	VECTOR_084,
	VECTOR_085,
	VECTOR_086,
	VECTOR_087,
	VECTOR_088,
	VECTOR_089,
	VECTOR_090,
	VECTOR_091,
	VECTOR_092,
	VECTOR_093,
	VECTOR_094,
	VECTOR_095,
	VECTOR_096,
	VECTOR_097,
	VECTOR_098,
	VECTOR_099,
	VECTOR_100,
	VECTOR_101,
	VECTOR_102,
	VECTOR_103,
	VECTOR_104,
	VECTOR_105,
	VECTOR_106,
	VECTOR_107,
	VECTOR_108,
	VECTOR_109,
	VECTOR_110
};

// 默认终端服务例程函数
void default_isr(void){

}
