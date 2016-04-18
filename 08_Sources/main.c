//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件

//全局变量定义
uint32_t PITCounter = 0;
uint8_t TIME0flag_5ms;
uint8_t TIME0flag_10ms;
uint8_t TIME0flag_15ms;
uint8_t TIME0flag_20ms;
uint16_t TIME0flag_100ms;
uint32_t TIME0flag_1s;

uint8_t APWMflg = 1;

/*******
 PID参数
 *******/
float Angle_P;
float Angle_D;
uint32_t Speed_P;
uint32_t Speed_I;
uint32_t Speed_D;

/*************
 加速度计和陀螺仪
 *************/
uint8_t AInitC;
uint16_t AAngleAcceleArry[6];
uint8_t AAngAcceCount;
float AAngleArrySCI[6];
int16_t MotorAAngPWM;
uint8_t AAngPeriodCount;
int16_t AAngPWM;
int16_t LastAAngPWM;

/********
 调速变量
 ********/
uint16_t SpeedPeriodCount;
int16_t LeftSpeedC, RightSpeedC;
int16_t count1 = 0;
int16_t SpeedAD ;
int16_t SpeedPWM = 0;
int16_t SpeedPWMR = 0;
int16_t LastSpeedPWM = 0;
int16_t LastSpeedPWMR = 0;
int16_t MotorSpeedPWM;
int16_t MotorSpeedPWMR;
int16_t PWMout;

int16_t ATurnPWM;
int16_t ALastTurnPWM;
int16_t AMotorTurnPWM;
int8_t TurnPriodCt;
uint16_t RunCountLast, RunCountLast1;
extern uint16_t RunCount, RunCount1;
uint8_t run_flag,Runstop;

