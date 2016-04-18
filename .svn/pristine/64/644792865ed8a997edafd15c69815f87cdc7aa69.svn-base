//===========================================================================
//文件名称：isr.h
//功能概要： 中断底层驱动构件头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================

#ifndef _ISR_H   //防止重复定义（ISR_H  开头)
#define _ISR_H

//===============用户中断向量表注册表=====================

//1 注册串口5中断向量
#ifdef VECTOR_071
    #undef VECTOR_071
    extern void isr_uart5_re(void);
    #define VECTOR_071  isr_uart5_re
#endif

//2 注册PIT0中断向量
#ifdef VECTOR_084
    #undef VECTOR_084
    extern void pit0_isr(void);
    #define VECTOR_084  pit0_isr
#endif

//3 注册PORTD中断向量
#ifdef VECTOR_106
    #undef VECTOR_106
    extern void PORTD_isr(void);
    #define VECTOR_106  PORTD_isr
#endif

#endif   //防止重复定义（ 结尾)
