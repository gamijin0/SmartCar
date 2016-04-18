//============================================================================
//文件名称：common.h
//功能概要：公共元素头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2012-10-30  V2.0
//============================================================================
#ifndef __COMMON_H
#define __COMMON_H

// 包含头文件
#include <stdint.h>
#include <stdbool.h>
#include <mk60dz10.h>
#include <arm_cm4.h>
#include <sysint.h>
//#include <null.h>
#ifndef NULL
	#define NULL 0L
#endif

static float PI = 3.141593;		//π

// 2.2 用于中断的宏定义
#define ARM_INTERRUPT_LEVEL_BITS  4       // 中断优先级宏定义
#define EnableInterrupts  asm(" CPSIE i"); // 开总中断
#define DisableInterrupts asm(" CPSID i"); // 关总中断

// 置位、清位、获得寄存器一位的状态
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    //置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  //清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  //获得寄存器一位的状态

// 临界区访问函数
//=========================================================================
//函数名称：init_critical
//参数说明：无
//函数返回：无
//功能概要：初始化临界区访问控制
//=========================================================================
void  init_critical(void);

//=========================================================================
//函数名称：enter_critical
//参数说明：无
//函数返回：无
//功能概要：进入临界区
//=========================================================================
void  enter_critical(void);

//=========================================================================
//函数名称：exit_critical
//参数说明：无
//函数返回：无
//功能概要：离开临界区
//=========================================================================
void  exit_critical(void);

#endif
