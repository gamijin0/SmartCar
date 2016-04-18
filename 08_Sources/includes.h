//============================================================================
//文件名称：includes.h
//功能概要：应用工程总头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2012-11-12  V2.0
//          2014-11-9  V3.0
//============================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "gpio.h"
#include "light.h"
#include "uart.h"
#include "sysint.h"
#include "pit.h"
#include "adc.h"
#include "pwm.h"
#include "motor.h"
#include "speed.h"
#include "GyroAcce.h"
#include "control.h"

//定义全局变量
uint16_t count;          //记录脉冲个数
float OutData[4];
static float g = 9.794;			//上海重力加速度,单位m/s^2


//定义小灯闪烁频率
#define RUN_COUNTER_MAX   1500000ul

//定义使用的调试号
#define UART_TEST  UART_5


#endif
