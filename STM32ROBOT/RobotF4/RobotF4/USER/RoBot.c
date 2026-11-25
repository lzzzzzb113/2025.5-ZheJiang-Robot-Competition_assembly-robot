#include "RoBot.h"

uint32_t 
	PWM[3],WL=250,HG1=24,HG2=30,T_WL=500,T_HG1=28,T_HG2=35,T_PWM=2000,
	
	Count1=0,CountX2=0,CountX3=0,CountX4=0,Count2=0,Count3=0,Count4=0,
	
	A=0,B=0,C=0,Ax=0,Bx=0,Cx=0,
	
	y=0,f=0,s=0,t=0,l=0,
	
	read_again=254,Boo=0,i=0,Check=0,running=1,
	
	flag0=0,flag1=0,flag9=0;
	
/*------------------------------------各个配置文件-------------------------------------*/

void Read_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_ice;	

	GPIO_ice.GPIO_Pin =  Read1_Pin|Read2_Pin|Read3_Pin;
	GPIO_ice.GPIO_Mode = GPIO_Mode_IN;
	GPIO_ice.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(Read_GPIO_Port, &GPIO_ice);
}

void HW_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_ice;	

	GPIO_ice.GPIO_Pin =  HW1_Pin|HW2_Pin|HW3_Pin;
	GPIO_ice.GPIO_Mode = GPIO_Mode_IN;
	GPIO_ice.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(HW_GPIO_Port, &GPIO_ice);
}

void QT_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_ice;	
	
	GPIO_ice.GPIO_Pin =  CS_Pin|WL_Pin|WLF_Pin;
	GPIO_ice.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_ice.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_ice.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(QT_GPIO_Port , &GPIO_ice);
}

void HG_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_ice;	
	
	GPIO_ice.GPIO_Pin =  HG1_Pin|HF1_Pin|HG2_Pin|HF2_Pin;
	GPIO_ice.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_ice.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_ice.GPIO_OType = GPIO_OType_PP;	
	GPIO_Init(HG_GPIO_Port , &GPIO_ice);	
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

void PWM_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_ice;	
	
	GPIO_ice.GPIO_Pin =  PWM0_Pin|PWM1_Pin|PWM2_Pin;
	GPIO_ice.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_ice.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_ice.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(PWM_GPIO_Port, &GPIO_ice);	
	
	//理想状态：150-67=83朝向传送带；150+67=217朝向物料盘

	PWM[1] = S_T_Y_J; //舵机二：旋转爪子
	
	PWM[0] = DIR_CS; //舵机一：底部云台旋转
	PWM[2] = CLAW_UNCLASP; //舵机三：爪子抓取
//	PWM[2] = CLAW_GRASP; //舵机三：爪子抓取
}

/*------------------------------------各个功能函数-------------------------------------*/
void Syntax_ABC(uint16_t a,uint16_t b,uint32_t c)
{
	while(PWM[a]!=b)
	{
		if(PWM[a]>b)
			{
			PWM[a]--;
			}
		else if(PWM[a]<b)
			{
			PWM[a]++;
			}
		else break;
			yans(c);
	}
}

void read_123(void)//000圆 001方 010三角 011棱台 //此函数不用
{
	read_again=254;
	while(read_again--){ 
			delay_ms(1);
			A=GPIO_ReadInputDataBit(Read_GPIO_Port,Read1_Pin);
			B=GPIO_ReadInputDataBit(Read_GPIO_Port,Read2_Pin);
			C=GPIO_ReadInputDataBit(Read_GPIO_Port,Read3_Pin);
		}
		if(A==0&&B==0&&C==0) {Ax=0;Bx=0;Cx=0;}
}

void yans(uint32_t t)
{
	while(t--);
}

void DJ(uint8_t a,uint8_t past,uint8_t last)
{
	uint8_t temp=past;
	unsigned long int ss=500000;
	
	if(past>last)
	{
		while(temp>last)
		{
			if(temp>last+12) Syntax_ABC(a,temp,ss);
			else {ss+=40000;Syntax_ABC(a,temp,ss);}
			temp--;
		}
		ss=500000;
		delay_ms(1000);
	}
	else if(past<last)
	{
		while(temp<last)
		{
			if(temp<last-12) Syntax_ABC(a,temp,ss);
			else {ss+=40000;Syntax_ABC(a,temp,ss);}
			temp++;
		}
		ss=500000;
		delay_ms(1000);
	}
}

