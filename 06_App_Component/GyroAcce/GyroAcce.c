//==============================================================
//文件名称：GyroAcce.c
//功能概要：陀螺仪、加速度传感器源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//==============================================================
#include "GyroAcce.h"

//==============================================================
//函数名称：GyroAcce_Init
//函数返回：无
//参数说明：无
//功能概要：陀螺仪、加速度传感器初始化。调用AD构件完成对陀螺仪、加速
//度传感器的MCU采样引脚的初始化，无需参数。
//==============================================================
void GyroAcce_init(void)
{
	adc_init(1) ; //PTB4、PTB6初始化
}

//==============================================================
//函数名称：GyroAcce_getAD
//函数返回：无
//参数说明：ADValue存放陀螺仪、加速度传感器采样的AD数据
//功能概要：获取陀螺仪、加速度传感器AD数据。调用AD构件完成对陀螺仪、
//加速度传感器的MCU采样引脚的电平采样。
//==============================================================
uint8_t GyroAcce_getAD(uint16_t *ADValue, uint8_t Count)
{
	 *ADValue       = adc_ave(1,10,12,16) ;    //PTB4		//Z轴加速度
     *(ADValue + 1) = adc_ave(1,12,12,16) ;    //PTB6		//X轴角速度

     return (Count + 16);
}

//==============================================================
//函数名称：GyroAccePHYToAngle
//函数返回：无
//参数说明： float *   GyroAngle，存放陀螺仪角速度的指针
//          float *   AcceValue，存放加速度传感器加速度的指针
//          float *   car_Angle，存放车模倾角的数组指针
//功能概要：利用卡尔曼滤波把角速度、加速度转成车模倾角。
//==============================================================
void GyroAccePHYToAngle(float *GyroAngle,float *AcceValue,
		float *car_Angle)
{
	float dt=0.005;	//0.005
	static float P[2][2] = {{ 1, 0 },{ 0, 1 }};
	static float Pdot[4] ={0,0,0,0};
	static const char C_0 = 1;
	static float q_bias,angle_err,PCt_0,PCt_1,EE,K_0,K_1,t_0,t_1;

	car_Angle[0]+=(*GyroAngle-q_bias) * dt;//先验估计

	// Pk-' 先验估计误差协方差的微分
	Pdot[0]=Q_angle - P[0][1] - P[1][0];
	Pdot[1]=- P[1][1];
	Pdot[2]=- P[1][1];
	Pdot[3]=Q_gyro;

	// Pk- 先验估计误差协方差微分的积分 = 先验估计误差协方差
	P[0][0] += Pdot[0] * dt;
	P[0][1] += Pdot[1] * dt;
	P[1][0] += Pdot[2] * dt;
	P[1][1] += Pdot[3] * dt;

	angle_err = asin(*AcceValue) * 180 / PI - car_Angle[0];//zk-先验估计

	PCt_0 = C_0 * P[0][0];
	PCt_1 = C_0 * P[1][0];

	EE = R_angle + C_0 * PCt_0;

	K_0 = PCt_0 / EE;
	K_1 = PCt_1 / EE;

	t_0 = PCt_0;
	t_1 = C_0 * P[0][1];

	P[0][0] -= K_0 * t_0;//后验估计误差协方差
	P[0][1] -= K_0 * t_1;
	P[1][0] -= K_1 * t_0;
	P[1][1] -= K_1 * t_1;

	//后验估计
	car_Angle[0] += K_0 * angle_err;
	q_bias	+= K_1 * angle_err;

	//输出值（后验估计）的微分 = 角速度
	car_Angle[1]= *GyroAngle-q_bias;
}

//==============================================================
//函数名称：ADToGyroAccePHY
//函数返回：无
//参数说明：uint_16 *   ADValue，存放陀螺仪、加速度传感器三向AD采样
//值的数组指针，
//          float *   GyroAngle，存放陀螺仪的数组指针,单位°/s,往前倾值增大,往后倾值减小
//          float *   AcceValue，存放加速度传感器加速度的数组指针,单位g,往前倾值减小,往后倾值增大
//功能概要：陀螺仪、加速度传感器的采样电压值转成角速度、加速度。
//==============================================================
void ADToGyroAccePHY(uint16_t *ADValue,float *GyroAngle,float *AcceValue)
{
	//加速度传感器
	*AcceValue = -1 * ((ADValue[0] - CAR_ACCE_SET )
	    		* 3.3 / 4096) / 0.8;
	//陀螺仪角速度
	 *GyroAngle = ((ADValue[1] - CAR_GYRO_SET)
			* 3.3 / 4096) / ((0.67 / 1000) * 5.1);

}


