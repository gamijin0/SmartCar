//===========================================================================
//�ļ����ƣ�isr.h
//���ܸ�Ҫ�� �жϵײ���������ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================

#ifndef _ISR_H   //��ֹ�ظ����壨ISR_H  ��ͷ)
#define _ISR_H

//===============�û��ж�������ע���=====================

//1 ע�ᴮ��5�ж�����
#ifdef VECTOR_071
    #undef VECTOR_071
    extern void isr_uart5_re(void);
    #define VECTOR_071  isr_uart5_re
#endif

//2 ע��PIT0�ж�����
#ifdef VECTOR_084
    #undef VECTOR_084
    extern void pit0_isr(void);
    #define VECTOR_084  pit0_isr
#endif

//3 ע��PORTD�ж�����
#ifdef VECTOR_106
    #undef VECTOR_106
    extern void PORTD_isr(void);
    #define VECTOR_106  PORTD_isr
#endif

#endif   //��ֹ�ظ����壨 ��β)