void SG(unsigned int m,unsigned int qs)
{
	if(m==0)
	{
		CountX3=qs*xf1;
		while(CountX3 != 0){
			GPIO_SetBits(HG_GPIO_Port,HF1_Pin); //水平滑轨前往传送带
		}
	}
	else if(m==1)
	{
		CountX3=qs*xf1;
		while(CountX3 != 0){
			GPIO_ResetBits(HG_GPIO_Port,HF1_Pin); //水平滑轨前往物料盘
		}
	}
}

void CG(unsigned int m,unsigned int qs)
{
	if(m==0)
	{
		CountX4=qs*xf2;
		while(CountX4 != 0){
			GPIO_SetBits(HG_GPIO_Port,HF2_Pin); //垂直滑轨前往顶部
		}
	}
	else if(m==1)
	{
		CountX4=qs*xf2;
		while(CountX4 != 0){
			GPIO_ResetBits(HG_GPIO_Port,HF2_Pin); //垂直滑轨前往底部
		}
	}
}

void XZ(unsigned int m,unsigned int qs)
{
	if(m==0)
	{
		CountX2=qs*xf3;
		while(CountX2 != 0)
			GPIO_ResetBits(QT_GPIO_Port,WLF_Pin);
	
	}
	else if(m==1)
	{
		CountX2=qs*xf3;
		while(CountX2 != 0)
			GPIO_SetBits(QT_GPIO_Port,WLF_Pin);
	}
}

u8 Openmv_Cheack(void)
{
	read_again=254;
	while(read_again--){ 
		delay_ms(1);
		P7;P8;P9;
	}
	if(P7 == 1 && P8 == 1 && P9 == 0) return 1; //圆形 7 
	if(P7 == 0 && P8 == 1 && P9 == 0) return 2; //矩形 2
	if(P7 == 1 && P8 == 0 && P9 == 0) return 3; //三角形 4
	if(P7 == 0 && P8 == 0 && P9 == 1) return 4; //梯形 1
//	if(P7 == 0 && P8 ==   && P9 == 1) return 5; //红色 3
//	if(P7 == 1 && P8 == 1 && P9 == 0) return 6; //蓝色 6
	if(P7 == 1 && P8 == 0 && P9 == 1) return 7; //六边形 5
}


void yuan(void)
{
    for(i=0;i<QW_CS;i++){ SG(TO_CS,1); } //识别完毕，前往抓取 ++19

	for(i=0;i<LOW_ZZ;i++) { CG(TO_LOW,1); }  //降下爪子 -20
	/*-------------------------蓝区主程序-------------------------*/
	
	Syntax_ABC(2,CLAW_GRASP_Y,10000); delay_ms(500); //抓取物料 
		
	for(i=0;i<15;i++) { CG(TO_HIGH,1); } //拉高物料 +15
	
	DJ(0,DIR_CS,DIR_WL); //转向物料盘
	
	for(i=0;i<QW_WLread;i++) { SG(TO_WL,1); } //参数调整 //前往物料盘 --5
	
	for(i=0;i<LOW_read;i++) { CG(TO_LOW,1); } //参数调整 //降下摄像头 -19

//	while(1){ //摄像头识别孔位
//		Boo = Openmv_Cheack();
//		if(Check!=Boo) { delay_ms(1500); XZ(CLOCK_N,1); }
//		if(Check==Boo) { break; } 
//	}
	
	Syntax_ABC(1,S_T_Y_J,10000);
	
	for(i=0;i<QW_WL;i++) { SG(TO_WL,1); } //参数调整 //放置物料位置 --14
	
	for(i=0;i<LOW_WL;i++) { CG(TO_LOW,1); } //参数调整 //降下物料 -7
	
	DJ(0,DIR_WL,DIR_WL+8);
	DJ(0,DIR_WL+4,DIR_WL-8);
	delay_ms(100);	
	DJ(0,DIR_WL-4,DIR_WL);
		
	Syntax_ABC(2,CLAW_UNCLASP,10000); //松开物料
		
	for(i=0;i<5;i++) { SG(TO_CS,1); } //拉回水平滑轨初始位置
	
	for(i=0;i<31;i++) { CG(TO_HIGH,1); } //拉回垂直滑轨初始高度
	
	XZ(CLOCK_N,1);
	
	DJ(0,DIR_WL,DIR_CS); //转回横臂初始朝向
	
	Syntax_ABC(1,Y,10000); //爪子转回初始方向，摄像头朝前
}

