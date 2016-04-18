//===========================================================================
//�ļ����ƣ�pwm.c
//���ܸ�Ҫ��pwm�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2013-5-5   V3.0 ����
//===========================================================================
#ifndef _PWM_H
#define _PWM_H

#include "common.h"
#include "gpio.h"

#define FTM0_IRQ_NO 17
#define PWM_ACCURACY 10000 //����ռ�ձ�(duty)��ΧΪ0~PWM_ACCURACY,��������Ϊ1
//FTMģ���
#define FTM0  0
#define FTM1  1
#define FTM2  2
//FTMͨ����
#define FTMCH0  0
#define FTMCH1  1
#define FTMCH2  2
#define FTMCH3  3
#define FTMCH4  4
#define FTMCH5  5
#define FTMCH6  6
#define FTMCH7  7
//����FTMͨ����ѡ��                     		  ���õĶ˿�_����
#define FTM0_CH0 (PORTC|1) // A3  C1
#define FTM0_CH1 (PORTC|2) // A4  C2
#define FTM0_CH2 (PORTC|3) // A5  C3
#define FTM0_CH3 (PORTC|4) // A6  C4
#define FTM0_CH4 (PORTD|4) // A7  D4
#define FTM0_CH5 (PORTD|5) // A0  D5
#define FTM0_CH6 (PORTD|6) // A1  D6
#define FTM0_CH7 (PORTD|7) // A2  D7

#define FTM1_CH0 (PORTA|12) //A8  A12  B0
#define FTM1_CH1 (PORTA|13) //A9  A13  B1

#define FTM2_CH0 (PORTA|1) // A10
#define FTM2_CH1 (PORTA|2) // A11

#define bus_clk_khz 50000

//=========================================================================
//�������ƣ�pwm_init
//���ܸ�Ҫ��pwmģ���ʼ����
//����˵����ftmModule_channel:ģ��ţ�0��1��2  ͨ����:0-6 ���pwm.h�ļ�����
//         period������ ��λ΢�루����0.1msΪ100,1msΪ1000��
//         duty��ռ�ձ�    0~PWM_ACCURACY(��PWM.h�ж���)
//�������أ���
//=========================================================================
uint8_t pwm_init(uint8_t ftmModule, uint8_t channel, uint32_t period, uint16_t duty);

//=========================================================================
//�������ƣ�pwm_set
//���ܸ�Ҫ������pwmģ�顣
//����˵����ftmModule_channel:ģ��ţ�0��1��2  ͨ����:0-6 ���pwm.h�ļ�����
//			period������ ��λ΢�루����0.1msΪ100,1msΪ1000��
//			duty��ռ�ձ�    0~PWM_ACCURACY(��PWM.h�ж���)
//�������أ���
//=========================================================================
uint8_t pwm_set(uint8_t ftmModule, uint8_t channel, uint32_t period, uint16_t duty);

#endif

//===========================================================================
//������
//��1�����ǿ�����Դ���룬�ڱ������ṩ��Ӳ��ϵͳ����ͨ������Ϸ��׸���ᣬ����֮����
//     ��ӭָ����
//��2������ʹ�÷Ǳ�����Ӳ��ϵͳ���û�����ֲ����ʱ������ϸ�����Լ���Ӳ��ƥ�䡣
//
//���ݴ�ѧ��˼����Ƕ��ʽ���ģ����ݻ�����Ϣ�Ƽ����޹�˾��
//������ѯ��0512-65214835  http://sumcu.suda.edu.cn
//ҵ����ѯ��0512-87661670,18915522016  http://www.hxtek.com.cn
