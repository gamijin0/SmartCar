/****************************************************************************
 * Copyright (c) 2013 ���ݴ�ѧ��˼����ʵ����(��Ȩ����)
 * All rights reserved.
*
 * @file     sysint.c
 * @brief    sysint����Դ�ļ�
 * @version  V1.00
 * @date     2014��05��17��
 * @note     �޶�˵����V1.00 ʵ����sysint��������
 *                    V2.0 jjw�޸�SystemClockSetup����
 ***************************************************************************/
#include "sysint.h"

uint32_t SystemCoreClock;

CPUInfoType_t CPUInfo; //������������Ϣ�ṹ��

/** 
 * @brief  ����/����ϵͳ��Ƶ��
 * @param  ClockOption  ʱ��Դѡ��,ѡ�����£�
 *                         ClockSource_IRC    : �ڲ�ʱ��Դ
 *                         ClockSource_EX4M   : �ⲿ4M����
 *                         ClockSource_EX50M  : �ⲿ50M����
 * @param  CoreClock    ϣ���õ����ں�Ƶ��
 *                         CoreClock_48M  : CoreClock = 48M
 *                         CoreClock_64M  : CoreClock = 64M
 *                         CoreClock_72M  : CoreClock = 72M
 *                         CoreClock_96M  : CoreClock = 96M
 *                         CoreClock_100M : CoreClock = 100M                    
 * @retval None
 * 
 * ʹ�øú�����ѡ��ʱ��Դ������Ƶ�õ�ϣ�����ں�ʱ�ӡ�
 */