void yuan_F(void)
{
    for(i=0;i<QW_CS;i++){ SG(TO_CS,1); } //识别完毕，前往抓取 ++19

	for(i=0;i<LOW_ZZ;i++) { CG(TO_LOW,1); }  //降下爪子 -20
	/*-------------------------蓝区主程序-------------------------*/
	
	Syntax_ABC(2,CLAW_GRASP_Y,10000); delay_ms(500); //抓取物料 
		
	for(i=0;i<15;i++) { CG(TO_HIGH,1); } //拉高物料 +15
	
	DJ(0,DIR_CS,DIR_WL); //转向物料盘
	
	for(i=0;i<QW_WLread;i++) { SG(TO_WL,1); } //参数调整 //前往物料盘 --5
	
	for(i=0;i<LOW_read;i++) { CG(TO_LOW,1); } //参数调整 //降下摄像头 -19

	while(1){ //摄像头识别孔位
		Boo = Openmv_Cheack();
		if(Check!=Boo) { delay_ms(1500); XZ(CLOCK_N,1); }
		if(Check==Boo) { break; } 
	}
	
	Syntax_ABC(1,S_T_Y_J,10000);
	
	for(i=0;i<QW_WL;i++) { SG(TO_WL,1); } //参数调整 //放置物料位置 --14
	
	for(i=0;i<LOW_WL;i++) { CG(TO_LOW,1); } //参数调整 //降下物料 -7
	
	DJ(0,DIR_WL,DIR_WL+8);
	DJ(0,DIR_WL+4,DIR_WL-8);
	delay_ms(100);	
	DJ(0,DIR_WL-4,DIR_WL);
		
	Syntax_ABC(2,CLAW_UNCLASP,10000); //松开物料
		
	for(i=0;i<5;i++) { SG(TO_CS,1); } //拉回水平滑轨初始位置
	
	for(i=0;i<31;i++) { CG(TO_HIGH,1); } //拉回垂直滑轨初始高度
	
	XZ(CLOCK_N,1);
	
	DJ(0,DIR_WL,DIR_CS); //转回横臂初始朝向
	
	Syntax_ABC(1,Y,10000); //爪子转回初始方向，摄像头朝前
}

void fang(void)
{
	for(i=0;i<QW_CS;i++){ SG(TO_CS,1); } //识别完毕，前往抓取 ++16

	for(i=0;i<LOW_ZZ;i++) { CG(TO_LOW,1); }  //降下爪子 -20
	/*-------------------------蓝区主程序-------------------------*/
	Syntax_ABC(2,CLAW_GRASP_F,10000); delay_ms(500);
		
	for(i=0;i<15;i++) { CG(TO_HIGH,1); } //拉高物料 +15
	
	DJ(0,DIR_CS,DIR_WL); //转向物料盘
	
	for(i=0;i<QW_WLread+1;i++) { SG(TO_WL,1); } //参数调整 //前往物料盘 --6
	
	for(i=0;i<LOW_read;i++) { CG(TO_LOW,1); } //参数调整 //降下摄像头 -19
	
	while(1){ //摄像头识别孔位
		Boo = Openmv_Cheack();
		if(Check!=Boo) { delay_ms(1500); XZ(CLOCK_N,1); }
		if(Check==Boo) { break; }
	}
	
	Syntax_ABC(1,S_T_Y_J,10000);
	
	for(i=0;i<QW_WL;i++) { SG(TO_WL,1); } //参数调整 //放置物料位置 --14
	
	for(i=0;i<LOW_WL;i++) { CG(TO_LOW,1); } //参数调整 //降下物料 -7
	
	DJ(0,DIR_WL,DIR_WL+4);
	delay_ms(200);	
	DJ(0,DIR_WL+4,DIR_WL-4);
	delay_ms(200);	
	DJ(0,DIR_WL-4,DIR_WL);
		
	Syntax_ABC(2,CLAW_UNCLASP,10000); //松开物料
		
	for(i=0;i<SG_FW-1;i++) { SG(TO_CS,1); } //拉回水平滑轨初始位置
	
	for(i=0;i<CG_FW;i++) { CG(TO_HIGH,1); } //拉回垂直滑轨初始高度
	
	XZ(CLOCK_N,1);
	
	DJ(0,DIR_WL,DIR_CS); //转回横臂初始朝向
	
	Syntax_ABC(1,Y,10000); //爪子转回初始方向，摄像头朝前
}

