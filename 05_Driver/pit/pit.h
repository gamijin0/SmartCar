//==========================================================================
//�ļ����ƣ�pit.h
//���ܸ�Ҫ��K60 pit�ײ����������ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2011-11-13  V1.0  ��ʼ�汾��
//         2014-11-9   V2.0  KDS���¿��
//==========================================================================


#ifndef __HW_PIT_H__
#define __HW_PIT_H__
//1 ͷ�ļ�
#include "common.h"

//2 �궨��

#define PIT0 0
#define PIT1 1
#define PIT2 2
#define PIT3 3

//==========================================================================
//��������: pit_init
//��������: ��                                          
//����˵��: pitno:��ʾpitͨ���š�  
//			timeout:��ʾ��ʱ�����ʼ�ݼ���ֵ          
//���ܸ�Ҫ: ������ؼĴ�����ֵ        
//==========================================================================
void pit_init(uint8_t pitno,uint32_t timeout);

//==========================================================================
//��������: enable_pit_int
//��������: ��                                              
//����˵��: pitno: ��ʾpitͨ����      
//���ܸ�Ҫ: ��PIT�ж�                                                                                                     
//==========================================================================
void enable_pit_int(uint8_t pitno);

//==========================================================================
//��������: disable_pit_int
//��������: ��                                              
//����˵��: pitno: ��ʾpitͨ����      
//���ܸ�Ҫ: �ر�PIT�ж�                                                                                                     
//==========================================================================
void disable_pit_int(uint8_t pitno);

#endif //__HW_PIT_H__