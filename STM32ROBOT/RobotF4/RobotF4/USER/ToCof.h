#ifndef _ToCof_h
#define _ToCof_h

#endif

#include "stm32f4xx.h"
/*------------------------全局变量----------------------*/
extern uint32_t PWM[6],DianJ,huaG,T_PWM,T_DianJ,T_huaG,Count1,Count4,Count3,CountX3,CountX2,A1,A2,B1,B2,jsjs,Ax;
/*------------------------舵机映射----------------------*/
#define PWM_GPIO_Port 	  GPIOA

#define PWM1_Pin 					GPIO_Pin_5
#define PWM2_Pin 					GPIO_Pin_7  
#define PWM4_Pin 					GPIO_Pin_4  
#define PWM3_Pin 					GPIO_Pin_8
#define PWM5_Pin 					GPIO_Pin_2
#define PWM6_Pin 					GPIO_Pin_3
#define KEY0 					GPIO_Pin_0
/*------------------------中断映射----------------------*/
#define            ADVANCE_TIM                   TIM1
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM1
#define            ADVANCE_TIM_Period            (10-1)
#define            ADVANCE_TIM_Prescaler         71
#define            ADVANCE_TIM_IRQ               TIM1_UP_TIM10_IRQn 
#define            ADVANCE_TIM_IRQHandler        TIM1_UP_IRQHandler
/*------------------------通信映射----------------------*/
#define Read_GPIO_Port  	GPIOB

#define Read1_Pin 				GPIO_Pin_9//P8  
#define Read2_Pin 				GPIO_Pin_8//P7
#define Read3_Pin 				GPIO_Pin_15 //-传送带
#define Read4_Pin 				GPIO_Pin_7//P6  
#define Read5_Pin 				GPIO_Pin_6//P7
/*------------------------传送映射----------------------*/
#define chuanS_GPIO_Port GPIOB

#define chuanS_Pin 				GPIO_Pin_14 
/*------------------------电机映射----------------------*/
#define Other_GPIO_Port  	GPIOB

#define dianJ_Pin 				GPIO_Pin_13 
#define huaG_Pin  				GPIO_Pin_12 


#define huaF_Pin  				GPIO_Pin_11 
/*------------------------修饰映射----------------------*/
#define Starry_Starry_Night  All_Config();
#define As_Beautiful_As_You  All_Main();
/*------------------------函数列表----------------------*/
void All_Config(void);
void All_Main(void);

void PWM_Config(void);
void Read_Config(void);
void chuanS_Config(void);
void Other_Config(void);
void ADVANCE_TIM_Init(void);
void yans(uint32_t t);
void Syntax_A(uint16_t a0,uint16_t b0,uint32_t c0);
void To_get(void);
void To_put(void);
void read_12(void);
void Syntax_C(void);
void To_Be(void);