void san(void)
{
	for(i=0;i<QW_CS;i++){ SG(TO_CS,1); } //识别完毕，前往抓取 ++16

	Syntax_ABC(1,S,10000);
	
	for(i=0;i<LOW_ZZ;i++) { CG(TO_LOW,1); }  //降下爪子 -20
	/*-------------------------蓝区主程序-------------------------*/
	Syntax_ABC(2,CLAW_GRASP_F,10000); delay_ms(500);
		
	for(i=0;i<15;i++) { CG(TO_HIGH,1); } //拉高物料 +15
	
	DJ(0,DIR_CS,DIR_WL); //转向物料盘
	
	for(i=0;i<QW_WLread;i++) { SG(TO_WL,1); } //参数调整 //前往物料盘 --6
	
	for(i=0;i<LOW_read;i++) { CG(TO_LOW,1); } //参数调整 //降下摄像头 -19
	
	Syntax_ABC(1,S_T_Y_J,10000);
	
	while(1){ //摄像头识别孔位
		Boo = Openmv_Cheack();
		if(Check!=Boo) { delay_ms(1500); XZ(CLOCK_N,1); }
		if(Check==Boo) { break; }
	}
	
	Syntax_ABC(1,S,10000);
	
	for(i=0;i<QW_WL;i++) { SG(TO_WL,1); } //参数调整 //放置物料位置 --14
	
	for(i=0;i<LOW_WL;i++) { CG(TO_LOW,1); } //参数调整 //降下物料 -7
	
	DJ(0,DIR_WL,DIR_WL+4);
	delay_ms(200);	
	DJ(0,DIR_WL+4,DIR_WL-4);
	delay_ms(200);	
	DJ(0,DIR_WL-4,DIR_WL);
		
	Syntax_ABC(2,CLAW_UNCLASP,10000); //松开物料
		
	for(i=0;i<SG_FW;i++) { SG(TO_CS,1); } //拉回水平滑轨初始位置
	
	for(i=0;i<CG_FW;i++) { CG(TO_HIGH,1); } //拉回垂直滑轨初始高度
	
	XZ(CLOCK_N,1);
	
	DJ(0,DIR_WL,DIR_CS); //转回横臂初始朝向
	
	Syntax_ABC(1,Y,10000); //爪子转回初始方向，摄像头朝前
}

void ti(void)
{
	for(i=0;i<QW_CS;i++){ SG(TO_CS,1); } //识别完毕，前往抓取 ++16

	Syntax_ABC(1,T,10000);
	
	for(i=0;i<LOW_ZZ;i++) { CG(TO_LOW,1); }  //降下爪子 -20
	/*-------------------------蓝区主程序-------------------------*/
	Syntax_ABC(2,CLAW_GRASP_F,10000); delay_ms(500);
		
	for(i=0;i<15;i++) { CG(TO_HIGH,1); } //拉高物料 +15
	
	DJ(0,DIR_CS,DIR_WL); //转向物料盘
	
	for(i=0;i<QW_WLread;i++) { SG(TO_WL,1); } //参数调整 //前往物料盘 --6
	
	for(i=0;i<LOW_read;i++) { CG(TO_LOW,1); } //参数调整 //降下摄像头 -19
	
	Syntax_ABC(1,S_T_Y_J,10000);
	
	while(1){ //摄像头识别孔位
		Boo = Openmv_Cheack();
		if(Check!=Boo) { delay_ms(1500); XZ(CLOCK_N,1); }
		if(Check==Boo) { break; }
	}
	
	Syntax_ABC(1,T,10000);
	
	for(i=0;i<QW_WL;i++) { SG(TO_WL,1); } //参数调整 //放置物料位置 --14
	
	for(i=0;i<LOW_WL;i++) { CG(TO_LOW,1); } //参数调整 //降下物料 -7
	
	DJ(0,DIR_WL,DIR_WL+4);
	delay_ms(200);	
	DJ(0,DIR_WL+4,DIR_WL-4);
	delay_ms(200);	
	DJ(0,DIR_WL-4,DIR_WL);
		
	Syntax_ABC(2,CLAW_UNCLASP,10000); //松开物料
		
	for(i=0;i<SG_FW;i++) { SG(TO_CS,1); } //拉回水平滑轨初始位置
	
	for(i=0;i<CG_FW;i++) { CG(TO_HIGH,1); } //拉回垂直滑轨初始高度
	
	XZ(CLOCK_N,1);
	
	DJ(0,DIR_WL,DIR_CS); //转回横臂初始朝向
	
	Syntax_ABC(1,Y,10000); //爪子转回初始方向，摄像头朝前
}