int main(void) {
	//1. 声明主函数使用的变量
	uint32_t mRuncount;     //主循环计数器
//	uint8_t duty;
	uint8_t countgo;
	uint16_t ADValue[2];
	float GyroAngle, AcceValue, car_Angle[2];
	//2. 关总中断
	DISABLE_INTERRUPTS
	;
	//3. 初始化外设模块
	light_init(RUN_LIGHT1, Light_ON); //灯1初始化
	light_init(RUN_LIGHT2, Light_ON); //灯2初始化
	uart_init(UART_TEST, 115200);     //uart5初始化
	pit_init(PIT0, BUS_CLK_KHz * 5);  //初始化pit0，周期1s
//	pwm_init(FTM0, FTMCH0,1000,0);
//	pwm_init(FTM0, FTMCH1,100,0);
	motor_init(MOTOR1);
	motor_init(MOTOR2);
	GyroAcce_init();
	//4. 给有关变量赋初值
//	duty = 0;
//	mRuncount = 0;      //小灯计数器
	count = 0;

	/***********
	 初始速度
	 ***********/
	SpeedAD = 50 ;
	/***********
	 PID变量，待调
	 ***********/
	Angle_P = 0.008;  //0.005
	Angle_D = 0.005;  //0.005
	Speed_P = 0; //55
	Speed_I = 0;  //20
	Speed_D = 0;

	//5. 使能模块中断
	enable_pit_int(PIT0);   //开pit中断
	uart_enable_re_int(UART_TEST);   //使能uart5接收中断
	//6. 开总中断
	ENABLE_INTERRUPTS;

	//进入主循环
	//主循环开始==================================================================
	for (;;) 
	{
		mRuncount++;
		if (mRuncount > RUN_COUNTER_MAX)
		{
			mRuncount=0;		   //主循环次数计数器清零
			light_change(RUN_LIGHT1);      //蓝灯（RUN_LIGHT_BLUE）状态变化
		}

		if (TIME0flag_5ms == 1)    // 5mS IF里面语句执行一次
		{
			TIME0flag_5ms = 0;

			//角速度加速度传感器AD采集
			AAngAcceCount = GyroAcce_getAD(ADValue, AAngAcceCount);

//			for (AInitC = 0; AInitC < 6; AInitC++) {
//				AAngleArrySCI[AInitC] = AAngleAcceleArry[AInitC]
//						/ AAngAcceCount;
//				AAngleAcceleArry[AInitC] = 0;
//			}
//			AAngAcceCount = 0;
//
//			//向串口发送角速度以及加速度的AD值,用于获取陀螺仪加速度传感器初始状态AD值
//			uart_send1(5,0x0);
//			uart_send1(5,ADValue[0] >> 8);
//			uart_send1(5,ADValue[0]);
//			uart_send1(5,ADValue[1] >> 8);
//			uart_send1(5,ADValue[1]);
//			uart_send1(5,0xff);
//
			//角速度加速度传感器AD值回归物理值,角速度单位为°/s,加速度单位为g
			ADToGyroAccePHY(ADValue, &GyroAngle, &AcceValue);
//			//向串口发送角速度以及加速度的物理值,角速度单位为°/s,加速度单位为m/s^2
//			uart_send1(5,(int)GyroAngle);
//			uart_send1(5,(int)(AcceValue*g));

			//通过卡尔曼滤波得到车子的倾角与角速度,单位为°和°/s
			GyroAccePHYToAngle(&GyroAngle, &AcceValue, car_Angle);
//						uart_send1(5,0x0);
//						uart_send1(5,(int)car_Angle[0] >> 8);
//						uart_send1(5,(int)car_Angle[0]);
//						uart_send1(5,(int)AcceValue >> 8);
//						uart_send1(5,(int)AcceValue);
//						uart_send1(5,ADValue[0] >> 8);
//						uart_send1(5,ADValue[0]);
//						uart_send1(5,0xff);
//			OutData[0] = car_Angle[0];				//滤波后倾斜角度
//			OutData[1] = car_Angle[1];				//滤波后角速度
//			OutData[2] = asin(AcceValue) * 180 / PI;//滤波前倾斜角度
//			OutData[3] = GyroAngle;					//滤波前角速度
//			OutPut_Data(OutData);
//
			uart_send1(5,(int)car_Angle[0]);
			uart_send1(5,(int)(asin(AcceValue) * 180 / PI));

//
//			AAngPWM = AngleControl(car_Angle, Angle_P, Angle_D);
//			AAngPeriodCount = 0;
//
//			AAngPeriodCount++;
//			MotorAAngPWM = AAangPWMOut(AAngPWM, LastAAngPWM, AAngPeriodCount);
//			LastAAngPWM = MotorAAngPWM;

//			SpeedPeriodCount++;
//			MotorSpeedPWM = SpeedPWMOut(SpeedPWM, LastSpeedPWM,
//					SpeedPeriodCount);
//			LastSpeedPWM = MotorSpeedPWM;

//			TurnPriodCt++;
////			AMotorTurnPWM = TURNPWMOut(ATurnPWM, ALastTurnPWM, TurnPriodCt);
//			AMotorTurnPWM = 0;
//			ALastTurnPWM = AMotorTurnPWM;

//			PWMout = MotorSpeedOut(MotorAAngPWM, MotorSpeedPWM, AMotorTurnPWM);
		}

//		if (TIME0flag_10ms == 1) // 10mS IF里面语句执行一次
//		{
//			TIME0flag_10ms = 0;
//			//===========================转向控制===================================
//
//			TurnPriodCt = 0;
////			ATurnPWM = CCD_pwm(Pix);
//		}

		/******************
		 速度计算模块
 		 *****************/
//		if (TIME0flag_100ms == 1)
//		{
//			TIME0flag_100ms = 0;
//
//			count1 = (LeftSpeedC + RightSpeedC) / 2;
//
//			SpeedPeriodCount = 0;
//			LastSpeedPWM = SpeedPWM;
//
//			if (run_flag == 0)
//			{
//				if (RunCountLast == RunCount)
//					run_flag = 1;
//
//				RunCountLast = RunCount;
////				run_flag1=0;
////				for(i=0;i<10;i++)
////				{
////				light_signal1_now=gpio_get(PORTB|(2));//b2
////
////				uart_send1(UART_2,0);
////				uart_send1(UART_2,light_signal1_now>>8);
////				uart_send1(UART_2,light_signal1_now);
////				uart_send1(UART_2,0xff);
////
////
////				if(light_signal1_now==0)
////				{
////					run_flag1=1;
////					break;
////				}
////				}
////				if(run_flag1==0)
////				{
////					run_flag=1;
////				}
//			}
//			else
//			{
//
////				if(RunCountLast == RunCount)
////				{
////					motor_set(MOTOR1, 0);
////					motor_set(MOTOR2, 0);
////					run_flag=1;
////					break;
////				}
//
//				RunCountLast = RunCount;
//
//				SpeedPWM = SpeedPID(count1, SpeedAD, Speed_P, Speed_I, Speed_D);
//				LeftSpeedC = 0;
//				RightSpeedC = 0;
//			}
//		}

		//以下加入用户程序--------------------------------------------------------
	} //主循环end_for
	  //主循环结束==================================================================
}
