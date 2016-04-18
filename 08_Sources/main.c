//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�

//ȫ�ֱ�������
uint32_t PITCounter = 0;
uint8_t TIME0flag_5ms;
uint8_t TIME0flag_10ms;
uint8_t TIME0flag_15ms;
uint8_t TIME0flag_20ms;
uint16_t TIME0flag_100ms;
uint32_t TIME0flag_1s;

uint8_t APWMflg = 1;

/*******
 PID����
 *******/
float Angle_P;
float Angle_D;
uint32_t Speed_P;
uint32_t Speed_I;
uint32_t Speed_D;

/*************
 ���ٶȼƺ�������
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
 ���ٱ���
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
	//1. ����������ʹ�õı���
	uint32_t mRuncount;     //��ѭ��������
//	uint8_t duty;
	uint8_t countgo;
	uint16_t ADValue[2];
	float GyroAngle, AcceValue, car_Angle[2];
	//2. �����ж�
	DISABLE_INTERRUPTS
	;
	//3. ��ʼ������ģ��
	light_init(RUN_LIGHT1, Light_ON); //��1��ʼ��
	light_init(RUN_LIGHT2, Light_ON); //��2��ʼ��
	uart_init(UART_TEST, 115200);     //uart5��ʼ��
	pit_init(PIT0, BUS_CLK_KHz * 5);  //��ʼ��pit0������1s
//	pwm_init(FTM0, FTMCH0,1000,0);
//	pwm_init(FTM0, FTMCH1,100,0);
	motor_init(MOTOR1);
	motor_init(MOTOR2);
	GyroAcce_init();
	//4. ���йر�������ֵ
//	duty = 0;
//	mRuncount = 0;      //С�Ƽ�����
	count = 0;

	/***********
	 ��ʼ�ٶ�
	 ***********/
	SpeedAD = 50 ;
	/***********
	 PID����������
	 ***********/
	Angle_P = 0.008;  //0.005
	Angle_D = 0.005;  //0.005
	Speed_P = 0; //55
	Speed_I = 0;  //20
	Speed_D = 0;

	//5. ʹ��ģ���ж�
	enable_pit_int(PIT0);   //��pit�ж�
	uart_enable_re_int(UART_TEST);   //ʹ��uart5�����ж�
	//6. �����ж�
	ENABLE_INTERRUPTS;

	//������ѭ��
	//��ѭ����ʼ==================================================================
	for (;;) 
	{
		mRuncount++;
		if (mRuncount > RUN_COUNTER_MAX)
		{
			mRuncount=0;		   //��ѭ����������������
			light_change(RUN_LIGHT1);      //���ƣ�RUN_LIGHT_BLUE��״̬�仯
		}

		if (TIME0flag_5ms == 1)    // 5mS IF�������ִ��һ��
		{
			TIME0flag_5ms = 0;

			//���ٶȼ��ٶȴ�����AD�ɼ�
			AAngAcceCount = GyroAcce_getAD(ADValue, AAngAcceCount);

//			for (AInitC = 0; AInitC < 6; AInitC++) {
//				AAngleArrySCI[AInitC] = AAngleAcceleArry[AInitC]
//						/ AAngAcceCount;
//				AAngleAcceleArry[AInitC] = 0;
//			}
//			AAngAcceCount = 0;
//
//			//�򴮿ڷ��ͽ��ٶ��Լ����ٶȵ�ADֵ,���ڻ�ȡ�����Ǽ��ٶȴ�������ʼ״̬ADֵ
//			uart_send1(5,0x0);
//			uart_send1(5,ADValue[0] >> 8);
//			uart_send1(5,ADValue[0]);
//			uart_send1(5,ADValue[1] >> 8);
//			uart_send1(5,ADValue[1]);
//			uart_send1(5,0xff);
//
			//���ٶȼ��ٶȴ�����ADֵ�ع�����ֵ,���ٶȵ�λΪ��/s,���ٶȵ�λΪg
			ADToGyroAccePHY(ADValue, &GyroAngle, &AcceValue);
//			//�򴮿ڷ��ͽ��ٶ��Լ����ٶȵ�����ֵ,���ٶȵ�λΪ��/s,���ٶȵ�λΪm/s^2
//			uart_send1(5,(int)GyroAngle);
//			uart_send1(5,(int)(AcceValue*g));

			//ͨ���������˲��õ����ӵ��������ٶ�,��λΪ��͡�/s
			GyroAccePHYToAngle(&GyroAngle, &AcceValue, car_Angle);
//						uart_send1(5,0x0);
//						uart_send1(5,(int)car_Angle[0] >> 8);
//						uart_send1(5,(int)car_Angle[0]);
//						uart_send1(5,(int)AcceValue >> 8);
//						uart_send1(5,(int)AcceValue);
//						uart_send1(5,ADValue[0] >> 8);
//						uart_send1(5,ADValue[0]);
//						uart_send1(5,0xff);
//			OutData[0] = car_Angle[0];				//�˲�����б�Ƕ�
//			OutData[1] = car_Angle[1];				//�˲�����ٶ�
//			OutData[2] = asin(AcceValue) * 180 / PI;//�˲�ǰ��б�Ƕ�
//			OutData[3] = GyroAngle;					//�˲�ǰ���ٶ�
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

//		if (TIME0flag_10ms == 1) // 10mS IF�������ִ��һ��
//		{
//			TIME0flag_10ms = 0;
//			//===========================ת�����===================================
//
//			TurnPriodCt = 0;
////			ATurnPWM = CCD_pwm(Pix);
//		}

		/******************
		 �ٶȼ���ģ��
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

		//���¼����û�����--------------------------------------------------------
	} //��ѭ��end_for
	  //��ѭ������==================================================================
}
