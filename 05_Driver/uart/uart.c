//============================================================================
//文件名称：uart.c
//功能概要：uart底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2014-10-15   V2.0
//============================================================================
#include "uart.h"


//====================接口函数实现============================================

//========================================================================
//函数名称：uart_init
//功能概要：初始化uart模块
//参数说明：uartNo:串口号：UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//          sel_clk:选择串口时钟源:
//                内核时钟   (96000Khz)
//		  总线时钟    (48000khz)
//          baud:波特率：300、600、1200、2400、4800、9600、19200、115200...
//函数返回：无
//=========================================================================
uint8_t uart_init(uint8_t uartNo, uint32_t baud)
{
    register uint16_t sbr;
    uint8_t temp;
    uint32_t sel_clk;
    UART_MemMapPtr uartch = UART_ARR[uartNo];

    //使能引脚功能并启动引脚时钟
    switch (uartNo)
    {
    case 0:
    	#if (UART_0_GROUP==1)
            PORTA_PCR1 = PORT_PCR_MUX(0x2); //使能UART0_TXD
            PORTA_PCR2 = PORT_PCR_MUX(0x2); //使能UART0_RXD
        #endif

        #if (UART_0_GROUP==2)
            PORTA_PCR14 = PORT_PCR_MUX(0x2); //使能UART0_TXD
       	    PORTA_PCR15 = PORT_PCR_MUX(0x2); //使能UART0_RXD
        #endif

        #if (UART_0_GROUP==3)
       	    PORTB_PCR17 = PORT_PCR_MUX(0x2); //使能UART0_TXD
       	    PORTB_PCR16 = PORT_PCR_MUX(0x2); //使能UART0_RXD
        #endif

        #if (UART_0_GROUP==4)
       	    PORTD_PCR7 = PORT_PCR_MUX(0x2); //使能UART0_TXD
            PORTD_PCR6 = PORT_PCR_MUX(0x2); //使能UART0_RXD
        #endif

        BSET(SIM_SCGC4_UART0_SHIFT, SIM_SCGC4);//启动串口0时钟
       	break;
    case 1:
        #if (UART_1_GROUP==1)
            PORTC_PCR4 = PORT_PCR_MUX(0x3); //使能UART1_TXD
            PORTC_PCR3 = PORT_PCR_MUX(0x3); //使能UART1_RXD
        #endif

        #if (UART_1_GROUP==2)
            PORTE_PCR0 = PORT_PCR_MUX(0x3); //使能UART1_TXD
            PORTE_PCR1 = PORT_PCR_MUX(0x3); //使能UART1_RXD
        #endif

        BSET(SIM_SCGC4_UART1_SHIFT, SIM_SCGC4); //启动串口1时钟
        break;
    case 2:
    	#if (UART_2_GROUP==1)
            PORTD_PCR3 = PORT_PCR_MUX(0x3); //使能UART2_TXD
            PORTD_PCR2 = PORT_PCR_MUX(0x3); //使能UART2_RXD
        #endif

            BSET(SIM_SCGC4_UART2_SHIFT, SIM_SCGC4);//启动串口2时钟
            break;
    case 3:
        #if (UART_3_GROUP==1)
            PORTB_PCR11 = PORT_PCR_MUX(0x3); //使能UART3_TXD
            PORTB_PCR10 = PORT_PCR_MUX(0x3); //使能UART3_RXD
    	#endif

    	#if (UART_3_GROUP==2)
            PORTC_PCR17 = PORT_PCR_MUX(0x3); //使能UART3_TXD
            PORTC_PCR16 = PORT_PCR_MUX(0x3); //使能UART3_RXD
        #endif

    	#if (UART_3_GROUP==3)
            PORTE_PCR4 = PORT_PCR_MUX(0x3); //使能UART3_TXD
            PORTE_PCR5 = PORT_PCR_MUX(0x3); //使能UART3_RXD
        #endif

        BSET(SIM_SCGC4_UART3_SHIFT, SIM_SCGC4);//启动串口3时钟
        break;
    case 4:
    	#if (UART_4_GROUP==1)
            PORTC_PCR15 = PORT_PCR_MUX(0x3); //使能UART4_TXD
            PORTC_PCR14 = PORT_PCR_MUX(0x3); //使能UART4_RXD
    	#endif

        #if (UART_4_GROUP==2)
            PORTE_PCR24 = PORT_PCR_MUX(0x3); //使能UART4_TXD
            PORTE_PCR25 = PORT_PCR_MUX(0x3); //使能UART4_RXD
    	#endif

        BSET(SIM_SCGC1_UART4_SHIFT, SIM_SCGC1); //启动串口4时钟
        break;
    case 5:
    	#if (UART_5_GROUP==1)
            PORTD_PCR9 = PORT_PCR_MUX(0x3); //使能UART4_TXD
            PORTD_PCR8 = PORT_PCR_MUX(0x3); //使能UART4_RXD
    	#endif

    	#if (UART_5_GROUP==2)
            PORTE_PCR8 = PORT_PCR_MUX(0x3); //使能UART5_TXD
            PORTE_PCR9 = PORT_PCR_MUX(0x3); //使能UART5_RXD
    	#endif

        BSET(SIM_SCGC1_UART5_SHIFT, SIM_SCGC1);//启动串口2时钟
        break;
    default:
        return 1;  //传参错误，返回
        }

    //暂时关闭串口发送与接收功能
    uartch->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

	//配置串口工作模式,8位无校验模式
	uartch->C1 = 0;


    //配置波特率
    //串口0、1使用的内核时钟是其它串口使用外设时钟频率的2倍
    if (UART_0 == uartNo || UART_1 == uartNo)
        sel_clk=CORE_CLK_KHz;
    else
    	sel_clk=BUS_CLK_KHz;
    
    sbr = (uint16_t)((sel_clk*1000)/(baud * 16));
    temp = UART_BDH_REG(uartch) & ~(UART_BDH_SBR(0x1F));
    UART_BDH_REG(uartch) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(uartch) = (uint8_t)(sbr & UART_BDL_SBR_MASK);
    
    //初始化控制寄存器、清标志位
    uartch->C1 = 0x00;
    uartch->C3 = 0x00;
    uartch->S1 = 0x1F;
    uartch->S2 = 0x00;

    //启动发送接收
    UART_C2_REG(uartch) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
    return 0;
}


