//===========================================================================
//文件名称：pwm.c
//功能概要：pwm底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2013-5-5   V3.0 李涛
//===========================================================================
#ifndef _PWM_H
#define _PWM_H

#include "common.h"
#include "gpio.h"

#define FTM0_IRQ_NO 17
#define PWM_ACCURACY 10000 //允许占空比(duty)范围为0~PWM_ACCURACY,精度至少为1
//FTM模块号
#define FTM0  0
#define FTM1  1
#define FTM2  2
//FTM通道号
#define FTMCH0  0
#define FTMCH1  1
#define FTMCH2  2
#define FTMCH3  3
#define FTMCH4  4
#define FTMCH5  5
#define FTMCH6  6
#define FTMCH7  7
//定义FTM通道号选择                     		  可用的端口_引脚
#define FTM0_CH0 (PORTC|1) // A3  C1
#define FTM0_CH1 (PORTC|2) // A4  C2
#define FTM0_CH2 (PORTC|3) // A5  C3
#define FTM0_CH3 (PORTC|4) // A6  C4
#define FTM0_CH4 (PORTD|4) // A7  D4
#define FTM0_CH5 (PORTD|5) // A0  D5
#define FTM0_CH6 (PORTD|6) // A1  D6
#define FTM0_CH7 (PORTD|7) // A2  D7

#define FTM1_CH0 (PORTA|12) //A8  A12  B0
#define FTM1_CH1 (PORTA|13) //A9  A13  B1

#define FTM2_CH0 (PORTA|1) // A10
#define FTM2_CH1 (PORTA|2) // A11

#define bus_clk_khz 50000

//=========================================================================
//函数名称：pwm_init
//功能概要：pwm模块初始化。
//参数说明：ftmModule_channel:模块号：0、1、2  通道号:0-6 详见pwm.h文件定义
//         period：周期 单位微秒（比如0.1ms为100,1ms为1000）
//         duty：占空比    0~PWM_ACCURACY(在PWM.h中定义)
//函数返回：无
//=========================================================================
uint8_t pwm_init(uint8_t ftmModule, uint8_t channel, uint32_t period, uint16_t duty);

//=========================================================================
//函数名称：pwm_set
//功能概要：设置pwm模块。
//参数说明：ftmModule_channel:模块号：0、1、2  通道号:0-6 详见pwm.h文件定义
//			period：周期 单位微秒（比如0.1ms为100,1ms为1000）
//			duty：占空比    0~PWM_ACCURACY(在PWM.h中定义)
//函数返回：无
//=========================================================================
uint8_t pwm_set(uint8_t ftmModule, uint8_t channel, uint32_t period, uint16_t duty);

#endif

//===========================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，不足之处，
//     欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏州大学飞思卡尔嵌入式中心（苏州华祥信息科技有限公司）
//技术咨询：0512-65214835  http://sumcu.suda.edu.cn
//业务咨询：0512-87661670,18915522016  http://www.hxtek.com.cn
