//==============================================================
//文件名称：control.h
//功能概要：PID控制头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//==============================================================

#ifndef CONTROL_H_
#define CONTROL_H_

#include "common.h"    //包含公共要素头文件

/**********************
 * PID 参数 详细 参考 .c文件 有详细注释
 *********************/
#define  KPPLUSMAX      (170)
#define  KPNEGATIVEMAX  (-170)
#define  KIPLUSMAX      (170)
#define  KINEGATIVEMAX  (-170)
#define  KDPLUSMAX      (170)
#define  KDNEGATIVEMAX  (-170)
#define  KWPLUSMAX      (170)
#define  KWNEGATIVEMAX  (-170)
#define  KOUPLUSMAX     (8000)
#define  KOUPLUSMIN     (-8000)

//============================================================================
//函数名称：speedPID
//函数参数：speedCount 采集的车速     AmSpeed 目标车速
//函数返回：返回类型为int16_t，速度单位毫米每秒(mm/s)
//功能概要：计算车速
//============================================================================

int16_t SpeedPID(int16_t speedCount,int16_t AmSpeed,uint8_t speedKP,uint8_t speedKI,uint8_t speedKD);


#endif
