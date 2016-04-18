//============================================================================
//�ļ����ƣ�includes.h
//���ܸ�Ҫ��Ӧ�ù�����ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2012-11-12  V2.0
//          2014-11-9  V3.0
//============================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "gpio.h"
#include "light.h"
#include "uart.h"
#include "sysint.h"
#include "pit.h"
#include "adc.h"
#include "pwm.h"
#include "motor.h"
#include "speed.h"
#include "GyroAcce.h"
#include "control.h"

//����ȫ�ֱ���
uint16_t count;          //��¼�������
float OutData[4];
static float g = 9.794;			//�Ϻ��������ٶ�,��λm/s^2


//����С����˸Ƶ��
#define RUN_COUNTER_MAX   1500000ul

//����ʹ�õĵ��Ժ�
#define UART_TEST  UART_5


#endif
