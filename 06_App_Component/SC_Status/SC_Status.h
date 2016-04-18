//===========================================================================
//文件名称：SC_Status.h
//功能概要：SC_Status驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版    本：V1.0, 20151110
//===========================================================================

#ifndef SENSER_H_
#define SENSER_H_
//包含头文件
#include "common.h"

//AD通道,通道对应引脚硬件连接，对于不同芯片，可查看芯片手册修改通道对应的引脚号
#define EMS_0   9    //传感器0使用通道9，对应引脚PTB1
#define EMS_1   3    //传感器1使用通道12，对应引脚PTE22
#define EMS_2   13   //传感器2使用通道3，对应引脚PTB3
#define EMS_3   4    //传感器3使用通道23，对应引脚PTE21
#define EMS_4   23   //传感器4使用通道13，对应引脚PTE30
#define EMS_5   12   //传感器5使用通道4，对应引脚PTB2

//各路AD最大值
#define AD0_MAX  340
#define AD1_MAX  370
#define AD2_MAX  600
#define AD3_MAX  370
#define AD4_MAX  300
#define AD5_MAX  370

//各路AD最小值
#define AD0_MIN 0
#define AD1_MIN 81
#define AD2_MIN 0
#define AD3_MIN 8
#define AD4_MIN 0
#define AD5_MIN 52

//AD最大最小值数组
int max_AD[6];   //最大采样值数组
int min_AD[6];   //最小采样值数组

//采样数组
int AD_EMS[6];         //用于存放归一化后的6路传感器的值，传感器1-6分别对应AD_EMS[0]-AD_EMS[5]

//=================================================================================
//函数名称：SC_init
//函数返回：无
//参数说明： accurary采样精度:单端8-12-10-16；差分9-13-11-16
//         HardwareAverage硬件滤波：sample4/sample8/sample16/sample32
//功能概要：车模状态相关参数初始化，ADC初始化且统一使用单端输入模式。需使用ADC构件中
//         的函数，内部函数按照本实验室要求经封装。
//=================================================================================
void SC_init(int MoudelNumber);

//===================================================================================
//函数名称： SC_EMS_Get
//函数返回：无
//参数说明：无
//功能概要：采集6路传感器的值，并进行归一化处理，存放到全局数组AD_EMS中，考虑到精度，
//         归一化后各路AD值 范围是0-1000
//===================================================================================
void SC_EMS_Get(uint8_t accurary,uint8_t N);

//===================================================================================
//函数名称：SC_Status_Get
//函数返回：车模在跑道上的相对偏离程度，范围-100~+100
//参数说明：X为指向存放各路传感器AD值的数组的指针
//功能概要：该函数根据EMS_GET函数获得的6路归一化后的传感器值，判断车模在跑道上偏离程度
//===================================================================================
int SC_Status_Get(int *X);

#endif    //SENSER_H_

