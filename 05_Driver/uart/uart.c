//============================================================================
//�ļ����ƣ�uart.c
//���ܸ�Ҫ��uart�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2014-10-15   V2.0
//============================================================================
#include "uart.h"


//====================�ӿں���ʵ��============================================

//========================================================================
//�������ƣ�uart_init
//���ܸ�Ҫ����ʼ��uartģ��
//����˵����uartNo:���ںţ�UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//          sel_clk:ѡ�񴮿�ʱ��Դ:
//                �ں�ʱ��   (96000Khz)
//		  ����ʱ��    (48000khz)
//          baud:�����ʣ�300��600��1200��2400��4800��9600��19200��115200...
//�������أ���
//=========================================================================
uint8_t uart_init(uint8_t uartNo, uint32_t baud)
{
    register uint16_t sbr;
    uint8_t temp;
    uint32_t sel_clk;
    UART_MemMapPtr uartch = UART_ARR[uartNo];

    //ʹ�����Ź��ܲ���������ʱ��
    switch (uartNo)
    {
    case 0:
    	#if (UART_0_GROUP==1)
            PORTA_PCR1 = PORT_PCR_MUX(0x2); //ʹ��UART0_TXD
            PORTA_PCR2 = PORT_PCR_MUX(0x2); //ʹ��UART0_RXD
        #endif

        #if (UART_0_GROUP==2)
            PORTA_PCR14 = PORT_PCR_MUX(0x2); //ʹ��UART0_TXD
       	    PORTA_PCR15 = PORT_PCR_MUX(0x2); //ʹ��UART0_RXD
        #endif

        #if (UART_0_GROUP==3)
       	    PORTB_PCR17 = PORT_PCR_MUX(0x2); //ʹ��UART0_TXD
       	    PORTB_PCR16 = PORT_PCR_MUX(0x2); //ʹ��UART0_RXD
        #endif

        #if (UART_0_GROUP==4)
       	    PORTD_PCR7 = PORT_PCR_MUX(0x2); //ʹ��UART0_TXD
            PORTD_PCR6 = PORT_PCR_MUX(0x2); //ʹ��UART0_RXD
        #endif

        BSET(SIM_SCGC4_UART0_SHIFT, SIM_SCGC4);//��������0ʱ��
       	break;
    case 1:
        #if (UART_1_GROUP==1)
            PORTC_PCR4 = PORT_PCR_MUX(0x3); //ʹ��UART1_TXD
            PORTC_PCR3 = PORT_PCR_MUX(0x3); //ʹ��UART1_RXD
        #endif

        #if (UART_1_GROUP==2)
            PORTE_PCR0 = PORT_PCR_MUX(0x3); //ʹ��UART1_TXD
            PORTE_PCR1 = PORT_PCR_MUX(0x3); //ʹ��UART1_RXD
        #endif

        BSET(SIM_SCGC4_UART1_SHIFT, SIM_SCGC4); //��������1ʱ��
        break;
    case 2:
    	#if (UART_2_GROUP==1)
            PORTD_PCR3 = PORT_PCR_MUX(0x3); //ʹ��UART2_TXD
            PORTD_PCR2 = PORT_PCR_MUX(0x3); //ʹ��UART2_RXD
        #endif

            BSET(SIM_SCGC4_UART2_SHIFT, SIM_SCGC4);//��������2ʱ��
            break;
    case 3:
        #if (UART_3_GROUP==1)
            PORTB_PCR11 = PORT_PCR_MUX(0x3); //ʹ��UART3_TXD
            PORTB_PCR10 = PORT_PCR_MUX(0x3); //ʹ��UART3_RXD
    	#endif

    	#if (UART_3_GROUP==2)
            PORTC_PCR17 = PORT_PCR_MUX(0x3); //ʹ��UART3_TXD
            PORTC_PCR16 = PORT_PCR_MUX(0x3); //ʹ��UART3_RXD
        #endif

    	#if (UART_3_GROUP==3)
            PORTE_PCR4 = PORT_PCR_MUX(0x3); //ʹ��UART3_TXD
            PORTE_PCR5 = PORT_PCR_MUX(0x3); //ʹ��UART3_RXD
        #endif

        BSET(SIM_SCGC4_UART3_SHIFT, SIM_SCGC4);//��������3ʱ��
        break;
    case 4:
    	#if (UART_4_GROUP==1)
            PORTC_PCR15 = PORT_PCR_MUX(0x3); //ʹ��UART4_TXD
            PORTC_PCR14 = PORT_PCR_MUX(0x3); //ʹ��UART4_RXD
    	#endif

        #if (UART_4_GROUP==2)
            PORTE_PCR24 = PORT_PCR_MUX(0x3); //ʹ��UART4_TXD
            PORTE_PCR25 = PORT_PCR_MUX(0x3); //ʹ��UART4_RXD
    	#endif

        BSET(SIM_SCGC1_UART4_SHIFT, SIM_SCGC1); //��������4ʱ��
        break;
    case 5:
    	#if (UART_5_GROUP==1)
            PORTD_PCR9 = PORT_PCR_MUX(0x3); //ʹ��UART4_TXD
            PORTD_PCR8 = PORT_PCR_MUX(0x3); //ʹ��UART4_RXD
    	#endif

    	#if (UART_5_GROUP==2)
            PORTE_PCR8 = PORT_PCR_MUX(0x3); //ʹ��UART5_TXD
            PORTE_PCR9 = PORT_PCR_MUX(0x3); //ʹ��UART5_RXD
    	#endif

        BSET(SIM_SCGC1_UART5_SHIFT, SIM_SCGC1);//��������2ʱ��
        break;
    default:
        return 1;  //���δ��󣬷���
        }

    //��ʱ�رմ��ڷ�������չ���
    uartch->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

	//���ô��ڹ���ģʽ,8λ��У��ģʽ
	uartch->C1 = 0;


    //���ò�����
    //����0��1ʹ�õ��ں�ʱ������������ʹ������ʱ��Ƶ�ʵ�2��
    if (UART_0 == uartNo || UART_1 == uartNo)
        sel_clk=CORE_CLK_KHz;
    else
    	sel_clk=BUS_CLK_KHz;
    
    sbr = (uint16_t)((sel_clk*1000)/(baud * 16));
    temp = UART_BDH_REG(uartch) & ~(UART_BDH_SBR(0x1F));
    UART_BDH_REG(uartch) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(uartch) = (uint8_t)(sbr & UART_BDL_SBR_MASK);
    
    //��ʼ�����ƼĴ��������־λ
    uartch->C1 = 0x00;
    uartch->C3 = 0x00;
    uartch->S1 = 0x1F;
    uartch->S2 = 0x00;

    //�������ͽ���
    UART_C2_REG(uartch) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
    return 0;
}