void beifen(void) //备份
{
	for(i=0;i<kaishi;i++){ SG(TO_CS,1); }
	
	for(i=0;i<QW_CS;i++){ SG(TO_CS,1); } //识别完毕，前往抓取 ++19
	
	DJ(0,DIR_CS,DIR_CS+10); DJ(0,DIR_CS+10,DIR_CS); 
	
	while(1){
		GPIO_SetBits(QT_GPIO_Port,CS_Pin);
		if(GPIO_ReadInputDataBit(HW_GPIO_Port,HW1_Pin) == 0){
			
			delay_ms(270); GPIO_ResetBits(QT_GPIO_Port,CS_Pin);
			
			for(i=0;i<LOW_ZZ;i++) { CG(TO_LOW,1); }  //降下爪子 -20
	
			Syntax_ABC(2,CLAW_GRASP_Y,10000); delay_ms(500); //抓取物料 
				
			for(i=0;i<20;i++) { CG(TO_HIGH,1); } //拉高物料 +20
			
			DJ(0,DIR_CS,DIR_CS+63); //转向
			
			Syntax_ABC(2,CLAW_UNCLASP,10000);
			
			DJ(0,DIR_CS+63,DIR_CS);
		}
	}
}

void zonghe(void)
{
	/*-------------------------蓝区主程序-------------------------*/
	//6.8 垂直滑轨静止位置，传送带物料识别位置
    flag1=0;
	if(flag0==0){
		for(i=0;i<40;i++){ SG(TO_CS,1); }
		DJ(0,DIR_CS,DIR_CS+10); DJ(0,DIR_CS+10,DIR_CS); 
		flag0++;
	}
//		while(GPIO_ReadInputDataBit(HW_GPIO_Port,HW1_Pin) != 0){
//			GPIO_SetBits(QT_GPIO_Port,CS_Pin);
//		}
//		
//		delay_ms(270); GPIO_ResetBits(QT_GPIO_Port,CS_Pin);
	
	while(1)
	{
	   if(flag1==1)
	   {
			read_again=100;
			delay_ms(500);
			while(read_again--)
			{
				delay_ms(10);
				Check = Openmv_Cheack();
				if(Check==1) { Syntax_ABC(1,S_T_Y_J,10000); break; }//y
				if(Check==2) { Syntax_ABC(1,S_T_Y_J,10000); break; }//f
				if(Check==3) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==4) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==7) { Syntax_ABC(1,S_T_Y_J,10000); break; }
			}
			break;
	   }
	}
	
//	for(i=0;i<16;i++){ SG(TO_CS,1); } //识别完毕，前往抓取 ++16

//	for(i=0;i<20;i++) { CG(TO_LOW,1); }  //降下爪子 -20
	
	if(Check==1){yuan();}
	else if(Check==2){fang();}
    else 
	{
	 GPIO_SetBits(QT_GPIO_Port,CS_Pin);
	 delay_ms(1500);
	 GPIO_ResetBits(QT_GPIO_Port,CS_Pin);
	}
	
}

