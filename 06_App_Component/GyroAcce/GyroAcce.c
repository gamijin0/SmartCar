//==============================================================
//�ļ����ƣ�GyroAcce.c
//���ܸ�Ҫ�������ǡ����ٶȴ�����Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//==============================================================
#include "GyroAcce.h"

//==============================================================
//�������ƣ�GyroAcce_Init
//�������أ���
//����˵������
//���ܸ�Ҫ�������ǡ����ٶȴ�������ʼ��������AD������ɶ������ǡ�����
//�ȴ�������MCU�������ŵĳ�ʼ�������������
//==============================================================
void GyroAcce_init(void)
{
	adc_init(1) ; //PTB4��PTB6��ʼ��
}

//==============================================================
//�������ƣ�GyroAcce_getAD
//�������أ���
//����˵����ADValue��������ǡ����ٶȴ�����������AD����
//���ܸ�Ҫ����ȡ�����ǡ����ٶȴ�����AD���ݡ�����AD������ɶ������ǡ�
//���ٶȴ�������MCU�������ŵĵ�ƽ������
//==============================================================
uint8_t GyroAcce_getAD(uint16_t *ADValue, uint8_t Count)
{
	 *ADValue       = adc_ave(1,10,12,16) ;    //PTB4		//Z����ٶ�
     *(ADValue + 1) = adc_ave(1,12,12,16) ;    //PTB6		//X����ٶ�

     return (Count + 16);
}

//==============================================================
//�������ƣ�GyroAccePHYToAngle
//�������أ���
//����˵���� float *   GyroAngle����������ǽ��ٶȵ�ָ��
//          float *   AcceValue����ż��ٶȴ��������ٶȵ�ָ��
//          float *   car_Angle����ų�ģ��ǵ�����ָ��
//���ܸ�Ҫ�����ÿ������˲��ѽ��ٶȡ����ٶ�ת�ɳ�ģ��ǡ�
//==============================================================
void GyroAccePHYToAngle(float *GyroAngle,float *AcceValue,
		float *car_Angle)
{
	float dt=0.005;	//0.005
	static float P[2][2] = {{ 1, 0 },{ 0, 1 }};
	static float Pdot[4] ={0,0,0,0};
	static const char C_0 = 1;
	static float q_bias,angle_err,PCt_0,PCt_1,EE,K_0,K_1,t_0,t_1;

	car_Angle[0]+=(*GyroAngle-q_bias) * dt;//�������

	// Pk-' ����������Э�����΢��
	Pdot[0]=Q_angle - P[0][1] - P[1][0];
	Pdot[1]=- P[1][1];
	Pdot[2]=- P[1][1];
	Pdot[3]=Q_gyro;

	// Pk- ����������Э����΢�ֵĻ��� = ����������Э����
	P[0][0] += Pdot[0] * dt;
	P[0][1] += Pdot[1] * dt;
	P[1][0] += Pdot[2] * dt;
	P[1][1] += Pdot[3] * dt;

	angle_err = asin(*AcceValue) * 180 / PI - car_Angle[0];//zk-�������

	PCt_0 = C_0 * P[0][0];
	PCt_1 = C_0 * P[1][0];

	EE = R_angle + C_0 * PCt_0;

	K_0 = PCt_0 / EE;
	K_1 = PCt_1 / EE;

	t_0 = PCt_0;
	t_1 = C_0 * P[0][1];

	P[0][0] -= K_0 * t_0;//����������Э����
	P[0][1] -= K_0 * t_1;
	P[1][0] -= K_1 * t_0;
	P[1][1] -= K_1 * t_1;

	//�������
	car_Angle[0] += K_0 * angle_err;
	q_bias	+= K_1 * angle_err;

	//���ֵ��������ƣ���΢�� = ���ٶ�
	car_Angle[1]= *GyroAngle-q_bias;
}

//==============================================================
//�������ƣ�ADToGyroAccePHY
//�������أ���
//����˵����uint_16 *   ADValue����������ǡ����ٶȴ���������AD����
//ֵ������ָ�룬
//          float *   GyroAngle����������ǵ�����ָ��,��λ��/s,��ǰ��ֵ����,������ֵ��С
//          float *   AcceValue����ż��ٶȴ��������ٶȵ�����ָ��,��λg,��ǰ��ֵ��С,������ֵ����
//���ܸ�Ҫ�������ǡ����ٶȴ������Ĳ�����ѹֵת�ɽ��ٶȡ����ٶȡ�
//==============================================================
void ADToGyroAccePHY(uint16_t *ADValue,float *GyroAngle,float *AcceValue)
{
	//���ٶȴ�����
	*AcceValue = -1 * ((ADValue[0] - CAR_ACCE_SET )
	    		* 3.3 / 4096) / 0.8;
	//�����ǽ��ٶ�
	 *GyroAngle = ((ADValue[1] - CAR_GYRO_SET)
			* 3.3 / 4096) / ((0.67 / 1000) * 5.1);

}


//==============================================================
//�������ƣ�AngleControl
//�������أ�
//����˵����	float	*PWM_aq_gle,
//      	float	 angle_P,�Ƕȱ������Ʋ���
//          float    angle_D,�Ƕ�΢�ֿ��Ʋ���
//���ܸ�Ҫ����ģֱ�����ƺ��������ݳ�ģ�ǶȺͽ��ٶȼ��㳵ģ����Ŀ�������
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
�������ƣ�AAangPWMOut
�������ܣ�
��ڲ�����	NewspeedPWM      ��ǰ�ĵ�����PWM
      	LastspeedPWM     �ϴε�����PWM
        PeriodCount      ƽ������
���ڲ�������
�� ע��
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
�������ƣ�TURNPWMOut
�������ܣ�
��ڲ�����	NewspeedPWM      ��ǰ�ĵ�����PWM
        LastspeedPWM     �ϴε�����PWM
        PeriodCount      ƽ������
���ڲ�������
�� ע��
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
�������ƣ�SpeedPWMOut
�������ܣ�
��ڲ�����	NewspeedPWM      ��ǰ�ĵ�����PWM
        LastspeedPWM     �ϴε�����PWM
        PeriodCount      ƽ������
���ڲ�������
�� ע��
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
�������ƣ�MotorSpeedOut
�������ܣ�
��ڲ�����	anglePWM
        speedPWM
        turnPWM
����ֵ����
�� ע��
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





