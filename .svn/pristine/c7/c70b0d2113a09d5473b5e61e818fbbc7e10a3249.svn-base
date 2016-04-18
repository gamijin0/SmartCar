//===========================================================================
//文件名称：arm_cm4.h
//功能概要：ARM Cortex-M4内核提供功能定义的头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-10-09   V1.0     初始版本
//===========================================================================

#ifndef __ARM_CM4_H
#define __ARM_CM4_H

// 用于中断的宏定义
#define ARM_INTERRUPT_LEVEL_BITS          4   //中断优先级宏定义
#define ENABLE_INTERRUPTS  asm(" CPSIE i");    //开总中断
//CPSIE,Center Process System Interrupt Enable,中央处理系统中断使能
//实现原理：将PRIMASK(Primary Exception Mask Register)/FAULTMASK(一位的)置0，即为开中断
#define DISABLE_INTERRUPTS asm(" CPSID i");    //关总中断

//#include "psptypes.h"
typedef unsigned char		uint_8_t;
typedef unsigned short int  uint_16_t;
typedef unsigned long int   uint_32_t;
/*
#define _PTR_      *  // 定义指针类型关键字

// 重定义基本数据类型
// 在如下每个系列中，依次定义：
//     有符号类型、无符号类型、不优化有符号类型和不优化无符号类型
// 字符系列
typedef          char         _PTR_   char_ptr;
typedef unsigned char  uchar, _PTR_   uchar_ptr;
typedef volatile char         _PTR_   vchar_ptr;
typedef volatile unsigned char  vuchar, _PTR_   vuchar_ptr;
// 8位数系列
typedef signed   char   int_8, _PTR_   int_8_ptr;
typedef unsigned char  uint_8_t, _PTR_  uint_8_t_ptr;
typedef volatile signed   char   vint_8, _PTR_   vint_8_ptr;
typedef volatile unsigned char  vuint_8_t, _PTR_  vuint_8_t_ptr;
// 16位数系列
typedef          short int_16, _PTR_  int_16_ptr;
typedef unsigned short uint_16_t, _PTR_ uint_16_t_ptr;
typedef volatile          short vint_16, _PTR_  vint_16_ptr;
typedef volatile unsigned short vuint_16_t, _PTR_ vuint_16_t_ptr;
// 32位数系列
typedef          long  int_32, _PTR_  int_32_ptr;
typedef unsigned long  uint_32_t, _PTR_ uint_32_t_ptr;
typedef volatile          long  vint_32, _PTR_  vint_32_ptr;
typedef volatile unsigned long  vuint_32_t, _PTR_ vuint_32_t_ptr;
*/

//============================================================================
//函数名称：stop
//函数返回：无
//参数说明：无
//功能概要：设置CPU为STOP模式
//============================================================================
void stop (void);

//============================================================================
//函数名称：wait
//函数返回：无
//参数说明：无
//功能概要：设置CPU为WAIT模式
//============================================================================
void wait (void);

//============================================================================
//函数名称：write_vtor
//函数返回：vtor：要更改的值
//参数说明：无
//功能概要：更改中断向量表偏移寄存器的值 
//============================================================================
void write_vtor (uint_16_t vtor);

//============================================================================
//函数名称：enable_irq
//函数返回：无  
//参数说明：irq：irq号
//功能概要：使能irq中断 
//============================================================================
void enable_irq (uint_16_t irq);

//============================================================================
//函数名称：disable_irq
//函数返回：无      
//参数说明：irq：irq号
//功能概要：禁止irq中断 
//============================================================================
void disable_irq (uint_16_t irq);

//============================================================================
//函数名称：set_irq_priority
//函数返回：无      
//参数说明：irq：irq号         											   
//         prio：优先级
//功能概要：设置irq中断和优先级 
//============================================================================
void set_irq_priority (uint_16_t irq, uint_16_t prio);


#endif