void yuanceshi(void)
{
	if(flag0==0){
		for(i=0;i<kaishi;i++){ SG(TO_CS,1); }
		DJ(0,DIR_CS,DIR_CS+10); DJ(0,DIR_CS+10,DIR_CS); 
		flag0++;
	}
	flag1=0;
		
	while(flag1!=1)
	{
			read_again=100;
			while(read_again--)
			{
				delay_ms(10);
				Check = Openmv_Cheack();
				if(Check==1) { Syntax_ABC(1,S_T_Y_J,10000); break; }//y
				if(Check==2) { Syntax_ABC(1,S_T_Y_J,10000); break; }//f
				if(Check==3) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==4) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==7) { Syntax_ABC(1,S_T_Y_J,10000); break; }
			}
			//GPIO_ResetBits(GPIOF,GPIO_Pin_9);GPIO_SetBits(GPIOF,GPIO_Pin_10);

	   GPIO_ResetBits(GPIOF,GPIO_Pin_10);GPIO_SetBits(GPIOF,GPIO_Pin_9);
			delay_ms(500);
	   
	}
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);GPIO_SetBits(GPIOF,GPIO_Pin_10);
	delay_ms(500);
	
	if(Check==1){GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);yuan();}
//	else if(Check==2){fang();}
//	else if(Check==3){san();}
//	else if(Check==4){ti();}
    else 
	{
	 GPIO_SetBits(QT_GPIO_Port,CS_Pin);
	 delay_ms(1500);
	 GPIO_ResetBits(QT_GPIO_Port,CS_Pin);
	}
}

void yuanceshi_F(void)
{
	if(flag0==0){
		for(i=0;i<kaishi;i++){ SG(TO_CS,1); }
		DJ(0,DIR_CS,DIR_CS+10); DJ(0,DIR_CS+10,DIR_CS); 
		flag0++;
	}
	flag1=0;
		
	while(flag1!=1)
	{

			read_again=100;
			while(read_again--)
			{
				delay_ms(10);
				Check = Openmv_Cheack();
				if(Check==1) { Syntax_ABC(1,S_T_Y_J,10000); break; }//y
				if(Check==2) { Syntax_ABC(1,S_T_Y_J,10000); break; }//f
				if(Check==3) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==4) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==7) { Syntax_ABC(1,S_T_Y_J,10000); break; }
			}
			//GPIO_ResetBits(GPIOF,GPIO_Pin_9);GPIO_SetBits(GPIOF,GPIO_Pin_10);

	   GPIO_ResetBits(GPIOF,GPIO_Pin_10);GPIO_SetBits(GPIOF,GPIO_Pin_9);
	   
	}
	GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
	
	if(Check==1){yuan();}
//	else if(Check==2){fang();}
//	else if(Check==3){san();}
//	else if(Check==4){ti();}
    else 
	{
	 GPIO_SetBits(QT_GPIO_Port,CS_Pin);
	 delay_ms(1500);
	 GPIO_ResetBits(QT_GPIO_Port,CS_Pin);
	}
}

void quanbu(void)
{
/*-------------------------蓝区主程序-------------------------*/
	//6.8 垂直滑轨静止位置，传送带物料识别位置
    
	if(flag0==0){
		for(i=0;i<kaishi;i++){ SG(TO_CS,1); }
		DJ(0,DIR_CS,DIR_CS+10); DJ(0,DIR_CS+10,DIR_CS); 
		flag0++;
	}
	flag1=0;
	
	{

			read_again=100;
			while(read_again--)
			{
				delay_ms(10);
				Check = Openmv_Cheack();
				if(Check==1) { Syntax_ABC(1,S_T_Y_J,10000); break; }//y
				if(Check==2) { Syntax_ABC(1,S_T_Y_J,10000); break; }//f
				if(Check==3) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==4) { Syntax_ABC(1,S_T_Y_J,10000); break; }
				if(Check==7) { Syntax_ABC(1,S_T_Y_J,10000); break; }
			}
			//GPIO_ResetBits(GPIOF,GPIO_Pin_9);GPIO_SetBits(GPIOF,GPIO_Pin_10);

	   GPIO_ResetBits(GPIOF,GPIO_Pin_10);GPIO_SetBits(GPIOF,GPIO_Pin_9);
	   
	}
	GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
	
	if(Check==1){yuan();}
	else if(Check==2){fang();}
	else if(Check==3){san();}
	else if(Check==4){ti();}
    else 
	{
	 GPIO_SetBits(QT_GPIO_Port,CS_Pin);
	 delay_ms(1500);
	 GPIO_ResetBits(QT_GPIO_Port,CS_Pin);
	}
}
/*----------------------------------主配置、执行文件-------------------------------------*/
void All_Config(void)
{ 
	PWM_Config();
	Read_Config();
	QT_Config();
	HG_Config();
	ADVANCE_TIM_Init();
	delay_init(168);
	KEY_Init();
	LED_Init();
	uart_init(115200);
}