void SystemClockSetup(uint8_t ClockOption,uint16_t CoreClock)
{
    if(ClockOption == ClockSource_IRC)
    {
        // ���� FEI ģʽ
        MCG_C1 = (uint8_t)0x06u;  //�ڲ�32KHzʱ�ӱ�ѡ��
        MCG_C2 = (uint8_t)0x00u;
        MCG_C4 &= ~((1<<6)|(1<<7)|(1<<5));
        switch(CoreClock)
        {
            case CoreClock_96M:
                MCG_C4|= (1<<6)|(1<<7)|(1<<5);  
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                        |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));
                SystemCoreClock    = 96000000;
                break;
            case CoreClock_72M:
                MCG_C4|= (1<<6)|(1<<7)|(0<<5);  
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                        |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(2));    
                SystemCoreClock    = 72000000;
                break;
            case CoreClock_48M:
                MCG_C4|= (0<<6)|(1<<7)|(1<<5);  
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)
                        |SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));    
                SystemCoreClock    = 48000000;
                break;
            default: //48M
                MCG_C4|= (0<<6)|(1<<7)|(1<<5);  
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)
                        |SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));    
                SystemCoreClock    = 48000000;
                break;
        }
        MCG_C5 = (uint8_t)0x00u;
        MCG_C6 = (uint8_t)0x00u;
        while((MCG_S & MCG_S_IREFST_MASK) == 0u);  //��� FLL�ο�ʱ�����ڲ��ο�ʱ��
        while((MCG_S & 0x0Cu) != 0x00u);           //�ȴ�FLL��ѡ��
    }
    if(ClockOption == ClockSource_EX4M || ClockOption == ClockSource_EX50M)
    {
        SIM_SCGC5 |= (uint32_t)0x0200UL; // ʹ������ʱ���ſأ����ⲿ���ʱ��Դ
        if ( *((uint8_t*) 0x03FFU) != 0xFFU) 
        {
            MCG_C3 = *((uint8_t*) 0x03FFU);
            MCG_C4 = (MCG_C4 & 0xE0U) | ((*((uint8_t*) 0x03FEU)) & 0x1FU);
        }
        SIM_CLKDIV1 = (uint32_t)0x01130000UL; // ����ʱ��ϵͳԤ��Ƶ
        SIM_CLKDIV2 = (uint32_t)((SIM_CLKDIV2 & (uint32_t)~0x0DUL) 
                    | (uint32_t)0x02UL);      // ����USBʱ�����Ƶ
        SIM_SOPT2 |= (uint32_t)0x00010000UL;  // ѡ��PLLΪ����ʱ��Դ
        SIM_SOPT1 |= (uint32_t)0x00080000UL;  // ����32kHzʱ��Դ
        PORTA_PCR18 &= (uint32_t)~0x01000700UL;
        
        //���� FEI ģʽ��ת�� FBE ģʽ 
        OSC_CR = (uint8_t)0x00u;
        SIM_SOPT2 &= (uint8_t)~(uint8_t)0x01u;
        MCG_C2 = (uint8_t)0x21u;    //ѡ���ⲿ��Ƶ�ο�ʱ��
        MCG_C1 = (uint8_t)0xA8u;    //ѡ���ⲿ�ο�ʱ�ӣ���Ƶ����Ϊ1024

        while((MCG_S & MCG_S_IREFST_MASK) != 0u); //��� FLL�ο�ʱ�����ⲿ�ο�ʱ��
        while((MCG_S & 0x0Cu) != 0x08u);          //�ȴ��ⲿ�ο�ʱ�ӱ�ѡ��ΪMCG���
        
        //����FBE��ת��PBEģʽ
        if(ClockOption == ClockSource_EX4M)
        {
            MCG_C5 = (uint8_t)(0x20|MCG_C5_PRDIV(1));        //4/2 = 2M
        }
        else if (ClockOption == ClockSource_EX50M)
        {
            MCG_C5 = (uint8_t)(0x20|MCG_C5_PRDIV(24));       //50/25 = 2M
        }
        switch(CoreClock)
        {
            case CoreClock_48M:
                MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(0));
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)
                        |SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));    
                SystemCoreClock    = 48000000;
                break;        
            case CoreClock_64M:
                MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(8));
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                        |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(2));
                SystemCoreClock    = 64000000;
                break;        
            case CoreClock_72M:
                MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(12));
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                        |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(2));
                SystemCoreClock    = 72000000;
                break;            
            case CoreClock_96M:
                MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(24));
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                        |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));        
                SystemCoreClock    = 96000000;
                break;        
            case CoreClock_100M:
                MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(26));
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                        |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));    
                SystemCoreClock    = 100000000;
                break;    
            case CoreClock_200M:
                if(ClockOption == ClockSource_EX4M)
                {
                    MCG_C5 = (uint8_t)MCG_C5_PRDIV(0);        //4/1 = 4M
                    MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(26));
                    SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                            |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(7));    
                }
                else if (ClockOption == ClockSource_EX50M)
                {
                    MCG_C5 = (uint8_t)MCG_C5_PRDIV(12);
                    MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(28));
                    SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)
                            |SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(7));    
                }
                SystemCoreClock    = 200000000;
                break;            
            default:
                MCG_C6 = (uint8_t)(0x40u|MCG_C6_VDIV(0));
                SIM_CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)
                        |SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));
                SystemCoreClock    = 48000000;
                break;
        } 
        while((MCG_S & 0x0Cu) != 0x08u);           //�ȴ��ⲿ�ο�ʱ�ӱ�ѡ��ΪMCG���    
        while((MCG_S & MCG_S_LOCK_MASK) == 0u);    //�ȴ�����
        
        //ת��PEE
        MCG_C1 = (uint8_t)0x28u;                   //ѡ��PLL����Ϊʱ��Դ
        while((MCG_S & 0x0Cu) != 0x0Cu);           //�ȴ�PLL���
        while((MCG_S & MCG_S_LOCK_MASK) == 0u);    //�ȴ�PLL����
        MCG_C6 |= (uint8_t)0x20U; // ʹ��ʱ�Ӽ��
    }
}
/** 
 * @brief  �����ж���������ʼλ�á�
 * @param  VectorOffset �ж��������ƫ��ֵ
 * @retval None
 * 
 * ���ж��������ƫ��ֵ����VTOR�Ĵ�����
 */
void SetVectorTable(uint32_t VectorOffset)
{
    //������
  //ASSERT(IS_VECTOR_OFFSET(VectorOffset));
  SCB_VTOR = VectorOffset;  //�����ж�������ƫ�Ƶ�ַ
}

