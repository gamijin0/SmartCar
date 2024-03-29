//===========================================================================
//文件名称：isr.c
//功能概要：自定义中断服务例程源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2013-05-03    V1.0,2014-05-10    V2.3(WYH) 
//===========================================================================

#include "includes.h"

extern  uint32_t PITCounter;
uint16_t pluse_countL = 0;
uint16_t pluse_countR = 0;
//===========================================================================
//中断例程：isr_uart(x)_re
//功能概要：串口中断服务例程，每收到一个字节执行一次本程序，发送回去，并组帧
//参数说明：user_isr_ptr（未使用）
//备注：使用全局变量 g_UART_ISR_buffer[]     
//===========================================================================
void isr_uart0_re(void)
{
	    uint8_t ch;
	    uint8_t flag = 1;

	    DisableInterrupts;

	    ch = uart_re1(UART_0, &flag);
	    if (0 == flag)
	    {
	        uart_send1(UART_0, ch);
	    }

	    EnableInterrupts;
}


void isr_uart3_re(void)
{
	    uint8_t ch;
	    uint8_t flag = 1;

	    DisableInterrupts;

	    ch = uart_re1(UART_3, &flag);
	    if (0 == flag)
	    {
	        uart_send1(UART_3, ch);
	    }

	    EnableInterrupts;
}


void isr_uart5_re(void)
{
	    uint8_t ch;
	    uint8_t flag = 1;

	    DisableInterrupts;

	    ch = uart_re1(UART_5, &flag);
	    if (0 == flag)
	    {
//	        uart_send1(UART_5, ch);
	    }

	    EnableInterrupts;
}

//==========================================================================
//函数名称：pit0_isr
//功能概要：中断例程
//参数说明：无
//函数返回：无
//==========================================================================
extern uint8_t TIME0flag_5ms   ;
extern uint8_t TIME0flag_10ms  ;
extern uint8_t TIME0flag_15ms  ;
extern uint8_t TIME0flag_20ms  ;
extern uint16_t TIME0flag_100ms ;
extern uint32_t TIME0flag_1s ;
void pit0_isr(void)
{
		static uint8_t TimerCnt5ms = 0;
		static uint8_t TimerCnt10ms = 0;
		static uint8_t TimerCnt15ms = 0;
		static uint8_t TimerCnt20ms = 0;
		static uint16_t TimerCnt100ms = 0;
		static uint32_t TimerCnt1s=0;
		enter_critical(); //进入临界区,关中断
		if ((PIT_TFLG(PIT0) & PIT_TFLG_TIF_MASK) == PIT_TFLG_TIF_MASK)
		{
			PIT_TFLG(PIT0) |= PIT_TFLG_TIF_MASK;       //清标志
		}

		TimerCnt5ms++;
		TimerCnt10ms++;
		TimerCnt15ms++;
		TimerCnt20ms++;
		TimerCnt100ms++;
		TimerCnt1s++;

		if (TimerCnt5ms >= 1)
		{
			TimerCnt5ms = 0;
			TIME0flag_5ms = 1;
		}//5ms置标志
		if (TimerCnt10ms >= 2)
		{
			TimerCnt10ms = 0;
			TIME0flag_10ms = 1;
		}//10ms置标志
		if (TimerCnt15ms >= 3)
		{
			TimerCnt15ms = 0;
			TIME0flag_15ms = 1;
		}//15ms置标志
		if (TimerCnt20ms >= 4)
		{
			TimerCnt20ms = 0;
			TIME0flag_20ms = 1;
		}//20ms置标志
		if (TimerCnt100ms >= 20)
		{
			TimerCnt100ms = 0;
			TIME0flag_100ms = 1;
		}//100ms置标志
		if (TimerCnt1s >= 200)
		{
			TimerCnt1s = 0;
			TIME0flag_1s = 1;
		}//1s置标志

		exit_critical(); //退出临界区,恢复原总中断设置情况
}

//============================================================================
//函数名称：PORTD_IRQHandler
//函数参数：
//函数返回：无
//功能概要：PORTD端口中断服务函数
//============================================================================
int16_t LeftSpeedC, RightSpeedC;
int16_t RunCount;
extern uint8_t run_flag, Runstop;
//GPIO中断服务例程
void PORTD_isr()
{
	uint8_t  n;    //引脚号

	n = (uint8_t)(SPEED_PINL & 0x0F);  //获取引脚号
    if(PORTD_ISFR & (1 << n))         //设定的引脚触发中断
    {
        PORTD_ISFR  |= (1 << n);        //写1清中断标志位
        LeftSpeedC ++ ;
    }
    n = (uint8_t)(SPEED_PINR & 0x0F);  //获取引脚号
    if(PORTD_ISFR & (1 << n))         //设定的引脚触发中断
    {
        PORTD_ISFR  |= (1 << n);        //写1清中断标志位
        RightSpeedC ++ ;
    }
}

