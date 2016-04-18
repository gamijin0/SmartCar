/****************************************************************************
 * Copyright (c) 2013 苏州大学飞思卡尔实验室(版权声明)
 * All rights reserved.
 *
 * @file     sysint.h
 * @brief    sysint构件头文件
 * @version  V1.00
 * @date     2013年10月16日
 * @note     修订说明：V1.00 实现了sysint基本驱动
 ***************************************************************************/	 
#ifndef __SYSINT_H__
#define __SYSINT_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "MK60DZ10.h"
#include "common.h"
 
#define USE_FULL_ASSERT          //是否启动参数检测机制，如果启用需要用户实现 assert_failed函数
#define DEBUG_PRINT              //是否用串口打印调试信息

#ifndef NULL
	#define NULL 0
#endif

 //宏定义串口使用的时钟
 #define  CORE_CLK_KHz     96000   //芯片内核时钟频率，kHz
 #define  BUS_CLK_KHz      48000   //芯片总线时钟频率，Khz

 //处理器信息及主频信息结构
 typedef struct
 {
 	uint8_t FamilyType;    //Kinetis系列家族类型号 
 	uint8_t ResetState;    //复位原因
 	uint8_t SiliconRev;    //SiliconRev
 	uint16_t PinCnt;       //引脚数量
 	uint32_t PFlashSize;   //PFlash大小
 	uint32_t FlexNVMSize;  //FlexNVM大小
 	uint32_t RAMSize;      //RAM大小
 	uint32_t CoreClock;    //内核时钟
 	uint32_t BusClock;     //总线时钟
 	uint32_t FlexBusClock; //FlexBus时钟
 	uint32_t FlashClock;   //Flash时钟
 } CPUInfoType_t;
 extern CPUInfoType_t CPUInfo;
 
//MCG时钟源选择
#define ClockSource_IRC     		((uint8_t)0x0)
#define ClockSource_EX50M  			((uint8_t)0x5)
#define ClockSource_EX4M			((uint8_t)0x6)

//参数检测宏
#define IS_CLOCK_SELECT(CLOCK_TYPE)   (((CLOCK_TYPE) ==    CoreClock_100M)||   \
									   ((CLOCK_TYPE) ==    CoreClock_200M)||   \
									   ((CLOCK_TYPE) ==    CoreClock_96M) ||   \
									   ((CLOCK_TYPE) ==    CoreClock_72M) ||   \
									   ((CLOCK_TYPE) ==    CoreClock_64M) ||   \
									   ((CLOCK_TYPE) ==    CoreClock_48M))
//NVIC中断分组选择
#define NVIC_PriorityGroup_0         ((uint32_t)0x7) // 0 bits for pre-emption priority   4 bits for subpriority                                                
#define NVIC_PriorityGroup_1         ((uint32_t)0x6) // 1 bits for pre-emption priority   3 bits for subpriority                                                 
#define NVIC_PriorityGroup_2         ((uint32_t)0x5) // 2 bits for pre-emption priority   2 bits for subpriority                                                   
#define NVIC_PriorityGroup_3         ((uint32_t)0x4) // 3 bits for pre-emption priority   1 bits for subpriority                                                  
#define NVIC_PriorityGroup_4         ((uint32_t)0x3) // 4 bits for pre-emption priority   0 bits for subpriority 
  
//参数检查
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
                                       ((GROUP) == NVIC_PriorityGroup_1) || \
                                       ((GROUP) == NVIC_PriorityGroup_2) || \
                                       ((GROUP) == NVIC_PriorityGroup_3) || \
                                       ((GROUP) == NVIC_PriorityGroup_4))


#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)
#define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

//VETOR_OFFSET检测宏
#define IS_VECTOR_OFFSET(OFFSET)  ((OFFSET) % 4 == 0)

//void assert_failed(uint8_t* file, uint32_t line);
 //参数检测器宏
 #define IS_CLOCK_OPTION(SOURCE)	   (((SOURCE)  == ClockSource_IRC)  || \
                                        ((SOURCE) == ClockSource_EX50M) || \
                                        ((SOURCE) == ClockSource_EX4M))
 //MCG时钟输出选择
 #define CoreClock_200M      		((uint8_t)0x13) //最高100M频率 200M属于为小车设计的超频
 #define CoreClock_100M				((uint8_t)0x12)
 #define CoreClock_96M				((uint8_t)0x11)
 #define CoreClock_72M				((uint8_t)0x10)
 #define CoreClock_64M				((uint8_t)0x9)
 #define CoreClock_48M				((uint8_t)0x8)
 
 /** 
  * @brief  设置/更改系统主频。
  * @param  ClockOption  时钟源选择,选择如下：
  * 		                ClockSource_IRC    : 内部时钟源
  * 		                ClockSource_EX4M   : 外部4M晶振
  * 		                ClockSource_EX50M  : 外部50M晶振
  * @param  CoreClock    希望得到的内核频率
  * 						CoreClock_48M  : CoreClock = 48M
  * 						CoreClock_64M  : CoreClock = 64M
  * 						CoreClock_72M  : CoreClock = 72M
  * 						CoreClock_96M  : CoreClock = 96M
  * 						CoreClock_100M : CoreClock = 100M					
  * @retval None
  * 
  * 使用该函数来选择时钟源经过倍频得到希望的内核时钟。
  */
void SystemClockSetup(uint8_t ClockOption,uint16_t CoreClock); 

//void SystemSoftReset(void);                                    
void SetVectorTable(uint32_t offset);                          
void GetCPUInfo(void);
void sys_pll_init(void);
void sys_pll_init1(void);
#ifdef __cplusplus
}
#endif

#endif

