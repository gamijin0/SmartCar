//===========================================================================
//�ļ����ƣ�arm_cm4.h
//���ܸ�Ҫ��ARM Cortex-M4�ں��ṩ���ܶ����ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-10-09   V1.0     ��ʼ�汾
//===========================================================================

#ifndef __ARM_CM4_H
#define __ARM_CM4_H

// �����жϵĺ궨��
#define ARM_INTERRUPT_LEVEL_BITS          4   //�ж����ȼ��궨��
#define ENABLE_INTERRUPTS  asm(" CPSIE i");    //�����ж�
//CPSIE,Center Process System Interrupt Enable,���봦��ϵͳ�ж�ʹ��
//ʵ��ԭ����PRIMASK(Primary Exception Mask Register)/FAULTMASK(һλ��)��0����Ϊ���ж�
#define DISABLE_INTERRUPTS asm(" CPSID i");    //�����ж�

//#include "psptypes.h"
typedef unsigned char		uint_8_t;
typedef unsigned short int  uint_16_t;
typedef unsigned long int   uint_32_t;
/*
#define _PTR_      *  // ����ָ�����͹ؼ���

// �ض��������������
// ������ÿ��ϵ���У����ζ��壺
//     �з������͡��޷������͡����Ż��з������ͺͲ��Ż��޷�������
// �ַ�ϵ��
typedef          char         _PTR_   char_ptr;
typedef unsigned char  uchar, _PTR_   uchar_ptr;
typedef volatile char         _PTR_   vchar_ptr;
typedef volatile unsigned char  vuchar, _PTR_   vuchar_ptr;
// 8λ��ϵ��
typedef signed   char   int_8, _PTR_   int_8_ptr;
typedef unsigned char  uint_8_t, _PTR_  uint_8_t_ptr;
typedef volatile signed   char   vint_8, _PTR_   vint_8_ptr;
typedef volatile unsigned char  vuint_8_t, _PTR_  vuint_8_t_ptr;
// 16λ��ϵ��
typedef          short int_16, _PTR_  int_16_ptr;
typedef unsigned short uint_16_t, _PTR_ uint_16_t_ptr;
typedef volatile          short vint_16, _PTR_  vint_16_ptr;
typedef volatile unsigned short vuint_16_t, _PTR_ vuint_16_t_ptr;
// 32λ��ϵ��
typedef          long  int_32, _PTR_  int_32_ptr;
typedef unsigned long  uint_32_t, _PTR_ uint_32_t_ptr;
typedef volatile          long  vint_32, _PTR_  vint_32_ptr;
typedef volatile unsigned long  vuint_32_t, _PTR_ vuint_32_t_ptr;
*/

//============================================================================
//�������ƣ�stop
//�������أ���
//����˵������
//���ܸ�Ҫ������CPUΪSTOPģʽ
//============================================================================
void stop (void);

//============================================================================
//�������ƣ�wait
//�������أ���
//����˵������
//���ܸ�Ҫ������CPUΪWAITģʽ
//============================================================================
void wait (void);

//============================================================================
//�������ƣ�write_vtor
//�������أ�vtor��Ҫ���ĵ�ֵ
//����˵������
//���ܸ�Ҫ�������ж�������ƫ�ƼĴ�����ֵ 
//============================================================================
void write_vtor (uint_16_t vtor);

//============================================================================
//�������ƣ�enable_irq
//�������أ���  
//����˵����irq��irq��
//���ܸ�Ҫ��ʹ��irq�ж� 
//============================================================================
void enable_irq (uint_16_t irq);

//============================================================================
//�������ƣ�disable_irq
//�������أ���      
//����˵����irq��irq��
//���ܸ�Ҫ����ֹirq�ж� 
//============================================================================
void disable_irq (uint_16_t irq);

//============================================================================
//�������ƣ�set_irq_priority
//�������أ���      
//����˵����irq��irq��         											   
//         prio�����ȼ�
//���ܸ�Ҫ������irq�жϺ����ȼ� 
//============================================================================
void set_irq_priority (uint_16_t irq, uint_16_t prio);


#endif
