//===========================================================================
//文件名称：pwm.c
//功能概要：pwm底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2013-5-5   V3.0
//===========================================================================
#include "pwm.h"
#include "gpio.h"

//定义三个指针数组保存 FTMn 的地址
volatile struct FTM_MemMap *FTMx[3] = {FTM0_BASE_PTR, FTM1_BASE_PTR, FTM2_BASE_PTR};
//=========================================================================
//函数名称：pwm_init
//功能概要：pwm模块初始化。
//参数说明：ftmModule_channel:模块号：0、1、2  通道号:0-6 详见pwm.h文件定义
//       period：周期 单位微秒（比如0.1ms为100,1ms为1000）
//       duty：占空比    0~PWM_ACCURACY(在PWM.h中定义)
//函数返回：	0	成功
//			1	模块号，通道号错误
//			2	频率大于时钟的二分之一
//			3	设置管脚有误
//=========================================================================
uint8_t pwm_init(uint8_t ftmModule, uint8_t channel, uint32_t period, uint16_t duty)
{
	uint32_t clk_hz = (bus_clk_khz * 1000) >> 1;       //bus频率/2  bus_clk_khz = 50000
	uint16_t mod;
	uint8_t sc_ps;
	uint16_t cv;

	//检查传递进来的通道是否正确
	if(!( (ftmModule == FTM0) || ( (ftmModule == FTM1 || ftmModule == FTM2 ) && (channel <= FTMCH1))   ))
		return 1;		//模块号，通道号错误

	//检测 频率 是否正常 ,频率必须小于时钟二分之一
	if(!( period <= (clk_hz >> 1) ))
		return 2;		//频率大于时钟的二分之一

	/*       计算分频因子       */
	mod = (clk_hz >> 16 ) / period ;
	for(sc_ps = 0; (mod >> sc_ps) >= 1; sc_ps++);
	if(period < 1000)sc_ps++;

	mod = (clk_hz >> sc_ps) / period;                        //频率设置因子,clk_hz = 25000000

	cv = (duty * (mod - 0 + 1)) / PWM_ACCURACY;            //占空比设置因子

	/******************* 开启时钟 和 复用IO口*******************/
	//注，这里代码虽然长，但编译时会删掉很多没用的部分，不影响速度
	switch(ftmModule)
	{
	case FTM0:
		SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;                           //使能FTM0时钟
		switch(channel)
		{
		case FTMCH0:
			if(FTM0_CH0 == (PORTC|1))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
				PORT_PCR_REG(PORTC_BASE_PTR, 1) = PORT_PCR_MUX(4);  // PTC1
			}
			else if(FTM0_CH0 == (PORTA|3))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 3) = PORT_PCR_MUX(3);  // PTA3
			}
			else
			{
				return 3;                   //设置管脚有误？
			}
			break;

		case FTMCH1:
			if(FTM0_CH1 == (PORTC|2))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
				PORT_PCR_REG(PORTC_BASE_PTR, 2) = PORT_PCR_MUX(4);  // PTC2
			}
			else if(FTM0_CH1 == (PORTA|4))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 4) = PORT_PCR_MUX(3);  // PTA4
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		case FTMCH2:
			if(FTM0_CH2 == (PORTC|3))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
				PORT_PCR_REG(PORTC_BASE_PTR, 3) = PORT_PCR_MUX(4);  // PTC3
			}
			else if(FTM0_CH2 == (PORTA|5))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 5) = PORT_PCR_MUX(3);  // PTA5
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		case FTMCH3:
			if(FTM0_CH3 == (PORTC|4))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
				PORT_PCR_REG(PORTC_BASE_PTR, 4) = PORT_PCR_MUX(4);  // PTC4
			}
			else if(FTM0_CH3 == (PORTA|6))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 6) = PORT_PCR_MUX(3);  // PTA6
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		case FTMCH4:
			if(FTM0_CH4 == (PORTD|4))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
				PORT_PCR_REG(PORTD_BASE_PTR, 4) = PORT_PCR_MUX(4);  // PTD4
			}
			else if(FTM0_CH4 == (PORTA|7))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 7) = PORT_PCR_MUX(3);  // PTA7
			}
			else
			{
				return 3;                    //设置管脚有误？
			}
			break;

		case FTMCH5:
			if(FTM0_CH5 == (PORTD|5))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
				PORT_PCR_REG(PORTD_BASE_PTR, 5) = PORT_PCR_MUX(4);  // PTD5
			}
			else if(FTM0_CH5 == (PORTA|0))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 0) = PORT_PCR_MUX(3);  // PTA0
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		case FTMCH6:
			if(FTM0_CH6 == (PORTD|6))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
				PORT_PCR_REG(PORTD_BASE_PTR, 6) = PORT_PCR_MUX(4);  // PTD6
			}
			else if(FTM0_CH6 == (PORTA|1))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 1) = PORT_PCR_MUX(3);  // PTA1
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		case FTMCH7:
			if(FTM0_CH7 == (PORTD|7))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
				PORT_PCR_REG(PORTD_BASE_PTR, 7) = PORT_PCR_MUX(4);  // PTD7
			}
			else if(FTM0_CH7 == (PORTA|2))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 2) = PORT_PCR_MUX(3);  // PTA2
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;
		default:
			return 3;
		}
		break;

	case FTM1:
		SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;                           //使能FTM1时钟
		switch(channel)
		{
		case FTMCH0:
			if(FTM1_CH0 == (PORTA|8))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 8) = PORT_PCR_MUX(3);  // PTA8
			}
			else if(FTM1_CH0 == (PORTA|12))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 12) = PORT_PCR_MUX(3);  // PTA12
			}
			else if(FTM1_CH0 == (PORTB|0))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
				PORT_PCR_REG(PORTB_BASE_PTR, 0) = PORT_PCR_MUX(3);  // PTB0
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;


		case FTMCH1:
			if(FTM1_CH1 == (PORTA|9))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 9) = PORT_PCR_MUX(3);  // PTA9
			}
			else if(FTM1_CH1 == (PORTA|13))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 13) = PORT_PCR_MUX(3);  // PTA13
			}
			else if(FTM1_CH1 == (PORTB|1))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
				PORT_PCR_REG(PORTB_BASE_PTR, 1) = PORT_PCR_MUX(3);  // PTB1
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		default:
			return 3;
		}
		break;
	case FTM2:
		SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;                           //使能FTM2时钟
		switch(channel)
		{
		case FTMCH0:
			if(FTM2_CH0 == (PORTA|10))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 10) = PORT_PCR_MUX(3);  // PTA10
			}
			else if(FTM2_CH0 == (PORTB|18))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 18) = PORT_PCR_MUX(3);  // PTB18
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		case FTMCH1:
			if(FTM2_CH1 == (PORTA|11))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 11) = PORT_PCR_MUX(3);  // PTA11
			}
			else if(FTM2_CH1 == (PORTB|19))
			{
				SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
				PORT_PCR_REG(PORTA_BASE_PTR, 19) = PORT_PCR_MUX(3);  // PTB19
			}
			else
			{
				return 3;                     //设置管脚有误？
			}
			break;

		default:
			return 3;
		}
		break;
	default:
		break;
	}
	/******************** 选择输出模式为 边沿对齐PWM *******************/
	//通道状态控制，根据模式来选择 边沿或电平
	FTM_CnSC_REG(FTMx[ftmModule], channel) &= ~FTM_CnSC_ELSA_MASK;
	FTM_CnSC_REG(FTMx[ftmModule], channel) = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	//MSnB:MSnA = 1x
	// ELSnB:ELSnA = 10   High-true pulses  (clear Output on match)
	// ELSnB:ELSnA = 11   Low-true pulses   (set Output on match)
	// Edge-aligned PWM  边沿对齐PWM波   《k16 reference manual.pdf》  P944  或者  《K60P144M100SF2RM.pdf》P1001


	/******************** 配置时钟和分频 ********************/
	FTM_SC_REG(FTMx[ftmModule])    = FTM_SC_CPWMS_MASK | FTM_SC_PS(sc_ps) | FTM_SC_CLKS(1);  //没有使能溢出中断
	FTM_CNTIN_REG(FTMx[ftmModule]) = 0;                                                      // Channel (n) Value  。设置脉冲宽度：(CnV - CNTIN).
	FTM_MOD_REG(FTMx[ftmModule])   = mod;                                                    //Modulo value模数, EPWM的周期为 ：MOD - CNTIN + 0x0001
	FTM_CNTIN_REG(FTMx[ftmModule]) = 0;                                                      //Counter Initial Value 计数器初始化值
	FTM_CnV_REG(FTMx[ftmModule], channel) = cv;
	FTM_CNT_REG(FTMx[ftmModule])   = 0;                                                      //计数器。只有低16位可用
	FTM_OUTINIT_REG(FTMx[ftmModule])=0;
	return 0;
}

