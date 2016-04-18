//===========================================================================
//文件名称：motor.c
//功能概要：motor驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版    本：V2.0, 20150522
//===========================================================================

//====================================================================
//硬件连接说明：
//==================================================================
#include "motor.h"

//====================================================================
//函数名称：motor_init
//函数返回：无
//参数说明：motor:选择电机 ：MOTOR_1、MOTOR_2
//功能概要：电机初始化，根据传入参数选择要初始化的电机（例：MOTOR_1），然后根据宏定义的引脚（例：
//      MOTOR1_PWM1、MOTOR1_PWM2）和周期（MOTOR_PERIOD）初始化电机，初始占空比为0
//====================================================================
void motor_init(uint8_t motor)
{
	//根据带入参数motor，决定选择电机1还是电机2
	if(motor == MOTOR1)  //初始化电机1
	{
		pwm_init(MOTOR1_PWM1, MOTOR1_PWM1_CH, MOTOR_PERIOD, 0);
		pwm_init(MOTOR1_PWM2, MOTOR1_PWM2_CH, MOTOR_PERIOD, 0);
	}
	else if(motor == MOTOR2)//初始化电机2
	{
		pwm_init(MOTOR2_PWM1, MOTOR2_PWM1_CH, MOTOR_PERIOD, 0);
		pwm_init(MOTOR2_PWM2, MOTOR2_PWM2_CH, MOTOR_PERIOD, 0);
	}

}

//====================================================================
//函数名称：motor_set;
//函数返回：无
//参数说明：  motor:选择电机 ：MOTOR_1、MOTOR_2
//       duty：  占空比，控制车轮转速,
//       有正负 ：-PWM_ACCURACY~PWM_ACCURACY(在PWM.h中定义) ////方向
//功能概要：设置电机速度，根据电机选择motor参数以及占空比duty来设置对应舵机的PWM占空比
//====================================================================
void motor_set(uint8_t motor, int16_t duty)
{
	//根据带入参数motor，决定设置电机1还是电机2
	if(motor == MOTOR1)//设置电机1
	{
		//根据带入参数duty，决定电机正转还是反转
		if(duty >= 0) //电机正转
		{
			 pwm_set(MOTOR1_PWM1,MOTOR1_PWM1_CH, MOTOR_PERIOD,duty);
			 pwm_set(MOTOR1_PWM2,MOTOR1_PWM2_CH, MOTOR_PERIOD,0);
		}
		else//电机反转
		{
			pwm_set(MOTOR1_PWM1,MOTOR1_PWM1_CH,MOTOR_PERIOD,0);
			pwm_set(MOTOR1_PWM2,MOTOR1_PWM2_CH,MOTOR_PERIOD,-duty);
		}
	}
	else if(motor == MOTOR2)//设置电机2
	{
		if(duty >= 0)//电机正转
		{
			 pwm_set(MOTOR2_PWM1,MOTOR2_PWM1_CH, MOTOR_PERIOD,duty);
			 pwm_set(MOTOR2_PWM2,MOTOR2_PWM2_CH, MOTOR_PERIOD,0);
		}
		else//电机反转
		{
			pwm_set(MOTOR2_PWM1,MOTOR2_PWM1_CH, MOTOR_PERIOD,0);
			pwm_set(MOTOR2_PWM2,MOTOR2_PWM2_CH, MOTOR_PERIOD,-duty);
		}
	}
}