//============================================================================
//函数名称：uart_send1
//参数说明：uartNo: 串口号:UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//          ch:要发送的字节
//函数返回：函数执行状态：0=正常；非0=异常。
//功能概要：串行发送1个字节
//============================================================================
uint8_t uart_send1(uint8_t uartNo, uint8_t ch)
{
    uint32_t t;
    UART_MemMapPtr uartch = UART_ARR[uartNo]; //获取UART1或者2基地址

    for (t = 0; t < 0xFBBB; t++)//查询指定次数
    {
        if ( (uartch->S1) & UART_S1_TDRE_MASK )//判断发送缓冲区是否为空
        {
	    uartch->D = ch;   //获取数据并发送
	    break;             //跳出循环
        }
   }//end for
   if (t >= 0xFBBB)
       return 1; //发送超时，发送失败
   else
       return 0; //成功发送

}


//============================================================================
//函数名称：uart_sendN
//参数说明：uartNo: 串口号:UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//          buff: 发送缓冲区
//          len:发送长度
//函数返回： 函数执行状态：0=正常；1=异常
//功能概要：串行 接收n个字节   
//============================================================================
uint8_t uart_sendN (uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        if (uart_send1(uartNo, buff[i])) //发送一个字节数据，失败则跳出循环
        {
            break;
        }
    }
    if (i < len)
        return 1;   //发送len个字节出错
    else
        return 0;   //发送len个字节成功
}


//============================================================================
//函数名称：uart_send_string
//参数说明：uartNo:UART模块号:UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//          buff:要发送的字符串的首地址
//函数返回： 函数执行状态：0=正常；非0=异常。
//功能概要：从指定UART端口发送一个以'\0'结束的字符串
//============================================================================
uint8_t uart_send_string(uint8_t uartNo, void *buff)
{
    uint16_t i = 0;
    uint8_t *buff_ptr = (uint8_t *)buff;    //定义指针指向要发送字符串首地址
    for(i = 0; buff_ptr[i] != '\0'; i++)  //遍历字符串里的字符
    {
        if (uart_send1(uartNo,buff_ptr[i]))//发送指针对应的字符
            return 1;  //发送失败
    }
    return 0;         //发送成功
}


//============================================================================
//函数名称：uart_re1
//参数说明：uartNo: 串口号:UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//          fp:接收成功标志的指针:*fp=0，成功接收；*fp=1，接收失败
//函数返回：接收返回字节
//功能概要：串行接收1个字节
//============================================================================
uint8_t uart_re1 (uint8_t uartNo,uint8_t *fp)
{
    uint32_t t;
    uint8_t  dat;
    UART_MemMapPtr uartch= UART_ARR[uartNo];//获取UART1或者2基地址

    for (t = 0; t < 0xFBBB; t++)//查询指定次数
    {
    	//判断接收缓冲区是否满
        if ((uartch->S1) & UART_S1_RDRF_MASK )
        {
        	dat = uartch->D; //获取数据
        	*fp= 0;  //接受成功
        	break;
        }

    }//end for
    if(t >= 0xFBBB)
    {
        dat = 0xFF;
        *fp = 1;    //未收到数据
    }
    return dat;    //返回接收到的数据

}