void All_Main(void)
{ 	
	/*-------------------------蓝区主程序-------------------------*/
	/*-------------------------复位程序-------------------------*/
	/*-------------------------END-------------------------*/
	/*-------------------------测试程序-------------------------*/
	//垂轨刻度7.0左右为合适高度
	while(1){
		if(KEY1==0){
			
//			SG(TO_WL,kaishi);
			
			flag0=0;
			while(1)
			{
				yuanceshi();
			}
			
//			CG(TO_HIGH,1);
			
		}
		if(KEY2==0){
			
			SG(TO_WL,kaishi);
			
			flag0=0;
			while(1)
			{
				yuanceshi();
			}
			
//			SG(TO_WL,1);

		}
		if(KEY3==0){
			
			SG(TO_WL,kaishi);
			
//			SG(TO_WL,1);
//			CG(TO_HIGH,1);
			
		}
	}
}

/*------------------------------------中断服务内容-------------------------------------*/

void  ADVANCE_TIM_IRQHandler (void)
{
	
	if ( TIM_GetITStatus( ADVANCE_TIM, TIM_IT_Update) != RESET ) 
	{	
		
		Count1++;
		if(Count1==PWM[0]){GPIO_ResetBits(PWM_GPIO_Port,PWM0_Pin);} //舵机一：底部云台旋转
		if(Count1==PWM[1]){GPIO_ResetBits(PWM_GPIO_Port,PWM1_Pin);} //舵机二：旋转爪子
		if(Count1==PWM[2]){GPIO_ResetBits(PWM_GPIO_Port,PWM2_Pin);} //舵机三：爪子抓取
		if(Count1==T_PWM )
			 {
				 Count1=0;
				 GPIO_SetBits(PWM_GPIO_Port,PWM0_Pin|PWM1_Pin|PWM2_Pin);
			 }
			 
		if(CountX2 > 0) //物料盘
				{ 
					Count2++;
					if(Count2==WL)  {GPIO_ResetBits(QT_GPIO_Port,WL_Pin);}
					if(Count2==T_WL )
						{
							CountX2--;
							Count2=0;
							GPIO_SetBits(QT_GPIO_Port,WL_Pin);
						}
				}
				
		if(CountX3 > 0) //水平滑轨
				{ 
					Count3++;
					if(Count3==HG1) {GPIO_ResetBits(HG_GPIO_Port,HG1_Pin);}
					if(Count3==T_HG1 )
						{
							CountX3--;
							Count3=0;
							GPIO_SetBits(HG_GPIO_Port,HG1_Pin);
						}
				}
				
		if(CountX4 > 0) //垂直滑轨
				{ 
					Count4++;
					if(Count4==HG2) {GPIO_ResetBits(HG_GPIO_Port,HG2_Pin);}
					if(Count4==T_HG2 )
						{
							CountX4--;
							Count4=0;
							GPIO_SetBits(HG_GPIO_Port,HG2_Pin);
						}
				}
		if(flag1==0)
				{
					GPIO_SetBits(QT_GPIO_Port,CS_Pin);
					if(GPIO_ReadInputDataBit(HW_GPIO_Port,HW1_Pin) == 0)
					{
					delay_ms(270); GPIO_ResetBits(QT_GPIO_Port,CS_Pin);
					flag1=1;
					}
				}
		TIM_ClearITPendingBit(ADVANCE_TIM , TIM_FLAG_Update);
	}		 
}
/*------------------------------------THE_END-------------------------------------*/