//============================================================================
//�������ƣ�uart_send1
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//          ch:Ҫ���͵��ֽ�
//�������أ�����ִ��״̬��0=��������0=�쳣��
//���ܸ�Ҫ�����з���1���ֽ�
//============================================================================
uint8_t uart_send1(uint8_t uartNo, uint8_t ch)
{
    uint32_t t;
    UART_MemMapPtr uartch = UART_ARR[uartNo]; //��ȡUART1����2����ַ

    for (t = 0; t < 0xFBBB; t++)//��ѯָ������
    {
        if ( (uartch->S1) & UART_S1_TDRE_MASK )//�жϷ��ͻ������Ƿ�Ϊ��
        {
	    uartch->D = ch;   //��ȡ���ݲ�����
	    break;             //����ѭ��
        }
   }//end for
   if (t >= 0xFBBB)
       return 1; //���ͳ�ʱ������ʧ��
   else
       return 0; //�ɹ�����

}


//============================================================================
//�������ƣ�uart_sendN
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//          buff: ���ͻ�����
//          len:���ͳ���
//�������أ� ����ִ��״̬��0=������1=�쳣
//���ܸ�Ҫ������ ����n���ֽ�   
//============================================================================
uint8_t uart_sendN (uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        if (uart_send1(uartNo, buff[i])) //����һ���ֽ����ݣ�ʧ��������ѭ��
        {
            break;
        }
    }
    if (i < len)
        return 1;   //����len���ֽڳ���
    else
        return 0;   //����len���ֽڳɹ�
}