//=========================================================================
//函数名称：pwm_set
//功能概要：设置pwm模块。
//参数说明：ftmModule_channel:模块号：0、1、2  通道号:0-6 详见pwm.h文件定义
//			period：周期 单位微秒（比如0.1ms为100,1ms为1000）
//			duty：占空比    0~PWM_ACCURACY(在PWM.h中定义)
//函数返回：无
//=========================================================================
uint8_t pwm_set(uint8_t ftmModule, uint8_t channel, uint32_t period, uint16_t duty)
{
	uint32_t clk_hz = (bus_clk_khz * 1000) >> 1;        //bus频率/2
	uint16_t cv;
	uint16_t mod;
    uint8_t sc_ps;

	if(!( (ftmModule == FTM0) || ( (ftmModule == FTM1 || ftmModule == FTM2 ) && (channel <= FTMCH1)) )) //检查传递进来的通道是否正确
		return 1;
	if(!( period <= (clk_hz >> 1) ))    //检测 频率 是否正常 ,频率必须小于时钟二分之一
		return 2;
	if(!(duty <= PWM_ACCURACY))     //检测 占空比是否合理
		return 3;


	//占空比 = (CnV-CNTIN)/(MOD-CNTIN+1)
	mod = FTM_MOD_REG(FTMx[ftmModule]);        //读取 MOD 的值


	// 配置FTM通道值
	//FTM_CnV_REG(FTMx[ftmModule], channel) = cv;

	/*       计算频率设置        */
	mod = (clk_hz >> 16 ) / period ;
	for(sc_ps = 0; (mod >> sc_ps) >= 1; sc_ps++);
	mod = (clk_hz >> sc_ps) / period;
	//if(period < 1000)sc_ps++;
	cv = (duty * (mod - 0 + 1)) / PWM_ACCURACY;

	/******************** 配置时钟和分频 ********************/
	FTM_SC_REG(FTMx[ftmModule])    = FTM_SC_CPWMS_MASK | FTM_SC_PS(sc_ps) | FTM_SC_CLKS(1);  //没有使能溢出中断
	FTM_CNTIN_REG(FTMx[ftmModule]) = 0;                                                      // Channel (n) Value  。设置脉冲宽度：(CnV - CNTIN).
	FTM_MOD_REG(FTMx[ftmModule])   = mod;                                                    //Modulo value模数, EPWM的周期为 ：MOD - CNTIN + 0x0001
	FTM_CNTIN_REG(FTMx[ftmModule]) = 0;                                                      //Counter Initial Value 计数器初始化值
	FTM_CnV_REG(FTMx[ftmModule], channel) = cv;                                                    //计数器。只有低16位可用
	FTM_OUTINIT_REG(FTMx[ftmModule])=0;
	return 0;
}
