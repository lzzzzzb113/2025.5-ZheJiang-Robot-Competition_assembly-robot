#include "ToCof.h"
//2000
uint32_t PWM[6],DianJ=1000,huaG=30,T_PWM=2000,T_DianJ=2000,T_huaG=35,Count1=0,Count4=0,Count3=0,CountX3=0,CountX2=0,
		A1=0,A2=0,B1=0,B2=0,Ax=0,Bx=0,i=0,ss=92000,tap,KEYX=0,jsjs=254;
//         CountX1 = 252   —> 45°
//         CountX2 = 31000 —> 满度   //set去往电机

//         方形中间行程    —> ss = 18100 
//         圆形中间行程    —> ss = 19100 
struct yunint{
	uint32_t ID;
	uint32_t YW;
}yun[8];


//static void Syntax_B(uint16_t a0,uint16_t b0,struct yunint a[])
//{
//	uint16_t c0;
//	if(a0>7)c0 = c0 - 8;
//	for(c0=0;c0<8;c0++)
//	{
//		if(a[i].ID == b0 && a[i].YW == 0)break;
//	}
//	c0=c0+1;
//	if(c0<b0)c0 = c0 + 8;
//	CountX2=252 * (c0 - b0);
//	
//}
/*----------------------------------------------*/
void All_Main(void)
{ 

//	KEYX=0;
//  while(KEYX==0){KEYX=GPIO_ReadInputDataBit(PWM_GPIO_Port,KEY0);yans(999999);}
//	Syntax_C();
////	while(1){
////	KEYX=0;
////  while(KEYX==0){KEYX=GPIO_ReadInputDataBit(PWM_GPIO_Port,KEY0);yans(999999);}
////	GPIO_SetBits(Other_GPIO_Port,huaF_Pin);
////	CountX3=2000;
////	while(CountX3 != 0){};
////  }
//	while(1)
//	{

////*----------------------------------------------*/     //调试动作
////		Syntax_A(3,248,10000);//zuixiamian        A4
////		Syntax_A(0,170,10000);//zhongjian         A5
////		Syntax_A(1,130,10000);//zhongjian   shang         A7              PWM4和PWM5相反
////		Syntax_A(2,125,10000);//zhuan              A8
////		Syntax_A(5,220,10000);//0    1             A3
////		Syntax_A(4,90,10000);//zhuazi            A2	
///*----------------------------------------------*/     //准备动作
//      To_Be();
///*----------------------------------------------*/			//传送带动
//		  GPIO_SetBits(chuanS_GPIO_Port,chuanS_Pin);
///*----------------------------------------------*/		//传送带停
//		  while(GPIO_ReadInputDataBit(Read_GPIO_Port,Read3_Pin) != 0);
//      yans(200000);//防抖动
//		  while(GPIO_ReadInputDataBit(Read_GPIO_Port,Read3_Pin) != 0);
//			GPIO_SetBits(chuanS_GPIO_Port,chuanS_Pin);
//			yans(10000);yans(999999);yans(399999);
//			
//		  GPIO_ResetBits(chuanS_GPIO_Port,chuanS_Pin);
//			yans(10000);yans(10000);yans(999999);yans(999999);yans(999999);
///*----------------------------------------------*/		//读摄像头
//		  read_12();
//			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);
//		  while(Ax != 1)
//			{
//			GPIO_SetBits(chuanS_GPIO_Port,chuanS_Pin);
//			while(GPIO_ReadInputDataBit(Read_GPIO_Port,Read3_Pin) != 0);
//      yans(200000);//防抖动
//		  while(GPIO_ReadInputDataBit(Read_GPIO_Port,Read3_Pin) != 0);
//			GPIO_SetBits(chuanS_GPIO_Port,chuanS_Pin);
//			yans(10000);yans(999999);yans(399999);
//		  GPIO_ResetBits(chuanS_GPIO_Port,chuanS_Pin);
//			yans(10000);yans(10000);yans(999999);yans(999999);yans(999999);
//			read_12();
//				}
///*----------------------------------------------*/		//前往传送带，夹取物块
//	
//			GPIO_SetBits(Other_GPIO_Port,huaF_Pin);
//		  CountX3=53300;
//			while(CountX3 != 0){};	

//			To_get();
//			
///*----------------------------------------------*/		//去往圆台
////      GPIO_ResetBits(Other_GPIO_Port,huaF_Pin);
////		  CountX3=89500;
////			while(CountX3 != 0){};
//      GPIO_ResetBits(Other_GPIO_Port,huaF_Pin);
//		  CountX3=77800;
//			while(CountX3 != 0){};
//		
///*----------------------------------------------*/		//放下物块
//		  while(CountX3 != 0){};
//			//
//		  To_put();
//			
////			GPIO_SetBits(Other_GPIO_Port,huaF_Pin);
////		  CountX3=36500;
////      while(CountX3 != 31500){};
////		  GPIO_SetBits(chuanS_GPIO_Port,chuanS_Pin);
////		  while(CountX3 != 0){};
//			GPIO_SetBits(Other_GPIO_Port,huaF_Pin);
//		  CountX3=24500;
//		  while(CountX3 != 19500){};
//		  GPIO_SetBits(chuanS_GPIO_Port,chuanS_Pin);
//		  while(CountX3 != 0){};
//		  CountX2=1006;
//}
     
		 while(1){
			
			GPIO_SetBits(Other_GPIO_Port,huaG_Pin);
		 }
	}