//============================================================================
//�������ƣ�uart_send_string
//����˵����uartNo:UARTģ���:UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//          buff:Ҫ���͵��ַ������׵�ַ
//�������أ� ����ִ��״̬��0=��������0=�쳣��
//���ܸ�Ҫ����ָ��UART�˿ڷ���һ����'\0'�������ַ���
//============================================================================
uint8_t uart_send_string(uint8_t uartNo, void *buff)
{
    uint16_t i = 0;
    uint8_t *buff_ptr = (uint8_t *)buff;    //����ָ��ָ��Ҫ�����ַ����׵�ַ
    for(i = 0; buff_ptr[i] != '\0'; i++)  //�����ַ�������ַ�
    {
        if (uart_send1(uartNo,buff_ptr[i]))//����ָ���Ӧ���ַ�
            return 1;  //����ʧ��
    }
    return 0;         //���ͳɹ�
}


//============================================================================
//�������ƣ�uart_re1
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//          fp:���ճɹ���־��ָ��:*fp=0���ɹ����գ�*fp=1������ʧ��
//�������أ����շ����ֽ�
//���ܸ�Ҫ�����н���1���ֽ�
//============================================================================
uint8_t uart_re1 (uint8_t uartNo,uint8_t *fp)
{
    uint32_t t;
    uint8_t  dat;
    UART_MemMapPtr uartch= UART_ARR[uartNo];//��ȡUART1����2����ַ

    for (t = 0; t < 0xFBBB; t++)//��ѯָ������
    {
    	//�жϽ��ջ������Ƿ���
        if ((uartch->S1) & UART_S1_RDRF_MASK )
        {
        	dat = uartch->D; //��ȡ����
        	*fp= 0;  //���ܳɹ�
        	break;
        }

    }//end for
    if(t >= 0xFBBB)
    {
        dat = 0xFF;
        *fp = 1;    //δ�յ�����
    }
    return dat;    //���ؽ��յ�������

}


//============================================================================
//�������ƣ�uart_reN
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//          buff: ���ջ�����
//          len:���ճ���
//�������أ�����ִ��״̬ 0=����;��0=�쳣
//���ܸ�Ҫ������ ����n���ֽ�
//============================================================================
uint8_t uart_reN (uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;
    uint8_t flag = 0;

    //�ж��Ƿ��ܽ�������
    for (i = 0; i < len && 0 == flag; i++)
    {
        buff[i] = uart_re1(uartNo, &flag); //��������
    }
    if (i < len)
        return 1; //����ʧ��
    else
        return 0; //���ճɹ�
}


//============================================================================
//�������ƣ�uart_enable_re_int
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//�������أ���
//���ܸ�Ҫ�������ڽ����ж�
//============================================================================
void uart_enable_re_int(uint8_t uartNo)
{
    UART_MemMapPtr uartch = UART_ARR[uartNo];
    uartch->C2 |= UART_C2_RIE_MASK;        //����UART�����ж�
    enable_irq(table_irq_uart[uartNo]);   //���жϿ�����IRQ�ж�
}


//============================================================================
//�������ƣ�uart_disable_re_int
//����˵����uartNo: ���ں� :UART_0��UART_1��UART_2��UART_3��UART_4��UART_5
//�������أ���
//���ܸ�Ҫ���ش��ڽ����ж�
//============================================================================
void uart_disable_re_int(uint8_t uartNo)
{
    UART_MemMapPtr uartch = UART_ARR[uartNo];
	uartch->C2 &= ~UART_C2_RIE_MASK;           //��ֹUART�����ж�
	disable_irq(table_irq_uart[uartNo]);       //��ֹ�жϿ�����IRQ�ж�
}

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT) //����CRCУ��
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
void OutPut_Data(float OutData[4])//���ĸ�ͨ�����ݼ���У�鷢�ͳ�ȥ
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

////ʹ��˵��
////�磬��ʾ��ʵ�ٶȱ���Speed
////  OutData[0]=(int16)Speed;//OutData[0]Ϊ1ͨ��������OutData[1]Ϊ2ͨ����
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