//==============================================================
//函数名称：AngleControl
//函数返回：
//参数说明：	float	*PWM_aq_gle,
//      	float	 angle_P,角度比例控制参数
//          float    angle_D,角度微分控制参数
//功能概要：车模直立控制函数。根据车模角度和角速度计算车模电机的控制量。
//==============================================================
int16_t AngleControl(float *PWM_aq_gle,float angle_P,float angle_D)
{
    float fValue,fGyro_value;
    static float gyro_err;
    int32_t Angle_PWM_OUT;
    int16_t Piont = 10;//50 ;//10

    fGyro_value= (PWM_aq_gle[1]) * angle_D;
    fValue = (PWM_aq_gle[0]) * angle_P*Piont +(fGyro_value*0.7+gyro_err*0.3);
    gyro_err=fGyro_value;

	if(fValue > ANGLE_PWM_OUT_MAX)      fValue = ANGLE_PWM_OUT_MAX;
	else if(fValue < ANGLE_PWM_OUT_MIN) fValue = ANGLE_PWM_OUT_MIN;
	Angle_PWM_OUT = (int32_t)fValue;

    return Angle_PWM_OUT ;
}

/***********************************************************
函数名称：AAangPWMOut
函数功能：
入口参数：	NewspeedPWM      当前的电机输出PWM
      	LastspeedPWM     上次电机输出PWM
        PeriodCount      平滑周期
出口参数：无
备 注：
***********************************************************/
int16_t AAangPWMOut(int16_t NewAangPWM ,int16_t LastAangPWM,uint8_t PeriodCount)
{
	int16_t  AangPWMfav ;
	int16_t  AangOUT ;
    AangPWMfav = NewAangPWM - LastAangPWM ;
    AangOUT = AangPWMfav *(PeriodCount)/AANGPERIODFAV + LastAangPWM ;
    return AangOUT ;

}

/***********************************************************
函数名称：TURNPWMOut
函数功能：
入口参数：	NewspeedPWM      当前的电机输出PWM
        LastspeedPWM     上次电机输出PWM
        PeriodCount      平滑周期
出口参数：无
备 注：
***********************************************************/
int16_t TURNPWMOut(int16_t NewAangPWM ,int16_t LastAangPWM,int8_t PeriodCount)
{
	int16_t  AangPWMfav ;
	int16_t  AangOUT ;
    AangPWMfav = NewAangPWM - LastAangPWM ;
    AangOUT = AangPWMfav *(PeriodCount)/AANGPERIODFAV + LastAangPWM ;
    return AangOUT ;
}

/***********************************************************
函数名称：SpeedPWMOut
函数功能：
入口参数：	NewspeedPWM      当前的电机输出PWM
        LastspeedPWM     上次电机输出PWM
        PeriodCount      平滑周期
出口参数：无
备 注：
***********************************************************/
int16_t SpeedPWMOut(int16_t NewspeedPWM ,int16_t LastspeedPWM,uint8_t PeriodCount)
{
	int16_t  speedPWMfav ;
	int16_t  SpeedOUT ;
    speedPWMfav = NewspeedPWM - LastspeedPWM ;
    SpeedOUT = speedPWMfav *(PeriodCount)/SPEEDPERIODFAV + LastspeedPWM ;

    return SpeedOUT ;
}

/***********************************************************
函数名称：MotorSpeedOut
函数功能：
入口参数：	anglePWM
        speedPWM
        turnPWM
返回值：无
备 注：
***********************************************************/
int16_t MotorSpeedOut(int16_t anglePWM ,int16_t speedPWM ,int16_t turnPWM)
{
	int32_t LeftMotorOut ,RinghtMotorOut ;
	int32_t speedAvPWM ,turnAvPWM ;
	int32_t  leftMotorPWM ,RingtMotorPWM ;
    turnAvPWM = turnPWM/TURNTIMCOUNT ;

    LeftMotorOut = anglePWM*50 - speedPWM + turnAvPWM ;
    RinghtMotorOut = anglePWM*50 - speedPWM - turnAvPWM ;

    motor_set(MOTOR1,LeftMotorOut);
    motor_set(MOTOR2,RinghtMotorOut);

    return ((LeftMotorOut +RinghtMotorOut)/2);
}