//============================================================================
//函数名称：uart_reN
//参数说明：uartNo: 串口号:UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//          buff: 接收缓冲区
//          len:接收长度
//函数返回：函数执行状态 0=正常;非0=异常
//功能概要：串行 接收n个字节
//============================================================================
uint8_t uart_reN (uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;
    uint8_t flag = 0;

    //判断是否能接受数据
    for (i = 0; i < len && 0 == flag; i++)
    {
        buff[i] = uart_re1(uartNo, &flag); //接受数据
    }
    if (i < len)
        return 1; //接收失败
    else
        return 0; //接收成功
}


//============================================================================
//函数名称：uart_enable_re_int
//参数说明：uartNo: 串口号:UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//函数返回：无
//功能概要：开串口接收中断
//============================================================================
void uart_enable_re_int(uint8_t uartNo)
{
    UART_MemMapPtr uartch = UART_ARR[uartNo];
    uartch->C2 |= UART_C2_RIE_MASK;        //开放UART接收中断
    enable_irq(table_irq_uart[uartNo]);   //开中断控制器IRQ中断
}


//============================================================================
//函数名称：uart_disable_re_int
//参数说明：uartNo: 串口号 :UART_0、UART_1、UART_2、UART_3、UART_4、UART_5
//函数返回：无
//功能概要：关串口接收中断
//============================================================================
void uart_disable_re_int(uint8_t uartNo)
{
    UART_MemMapPtr uartch = UART_ARR[uartNo];
	uartch->C2 &= ~UART_C2_RIE_MASK;           //禁止UART接收中断
	disable_irq(table_irq_uart[uartNo]);       //禁止中断控制器IRQ中断
}

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT) //用于CRC校验
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}
void OutPut_Data(float OutData[4])//将四个通道数据加上校验发送出去
{
          int32_t temp[4] = {0};

         uint32_t temp1[4] = {0};

          unsigned char databuf[10] = {0};
          unsigned char i;
          unsigned short CRC16 = 0;
          for(i=0;i<4;i++)
           {

            temp[i]  = (int32_t)OutData[i];
            temp1[i] = (uint32_t)temp[i];
           }

          for(i=0;i<4;i++)
          {
            databuf[i*2]   = (unsigned char)(temp1[i]%256);
            databuf[i*2+1] = (unsigned char)(temp1[i]/256);
           }

  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;

  for(i=0;i<10;i++)
   uart_send1(5, databuf[i]);
}

////使用说明
////如，显示事实速度变量Speed
////  OutData[0]=(int16)Speed;//OutData[0]为1通道，类似OutData[1]为2通道。
////  OutPut_Data();
//float OutData[4];
//void uart_putchar (UART_MemMapPtr channel, char ch)
//{
//    while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));
//    UART_D_REG(channel) = (uint8_t)ch;
// }
//
//unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
//{
//    unsigned short CRC_Temp;
//    unsigned char i,j;
//    CRC_Temp = 0xffff;
//
//    for (i=0;i<CRC_CNT; i++){
//        CRC_Temp ^= Buf[i];
//        for (j=0;j<8;j++) {
//            if (CRC_Temp & 0x01)
//                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
//            else
//                CRC_Temp = CRC_Temp >> 1;
//        }
//    }
//    return(CRC_Temp);
//}
//
//void OutPut_Data()
//{
//  int temp[4] = {0};
//  unsigned int temp1[4] = {0};
//  unsigned char databuf[10] = {0};
//  unsigned char i;
//  unsigned short CRC16 = 0;
//  for(i=0;i<4;i++)
//   {
//
//    temp[i]  = (int16_t)OutData[i];
//    temp1[i] = (uint16_t)temp[i];
//
//   }
//
//  for(i=0;i<4;i++)
//  {
//    databuf[i*2]   = (int8_t)(temp1[i]%256);
//    databuf[i*2+1] = (int8_t)(temp1[i]/256);
//  }
//
//  CRC16 = CRC_CHECK(databuf,8);
//  databuf[8] = CRC16%256;
//  databuf[9] = CRC16/256;
//
//  for(i=0;i<10;i++)
//  uart_send1(5,databuf[i]);
//}