void All_Config(void)
{ 
	PWM_Config();
	Read_Config();
	chuanS_Config();
	Other_Config();
	ADVANCE_TIM_Init();
}
/*-----------------------------------------------------------------------------------*/
void Syntax_C(void)
{
//	while(B1 == 0 && B2 == 0){ 
//		yans(10000);
//		B1=GPIO_ReadInputDataBit(Read_GPIO_Port,Read4_Pin);
//		B2=GPIO_ReadInputDataBit(Read_GPIO_Port,Read5_Pin);
//		
//		}
//		if(B1==1 && B2==0)Bx=1;
//		if(B1==0 && B2==1)Bx=2;
//		if(B1==1 && B2==1)Bx=3;
//		while(Bx != Ax)
//		{
//			CountX2 = 252;
//			i++;
//			while(CountX2 != 0);
//			yans(100000);
//			tap =Bx;
//			yans(10000);
//			while(Bx == tap)
//			{ 
//				yans(10000);
//				B1=GPIO_ReadInputDataBit(Read_GPIO_Port,Read4_Pin);
//				B2=GPIO_ReadInputDataBit(Read_GPIO_Port,Read5_Pin);
//				if(B1==1 && B2==0)Bx=1;
//				else if(B1==0 && B2==1)Bx=2;
//				else if(B1==1 && B2==1)Bx=3;
//				else {yans(100000);break;}
//		  	}
//			
//			if(i==8)break;
//		}
	A1=GPIO_ReadInputDataBit(Read_GPIO_Port,Read4_Pin);
	while(A1!=1){
		CountX2=251;
		jsjs=254;
	while(CountX2 != 0){};
		yans(100000);
		while(jsjs--){ 
				yans(10000);
			
				A1=GPIO_ReadInputDataBit(Read_GPIO_Port,Read4_Pin);
//				A2=GPIO_ReadInputDataBit(Read_GPIO_Port,Read2_Pin);
			}
		
		
			}
}
void read_12(void)
{jsjs=254;
	while(jsjs--){ 
			yans(10000);
			A1=GPIO_ReadInputDataBit(Read_GPIO_Port,Read1_Pin);
//			A2=GPIO_ReadInputDataBit(Read_GPIO_Port,Read2_Pin);
		}
//		if(A1==1 && A2==0)Ax=1;
//		if(A1==0 && A2==1)Ax=2;
//		if(A1==1 && A2==1)Ax=3;
		if(A1==1)Ax=1;
		if(A1==0)Ax=0;
}
void To_get(void)
{
/*----------------------------------------------*/	//夹

			
			
			Syntax_A(3,217,30000);//zuixiamian        A4
			Syntax_A(0,170,30000);//zhongjian         A5
			Syntax_A(1,130,30000);//zhongjian  shang       A7
			Syntax_A(2,129,30000);//zhuan              A8
			Syntax_A(5,138,30000);//0                 A3
			Syntax_A(4,170,10000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);

			
			
/*----------------------------------------------*/       //抬起来
			Syntax_A(3,217,30000);//zuixiamian        A4
			Syntax_A(0,150,30000);//zhongjian         A5
			Syntax_A(1,150,30000);//zhongjian  shang       A7
			Syntax_A(2,129,30000);//zhuan              A8
			Syntax_A(5,138,30000);//0                 A3
			Syntax_A(4,170,10000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);

			
			
			
/*----------------------------------------------*/       //转			
			Syntax_A(3,84,50000);//zuixiamian        A4
			Syntax_A(0,150,10000);//zhongjian         A5
			Syntax_A(1,150,10000);//zhongjian  shang       A7
			Syntax_A(2,129,30000);//zhuan              A8
			Syntax_A(5,138,10000);//0                 A3
			Syntax_A(4,170,10000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);
/*----------------------------------------------*/       //下
			Syntax_A(3,84,50000);//zuixiamian        A4
			Syntax_A(0,150,10000);//zhongjian         A5
			Syntax_A(1,150,10000);//zhongjian  shang       A7
			Syntax_A(2,145,70000);//zhuan              A8
			Syntax_A(5,138,10000);//0                 A3
			Syntax_A(4,170,10000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);

			
}
void To_Be(void)
{     Syntax_A(2,120,10000);//zhuan              A8
	    Syntax_A(3,217,40000);//zuixiamian        A4
			Syntax_A(0,170,30000);//zhongjian         A5
			Syntax_A(1,130,30000);//zhongjian   shang         A7
			Syntax_A(5,138,30000);//0    1             A3
			Syntax_A(4,130,30000);//zhuazi            A2
	    yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);
	    Syntax_A(2,133,40000);//zhuan              A8(如果想再向下砸，就调大)
	    Syntax_A(3,217,90000);//zuixiamian        A4
			Syntax_A(0,170,30000);//zhongjian         A5
			Syntax_A(1,130,30000);//zhongjian   shang         A7
			Syntax_A(5,138,30000);//0    1             A3
			Syntax_A(4,120,30000);//zhuazi            A2
	    
			

}
void To_put(void)
{

/*----------------------------------------------*/       //放	
			Syntax_A(3,84,50000);//zuixiamian        A4
			Syntax_A(0,150,10000);//zhongjian         A5
			Syntax_A(1,150,10000);//zhongjian  shang       A7
			Syntax_A(2,145,30000);//zhuan              A8
			Syntax_A(5,138,10000);//0                 A3
			Syntax_A(4,145,10000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);
/*----------------------------------------------*/       //2放	
			Syntax_A(3,84,50000);//zuixiamian        A4
			Syntax_A(0,150,10000);//zhongjian         A5
			Syntax_A(1,150,10000);//zhongjian  shang       A7
			Syntax_A(2,145,30000);//zhuan              A8
			Syntax_A(5,138,10000);//0                 A3
			Syntax_A(4,138,60000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);
/*----------------------------------------------*/
	    Syntax_A(3,80,50000);//zuixiamian        A4
			Syntax_A(0,150,10000);//zhongjian         A5
			Syntax_A(1,150,10000);//zhongjian  shang       A7
			Syntax_A(2,145,30000);//zhuan              A8
			Syntax_A(5,138,10000);//0                 A3
			Syntax_A(4,138,60000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);
/*----------------------------------------------*/
	    Syntax_A(3,88,50000);//zuixiamian        A4
			Syntax_A(0,150,10000);//zhongjian         A5
			Syntax_A(1,150,10000);//zhongjian  shang       A7
			Syntax_A(2,145,30000);//zhuan              A8
			Syntax_A(5,138,10000);//0                 A3
			Syntax_A(4,138,60000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);
/*----------------------------------------------*/       //2放	
			Syntax_A(3,84,50000);//zuixiamian        A4
			Syntax_A(0,150,10000);//zhongjian         A5
			Syntax_A(1,150,10000);//zhongjian  shang       A7
			Syntax_A(2,145,30000);//zhuan              A8
			Syntax_A(5,138,10000);//0                 A3
			Syntax_A(4,138,60000);//zhuazi            A2
			yans(999999);yans(999999);yans(999999);yans(999999);yans(999999);


}
void PWM_Config(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		GPIO_InitTypeDef GPIO_ice;	
		
		GPIO_ice.GPIO_Pin =  PWM1_Pin|PWM2_Pin|PWM3_Pin|PWM4_Pin|PWM5_Pin|PWM6_Pin|KEY0;
		GPIO_ice.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_ice.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_ice.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(PWM_GPIO_Port, &GPIO_ice);	
	
		GPIO_ice.GPIO_Pin =  KEY0;
		GPIO_ice.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_ice.GPIO_Mode = GPIO_Mode_IN;
		GPIO_ice.GPIO_PuPd =GPIO_PuPd_UP;
		GPIO_Init(PWM_GPIO_Port, &GPIO_ice);
		PWM[0] = 170;
		PWM[1] = 130;
		PWM[2] = 125;
		PWM[3] = 217;
		PWM[4] = 120;
		PWM[5] = 138;
//    PWM[0] = 170;
//		PWM[1] = 130;
//		PWM[2] = 139;
//		PWM[3] = 215;
//		PWM[4] = 110;
//		PWM[5] = 138;  
//		Syntax_A(3,82,50000);//zuixiamian        A4
//	  Syntax_A(0,150,10000);//zhongjian         A5
//	  Syntax_A(1,150,10000);//zhongjian  shang       A7
//	  Syntax_A(2,145,70000);//zhuan              A8
//	  Syntax_A(5,138,10000);//0                 A3
//	  Syntax_A(4,167,10000);//zhuazi            A2		
		

	
		yun[0].YW = 0;
		yun[1].YW = 0;
		yun[2].YW = 0;
		yun[3].YW = 0;
		yun[4].YW = 0;
		yun[5].YW = 0;
		yun[6].YW = 0;
		yun[7].YW = 0;
}
void Read_Config(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		GPIO_InitTypeDef GPIO_ice;	
	
		GPIO_ice.GPIO_Pin =  Read1_Pin|Read2_Pin|Read3_Pin|Read4_Pin|Read5_Pin;
		GPIO_ice.GPIO_Mode = GPIO_Mode_IN;
		GPIO_ice.GPIO_PuPd =GPIO_PuPd_UP;
		GPIO_Init(Read_GPIO_Port, &GPIO_ice);	
}
void chuanS_Config(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		GPIO_InitTypeDef GPIO_ice;	
		
		GPIO_ice.GPIO_Pin =  chuanS_Pin;
		GPIO_ice.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_ice.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_ice.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(chuanS_GPIO_Port , &GPIO_ice);
}
void Other_Config(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		GPIO_InitTypeDef GPIO_ice;	
		
		GPIO_ice.GPIO_Pin =  huaG_Pin|dianJ_Pin|huaF_Pin;
		GPIO_ice.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_ice.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_ice.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(Other_GPIO_Port , &GPIO_ice);	
}
static void ADVANCE_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
    NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ ;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void ADVANCE_TIM_Mode_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
    ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK, ENABLE);	
    TIM_TimeBaseStructure.TIM_Period=ADVANCE_TIM_Period;
    TIM_TimeBaseStructure.TIM_Prescaler= ADVANCE_TIM_Prescaler;	
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
    TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(ADVANCE_TIM, TIM_FLAG_Update);
    TIM_ITConfig(ADVANCE_TIM,TIM_IT_Update,ENABLE);
    TIM_Cmd(ADVANCE_TIM, ENABLE);
}