void GetCPUInfo(void)
{
    //���Ȼ�ø�λ״̬��Ϣ
    if (MC_SRSH & MC_SRSH_SW_MASK)     CPUInfo.ResetState = 1;
    if (MC_SRSH & MC_SRSH_LOCKUP_MASK) CPUInfo.ResetState = 2;
    if (MC_SRSH & MC_SRSH_JTAG_MASK)   CPUInfo.ResetState = 3;
    if (MC_SRSL & MC_SRSL_POR_MASK)    CPUInfo.ResetState = 4;
    if (MC_SRSL & MC_SRSL_PIN_MASK)      CPUInfo.ResetState = 5;
    if (MC_SRSL & MC_SRSL_COP_MASK)    CPUInfo.ResetState = 6;
    if (MC_SRSL & MC_SRSL_LOC_MASK)    CPUInfo.ResetState = 7;
    if (MC_SRSL & MC_SRSL_LVD_MASK)    CPUInfo.ResetState = 8;
    if (MC_SRSL & MC_SRSL_WAKEUP_MASK) CPUInfo.ResetState = 9;
    //ȷ��Kinetisϵ���ͺ�
    switch((SIM_SDID & SIM_SDID_FAMID(0x7))>>SIM_SDID_FAMID_SHIFT) 
    {  
        case 0x0: CPUInfo.FamilyType = 10; break;
        case 0x1: CPUInfo.FamilyType = 20; break;
        case 0x2: CPUInfo.FamilyType = 30; break;
        case 0x3: CPUInfo.FamilyType = 40; break;
        case 0x4: CPUInfo.FamilyType = 60; break;
        case 0x5: CPUInfo.FamilyType = 70; break;
        case 0x6: CPUInfo.FamilyType = 50; break;
        case 0x7: CPUInfo.FamilyType = 53; break;
        default: CPUInfo.FamilyType = 0;  break;
    }
    //��װ��Ϣ
    switch((SIM_SDID & SIM_SDID_PINID(0xF))>>SIM_SDID_PINID_SHIFT) 
    {  
        case 0x02: CPUInfo.PinCnt = 32;  break;
        case 0x04: CPUInfo.PinCnt = 48;  break;
        case 0x05: CPUInfo.PinCnt = 64;  break;
        case 0x06: CPUInfo.PinCnt = 80;  break;
        case 0x07: CPUInfo.PinCnt = 81;  break;
        case 0x08: CPUInfo.PinCnt = 100; break;
        case 0x09: CPUInfo.PinCnt = 104; break;
        case 0x0A: CPUInfo.PinCnt = 144; break;
        case 0x0C: CPUInfo.PinCnt = 196; break;
         case 0x0E: CPUInfo.PinCnt = 256; break;
      default:  CPUInfo.PinCnt = 0;   break;    
    }  
   //SiliconRevID
    switch((SIM_SDID & SIM_SDID_REVID(0xF))>>SIM_SDID_REVID_SHIFT) 
    { 
            case 0x0: CPUInfo.SiliconRev = 10;break;
            case 0x1: CPUInfo.SiliconRev = 11;break;
            case 0x2: CPUInfo.SiliconRev = 12;break;
            default:  CPUInfo.SiliconRev = 0; break;
    }    
    //PFlash��С
    switch((SIM_FCFG1 & SIM_FCFG1_PFSIZE(0xF))>>SIM_FCFG1_PFSIZE_SHIFT)
    {
        case 0x7: CPUInfo.PFlashSize = 128*1024;break;
        case 0x9: CPUInfo.PFlashSize = 256*1024;break;
        case 0xB: CPUInfo.PFlashSize = 512*1024;break;
        case 0xF: CPUInfo.PFlashSize = 512*1024;break;
         default:  CPUInfo.PFlashSize = 0*1024;  break;         
    }
    //�����FlexNVM ȷ��FlexNVM��С
    if (SIM_FCFG2 & SIM_FCFG2_PFLSH_MASK) 
    {
        CPUInfo.FlexNVMSize = 0;
    }
    else
    {
        //ȷ��FLexNVM��С
        switch((SIM_FCFG1 & SIM_FCFG1_NVMSIZE(0xF))>>SIM_FCFG1_NVMSIZE_SHIFT)
        {
            case 0x0: CPUInfo.FlexNVMSize = 0;break;
            case 0x7: CPUInfo.FlexNVMSize = 128*1024;break;
            case 0x9: CPUInfo.FlexNVMSize = 256*1024;break;
            case 0xF: CPUInfo.FlexNVMSize = 256*1024;break;
            default:  CPUInfo.FlexNVMSize = 0;break;         
        }
    }
    //RAM��С
    switch((SIM_SOPT1 & SIM_SOPT1_RAMSIZE(0xF))>>SIM_SOPT1_RAMSIZE_SHIFT)
    {
        case 0x5: CPUInfo.RAMSize = 32*1024;  break;
        case 0x7: CPUInfo.RAMSize = 64*1024;  break;
        case 0x8: CPUInfo.RAMSize = 96*1024;  break;
        case 0x9: CPUInfo.RAMSize = 128*1024; break;
        default:  CPUInfo.RAMSize = 0*1024;   break;    
    }
    //ʱ�Ӽ���
    //SystemCoreClockUpdate();            //���¼���CoreClock
    CPUInfo.CoreClock = SystemCoreClock;
    CPUInfo.BusClock=(SystemCoreClock/(((SIM_CLKDIV1&SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1));     //����BusClock
    CPUInfo.FlexBusClock=(SystemCoreClock/(((SIM_CLKDIV1&SIM_CLKDIV1_OUTDIV3_MASK)>>SIM_CLKDIV1_OUTDIV3_SHIFT)+1)); //����FlexBusClock
    CPUInfo.FlashClock=(SystemCoreClock/(((SIM_CLKDIV1&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+1));   //����FlashClock
}
