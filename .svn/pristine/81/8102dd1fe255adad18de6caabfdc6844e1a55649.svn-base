//==============================================================
//文件名称：control.h
//功能概要：PID控制源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//==============================================================

#include "control.h"

//============================================================================
//函数名称：speedPID
//函数参数：speedCount 采集的车速     AmSpeed 目标车速
//函数返回：返回类型为int16_t，速度单位毫米每秒(mm/s)
//功能概要：计算车速
//============================================================================

int16_t SpeedPID(int16_t speedCount,int16_t AmSpeed,uint8_t speedKP,uint8_t speedKI,uint8_t speedKD)
{
	extern uint8_t APWMflg ;

	static float Speed1_Err,SumErrSpeed;  //静态变量存储中间变量
	float Speed2_Err,Speed_EC;
	float Speed_P_Value,Speed_D_Value,KI ;

	int32_t  SpeedPWMOUT;
	int16_t  SpeedPWM16OUT ;

	if(APWMflg == 0)
	{
	  speedKP = 0 ;
	  speedKI = 0 ;
	  SumErrSpeed = 0 ;
	}

	Speed2_Err = Speed1_Err ;                //将上一次的偏差保存

	Speed1_Err = AmSpeed - speedCount  ;      //  计算新的偏差值

	Speed_EC = Speed1_Err - Speed2_Err ;      //  计算新的偏差变化值

	Speed_P_Value =  Speed1_Err * speedKP;///100 ;   //  增量式PID控制计算P调节量

	KI =  Speed1_Err * speedKI ;    //增量式PID控制计算I调节量

	KI /= 100;

	SumErrSpeed  += KI;

	Speed_D_Value =  Speed_EC   *  speedKD ;     //  增量式PID控制计算D调节量

	SpeedPWMOUT = (int32_t)(Speed_P_Value + SumErrSpeed + Speed_D_Value);//Speed_P_Value/10
	if(SpeedPWMOUT < KOUPLUSMIN )
	{
	SpeedPWMOUT = KOUPLUSMIN ;
	}
	else if(SpeedPWMOUT > KOUPLUSMAX)
	{
	SpeedPWMOUT = KOUPLUSMAX ;

	}

	SpeedPWM16OUT = (int16_t)SpeedPWMOUT ;

	return  SpeedPWM16OUT ;

}


