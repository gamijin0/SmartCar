//============================================================================
//文件名称：vectors.h 
//功能概要：中断向量表 
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2011-11-13   V1.0     初始版本
//         2011-12-20   V1.1     规范排版
//============================================================================

#ifndef VECTORS_H
#define VECTORS_H

//#include "common.h"

//默认中断服务例程
extern void default_isr(void);
//extern void default_isr_1(void);

//typedef void pointer(void);

extern unsigned long _estack;
extern void __thumb_startup(void);
                                         // Address       Vector IRQ Source module   Source description
#define VECTOR_000      (void(*)(void)) &_estack	   //           ARM core        Initial Supervisor SP
#define VECTOR_001      __thumb_startup	// 0x0000_0004 1 -          ARM core        Initial Program Counter
#define VECTOR_002      default_isr     // 0x0000_0008 2 -          ARM core        Non-maskable Interrupt (NMI)
#define VECTOR_003      default_isr     // 0x0000_000C 3 -          ARM core        Hard Fault
#define VECTOR_004      default_isr     // 0x0000_0010 4 -
#define VECTOR_005      default_isr     // 0x0000_0014 5 -          ARM core         Bus Fault
#define VECTOR_006      default_isr     // 0x0000_0018 6 -          ARM core         Usage Fault
#define VECTOR_007      default_isr     // 0x0000_001C 7 -                           
#define VECTOR_008      default_isr     // 0x0000_0020 8 -                           
#define VECTOR_009      default_isr     // 0x0000_0024 9 -
#define VECTOR_010      default_isr     // 0x0000_0028 10 -
#define VECTOR_011      default_isr     // 0x0000_002C 11 -         ARM core         Supervisor call (SVCall)
#define VECTOR_012      default_isr     // 0x0000_0030 12 -         ARM core         Debug Monitor
#define VECTOR_013      default_isr     // 0x0000_0034 13 -                          
#define VECTOR_014      default_isr     // 0x0000_0038 14 -         ARM core         Pendable request for system service (PendableSrvReq)
#define VECTOR_015      default_isr     // 0x0000_003C 15 -         ARM core         System tick timer (SysTick)
#define VECTOR_016      default_isr     // 0x0000_0040 16     0     DMA              DMA Channel 0 transfer complete
#define VECTOR_017      default_isr     // 0x0000_0044 17     1     DMA              DMA Channel 1 transfer complete
#define VECTOR_018      default_isr     // 0x0000_0048 18     2     DMA              DMA Channel 2 transfer complete
#define VECTOR_019      default_isr     // 0x0000_004C 19     3     DMA              DMA Channel 3 transfer complete
#define VECTOR_020      default_isr     // 0x0000_0050 20     4     DMA              DMA Channel 4 transfer complete
#define VECTOR_021      default_isr     // 0x0000_0054 21     5     DMA              DMA Channel 5 transfer complete
#define VECTOR_022      default_isr     // 0x0000_0058 22     6     DMA              DMA Channel 6 transfer complete
#define VECTOR_023      default_isr     // 0x0000_005C 23     7     DMA              DMA Channel 7 transfer complete
#define VECTOR_024      default_isr     // 0x0000_0060 24     8     DMA              DMA Channel 8 transfer complete
#define VECTOR_025      default_isr     // 0x0000_0064 25     9     DMA              DMA Channel 9 transfer complete
#define VECTOR_026      default_isr     // 0x0000_0068 26    10     DMA              DMA Channel 10 transfer complete
#define VECTOR_027      default_isr     // 0x0000_006C 27    11     DMA              DMA Channel 11 transfer complete
#define VECTOR_028      default_isr     // 0x0000_0070 28    12     DMA              DMA Channel 12 transfer complete
#define VECTOR_029      default_isr     // 0x0000_0074 29    13     DMA              DMA Channel 13 transfer complete
#define VECTOR_030      default_isr     // 0x0000_0078 30    14     DMA              DMA Channel 14 transfer complete
#define VECTOR_031      default_isr     // 0x0000_007C 31    15     DMA              DMA Channel 15 transfer complete
#define VECTOR_032      default_isr     // 0x0000_0080 32    16     DMA              DMA Error Interrupt Channels 0-15
#define VECTOR_033      default_isr     // 0x0000_0084 33    17     MCM              Normal interrupt
#define VECTOR_034      default_isr     // 0x0000_0088 34    18     Flash memory     Command Complete
#define VECTOR_035      default_isr     // 0x0000_008C 35    19     Flash memory     Read Collision
#define VECTOR_036      default_isr     // 0x0000_0090 36    20     Mode Controller  Low Voltage Detect,Low Voltage Warning, Low Leakage Wakeup
#define VECTOR_037      default_isr     // 0x0000_0094 37    21     LLWU
#define VECTOR_038      default_isr     // 0x0000_0098 38    22     WDOG
#define VECTOR_039      default_isr     // 0x0000_009C 39    23		 RNGB
#define VECTOR_040      default_isr     // 0x0000_00A0 40    24     I2C0
#define VECTOR_041      default_isr     // 0x0000_00A4 41    25     I2C1
#define VECTOR_042      default_isr     // 0x0000_00A8 42    26     SPI0             Single interrupt vector for all sources
#define VECTOR_043      default_isr     // 0x0000_00AC 43    27     SPI1             Single interrupt vector for all sources
#define VECTOR_044      default_isr     // 0x0000_00B0 44    28     SPI2             Single interrupt vector for all sources
#define VECTOR_045      default_isr     // 0x0000_00B4 45    29     CAN0             OR'ed Message buffer (0-15)
#define VECTOR_046      default_isr     // 0x0000_00B8 46    30     CAN0             Bus Off
#define VECTOR_047      default_isr     // 0x0000_00BC 47    31     CAN0             Error
#define VECTOR_048      default_isr     // 0x0000_00C0 48    32     CAN0             Transmit Warning
#define VECTOR_049      default_isr     // 0x0000_00C4 49    33     CAN0             Receive Warning
#define VECTOR_050      default_isr     // 0x0000_00C8 50    34     CAN0             Wake Up
#define VECTOR_051      default_isr     // 0x0000_00CC 51    35     CAN0             Individual Matching Elements Update (IMEU)
#define VECTOR_052      default_isr     // 0x0000_00D0 52    36     CAN0             Lost receive
#define VECTOR_053      default_isr     // 0x0000_00D4 53    37     CAN1             OR'ed Message buffer (0-15)
#define VECTOR_054      default_isr     // 0x0000_00D8 54    38     CAN1             Bus off
#define VECTOR_055      default_isr     // 0x0000_00DC 55    39     CAN1             Error
#define VECTOR_056      default_isr     // 0x0000_00E0 56    40     CAN1             Transmit Warning
#define VECTOR_057      default_isr     // 0x0000_00E4 57    41     CAN1             Receive Warning
#define VECTOR_058      default_isr     // 0x0000_00E8 58    42     CAN1             Wake Up
#define VECTOR_059      default_isr     // 0x0000_00EC 59    43     CAN1             Individual Matching Elements Update (IMEU)
#define VECTOR_060      default_isr     // 0x0000_00F0 60    44     CAN1             Lost receive 
#define VECTOR_061      default_isr     // 0x0000_00F4 61    45     UART0            Single interrupt vector for UART status sources
#define VECTOR_062      default_isr     // 0x0000_00F8 62    46     UART0            Single interrupt vector for UART error sources
#define VECTOR_063      default_isr     // 0x0000_00FC 63    47     UART1            Single interrupt vector for UART status sources
#define VECTOR_064      default_isr     // 0x0000_0100 64    48     UART1            Single interrupt vector for UART error sources
#define VECTOR_065      default_isr     // 0x0000_0104 65    49     UART2            Single interrupt vector for UART status sources
#define VECTOR_066      default_isr     // 0x0000_0108 66    50     UART2            Single interrupt vector for UART error sources
#define VECTOR_067      default_isr     // 0x0000_010C 67    51     UART3            Single interrupt vector for UART status sources
#define VECTOR_068      default_isr     // 0x0000_0110 68    52     UART3            Single interrupt vector for UART error sources
// #define VECTOR_069      UART4_RX_TX_IRQHandler     // 0x0000_0114 69    53     UART4            Single interrupt vector for UART status sources
#define VECTOR_069      default_isr      // 0x0000_0114 69    53     UART4            Single interrupt vector for UART status sources
#define VECTOR_070      default_isr     // 0x0000_0118 70    54     UART4            Single interrupt vector for UART error sources
#define VECTOR_071      default_isr     // 0x0000_011C 71    55     UART5            Single interrupt vector for UART status sources
#define VECTOR_072      default_isr     // 0x0000_0120 72    56     UART5            Single interrupt vector for UART error sources
#define VECTOR_073      default_isr     // 0x0000_0124 73    57     ADC0
#define VECTOR_074      default_isr     // 0x0000_0128 74    58     ADC1
#define VECTOR_075      default_isr     // 0x0000_012C 75    59     CMP0             High-speed comparator 
#define VECTOR_076      default_isr     // 0x0000_0130 76    60     CMP1
#define VECTOR_077      default_isr     // 0x0000_0134 77    61     CMP2
#define VECTOR_078      default_isr     // 0x0000_0138 78    62     FTM0 			 Single interrupt vector for all sources
#define VECTOR_079      default_isr     // 0x0000_013C 79    63     FTM1 			 Single interrupt vector for all sources
#define VECTOR_080      default_isr     // 0x0000_0140 80    64     FTM2 			 Single interrupt vector for all sources
#define VECTOR_081      default_isr     // 0x0000_0144 81    65     CMT
#define VECTOR_082      default_isr     // 0x0000_0148 82    66     RTC Timer interrupt
#define VECTOR_083      default_isr     // 0x0000_014C 83    67
#define VECTOR_084      default_isr     // 0x0000_0150 84    68     PIT Channel 0
#define VECTOR_085      default_isr     // 0x0000_0154 85    69     PIT Channel 1
#define VECTOR_086      default_isr     // 0x0000_0158 86    70     PIT Channel 2
#define VECTOR_087      default_isr     // 0x0000_015C 87    71     PIT Channel 3
#define VECTOR_088      default_isr     // 0x0000_0160 88    72     PDB
#define VECTOR_089      default_isr     // 0x0000_0164 89    73     USB OTG
#define VECTOR_090      default_isr     // 0x0000_0168 90    74     USB Charger Detect
#define VECTOR_091      default_isr     // 0x0000_016C 91    75		 ENET			 IEEE 1588 Timer interrupt			 
#define VECTOR_092      default_isr     // 0x0000_0170 92    76		 ENET			 Transmit interrupt
#define VECTOR_093      default_isr     // 0x0000_0174 93    77		 ENET			 Receive interrupt
#define VECTOR_094      default_isr     // 0x0000_0178 94    78		 ENET			 Error and miscellaneous interrupt
#define VECTOR_095      default_isr     // 0x0000_017C 95    79     I2S
#define VECTOR_096      default_isr     // 0x0000_0180 96    80     SDHC
#define VECTOR_097      default_isr     // 0x0000_0184 97    81     DAC0
#define VECTOR_098      default_isr     // 0x0000_0188 98    82     DAC1
#define VECTOR_099      default_isr     // 0x0000_018C 99    83     TSI 			 Single interrupt vector for all sources
#define VECTOR_100      default_isr     // 0x0000_0190 100   84     MCG
#define VECTOR_101      default_isr     // 0x0000_0194 101   85     Low Power Timer
#define VECTOR_102      default_isr     // 0x0000_0198 102   86     Segment LCD 	 Single interrupt vector for all sources
#define VECTOR_103      default_isr     // 0x0000_019C 103   87     Port control module Pin Detect (Port A)
#define VECTOR_104      default_isr     // 0x0000_01A0 104   88     Port control module Pin Detect (Port B)
#define VECTOR_105      default_isr     // 0x0000_01A4 105   89     Port control module Pin Detect (Port C)
#define VECTOR_106      default_isr     // 0x0000_01A8 106   90     Port control module Pin Detect (Port D)
#define VECTOR_107      default_isr     // 0x0000_01AC 107   91     Port control module Pin Detect (Port E)
#define VECTOR_108      default_isr     // 0x0000_01B0 108   92    
#define VECTOR_109      default_isr     // 0x0000_01B4 109   93    
#define VECTOR_110      default_isr     // 0x0000_01B8 110   94    


#include <isr.h>

#endif 

