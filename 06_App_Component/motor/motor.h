//===========================================================================
//�ļ����ƣ�motor.h
//���ܸ�Ҫ��motor��������ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//��    ����V2.0, 20150522
//===========================================================================

#ifndef MOTOR_H_               //��ֹ�ظ����壨MOTOR_H_  ��ͷ)
#define MOTOR_H_
//����ͷ�ļ�
#include "common.h"
#include "pwm.h"


//��·PWM������
#define MOTOR1 0
#define MOTOR2 1

//���ģ���ͨ����
#define MOTOR1_PWM1   FTM0           // FTM0_CH4    //(PORTD|4)
#define MOTOR1_PWM2   FTM0           // FTM0_CH5    //(PORTD|5)
#define MOTOR2_PWM1   FTM0   		 // FTM0_CH2	//(PORTC|3)
#define MOTOR2_PWM2   FTM0 		   	 // FTM0_CH3	//(PORTC|4)

#define MOTOR1_PWM1_CH		FTMCH0
#define MOTOR1_PWM2_CH		FTMCH1
#define MOTOR2_PWM1_CH		FTMCH2
#define MOTOR2_PWM2_CH		FTMCH3

//���PWM����
#define MOTOR_PERIOD 1000 //���PWM���ڣ�����1ms��1000��ʾ1ms,��PWM.h��

//====================================================================
//�������ƣ�motor_init
//�������أ���
//����˵����motor:ѡ���� ��MOTOR_1��MOTOR_2
//���ܸ�Ҫ�������ʼ�������ݴ������ѡ��Ҫ��ʼ���ĵ��������MOTOR_1����Ȼ����ݺ궨������ţ�����
//      MOTOR1_PWM1��MOTOR1_PWM2�������ڣ�MOTOR_PERIOD����ʼ���������ʼռ�ձ�Ϊ0
//====================================================================
void motor_init(uint8_t motor);

//====================================================================
//�������ƣ�motor_set;
//�������أ���
//����˵����  motor:ѡ���� ��MOTOR_1��MOTOR_2
//       duty��  ռ�ձȣ����Ƴ���ת��,
//       ������ ��-PWM_ACCURACY~PWM_ACCURACY(��PWM.h�ж���) ////����
//���ܸ�Ҫ�����õ���ٶȣ����ݵ��ѡ��motor�����Լ�ռ�ձ�duty�����ö�Ӧ�����PWMռ�ձ�
//====================================================================
void motor_set(uint8_t motor, int16_t duty);



#endif //��ֹ�ظ����壨MOTOR_H_ ��β)
