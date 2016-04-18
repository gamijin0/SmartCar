//===========================================================================
//文件名称：motor.h
//功能概要：motor驱动构件头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版    本：V2.0, 20150522
//===========================================================================

#ifndef MOTOR_H_               //防止重复定义（MOTOR_H_  开头)
#define MOTOR_H_
//包含头文件
#include "common.h"
#include "pwm.h"


//两路PWM电机组号
#define MOTOR1 0
#define MOTOR2 1

//电机模块加通道号
#define MOTOR1_PWM1   FTM0           // FTM0_CH4    //(PORTD|4)
#define MOTOR1_PWM2   FTM0           // FTM0_CH5    //(PORTD|5)
#define MOTOR2_PWM1   FTM0   		 // FTM0_CH2	//(PORTC|3)
#define MOTOR2_PWM2   FTM0 		   	 // FTM0_CH3	//(PORTC|4)

#define MOTOR1_PWM1_CH		FTMCH0
#define MOTOR1_PWM2_CH		FTMCH1
#define MOTOR2_PWM1_CH		FTMCH2
#define MOTOR2_PWM2_CH		FTMCH3

//电机PWM周期
#define MOTOR_PERIOD 1000 //电机PWM周期，周期1ms（1000表示1ms,见PWM.h）

//====================================================================
//函数名称：motor_init
//函数返回：无
//参数说明：motor:选择电机 ：MOTOR_1、MOTOR_2
//功能概要：电机初始化，根据传入参数选择要初始化的电机（例：MOTOR_1），然后根据宏定义的引脚（例：
//      MOTOR1_PWM1、MOTOR1_PWM2）和周期（MOTOR_PERIOD）初始化电机，初始占空比为0
//====================================================================
void motor_init(uint8_t motor);

//====================================================================
//函数名称：motor_set;
//函数返回：无
//参数说明：  motor:选择电机 ：MOTOR_1、MOTOR_2
//       duty：  占空比，控制车轮转速,
//       有正负 ：-PWM_ACCURACY~PWM_ACCURACY(在PWM.h中定义) ////方向
//功能概要：设置电机速度，根据电机选择motor参数以及占空比duty来设置对应舵机的PWM占空比
//====================================================================
void motor_set(uint8_t motor, int16_t duty);



#endif //防止重复定义（MOTOR_H_ 结尾)