void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_NVIC_Config();
	ADVANCE_TIM_Mode_Config();		
}
void yans(uint32_t t)
{
	while(t--);
}
void Syntax_A(uint16_t a0,uint16_t b0,uint32_t c0)
{
	while(PWM[a0]!=b0)
	{
		if(PWM[a0]>b0)
			{
			PWM[a0]--;
			}
		else if(PWM[a0]<b0)
			{
			PWM[a0]++;
			}
		else break;
			yans(c0);
			yans(c0);
	}
}
//void Syntax_B(uint16_t a0,uint16_t b0,struct yunint a[])
//{
//	uint16_t c0;
//	for(c0=0;c0<8;c0++)
//	{
//		if(a[i].ID == b0 && a[i].YW == 0)break;
//	}
//	c0=c0+1;
//	if(c0<b0)c0 = c0 + 8;
//	CountX2=252 * (c0 - b0);
//	
//}
/*---------------------------中断服务内容-------------------------------*/

void  ADVANCE_TIM_IRQHandler (void)
{
	
	if ( TIM_GetITStatus( ADVANCE_TIM, TIM_IT_Update) != RESET ) 
	{	
		
		Count1++;
		if(Count1==PWM[0]){GPIO_ResetBits(PWM_GPIO_Port,PWM1_Pin);}
		if(Count1==PWM[1]){GPIO_ResetBits(PWM_GPIO_Port,PWM2_Pin);}
		if(Count1==PWM[2]){GPIO_ResetBits(PWM_GPIO_Port,PWM3_Pin);}
		if(Count1==PWM[3]){GPIO_ResetBits(PWM_GPIO_Port,PWM4_Pin);}
		if(Count1==PWM[4]){GPIO_ResetBits(PWM_GPIO_Port,PWM5_Pin);}
		if(Count1==PWM[5]){GPIO_ResetBits(PWM_GPIO_Port,PWM6_Pin);}
		if(Count1==T_PWM )
			 {
				 Count1=0;
				 GPIO_SetBits(PWM_GPIO_Port,PWM1_Pin|PWM2_Pin|PWM3_Pin|PWM4_Pin|PWM5_Pin|PWM6_Pin);
			 }
			 
		if(CountX2 > 0)
				{ 
					Count3++;
					if(Count3==DianJ)  {GPIO_ResetBits(Other_GPIO_Port,dianJ_Pin);}
					if(Count3==T_DianJ )
						{
							CountX2--;
							Count3=0;
							GPIO_SetBits(Other_GPIO_Port,dianJ_Pin);
						}
				}
				
		if(CountX3 > 0)
				{ 
					Count4++;
					if(Count4==huaG) {GPIO_ResetBits(Other_GPIO_Port,huaG_Pin);}
					if(Count4==T_huaG )
						{
							CountX3--;
							Count4=0;
							GPIO_SetBits(Other_GPIO_Port,huaG_Pin);
						}
				}
				
		TIM_ClearITPendingBit(ADVANCE_TIM , TIM_FLAG_Update);
	}		 
}
/*--------------------------THE_END--------------------------*/

