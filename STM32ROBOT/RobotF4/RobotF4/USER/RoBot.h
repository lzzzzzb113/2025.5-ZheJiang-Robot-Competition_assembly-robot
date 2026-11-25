#ifndef _RoBot_h
#define _RoBot_h

#endif

#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "key.h"
#include "usart.h"
/*------------------------全局变量----------------------*/
extern uint32_t PWM[3],WL,HG1,HG2,T_WL,T_HG1,T_HG2,T_PWM,
	
	Count1,CountX2,CountX3,CountX4,Count2,Count3,Count4,

	A,B,C,Ax,Bx,Cx,

	y,f,s,t,l,

	read_again,Boo,i,check,running,

	flag0,flag1,flag9;
/*------------------------滑轨电机----------------------*/
//水平滑轨：细分800条件下60圈走完全程——水平滑轨行程全长300mm约等于1圈5mm
//水平滑轨：细分1600条件下60圈走完全程——水平滑轨行程全长300mm约等于1圈5mm
#define qs1  1 //水平滑轨圈数 
#define xf1  800 //水平滑轨细分
//垂直滑轨：细分800条件下127圈走完全程——垂直滑轨行程全长260mm约等于1圈2.047mm
//垂直滑轨：细分400条件下61圈走完全程——垂直滑轨行程全长260mm约等于1圈4.26mm
#define qs2  1 //垂直滑轨圈数
#define xf2  400 //垂直滑轨细分
//物料盘：细分400条件下xx圈走完全程——约等于x圈45°
#define qs3  1 //物料盘圈数
#define xf3  258 //物料盘细分 物理细分400
/*------------------------舵机映射----------------------*/
#define PWM_GPIO_Port 	    GPIOC

#define PWM0_Pin 					GPIO_Pin_0 //舵机一：底部云台旋转 单片机：pin口所在右1中
#define PWM1_Pin 					GPIO_Pin_6 //舵机二：旋转爪子 单片机：pin口所在左2上
#define PWM2_Pin 					GPIO_Pin_12 //舵机三：爪子抓取 单片机：pin口所在左2中
/*------------------------摄像头映射----------------------*/
#define Read_GPIO_Port  	GPIOB 

#define Read1_Pin 				GPIO_Pin_6 //摄像头信号端子1 单片机：pin口所在左1底 P7
#define Read2_Pin 				GPIO_Pin_7 //摄像头信号端子2 单片机：pin口所在左2底 P8
#define Read3_Pin 				GPIO_Pin_15 //摄像头信号端子3 单片机：pin口所在左1上 P9

#define P7                      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define P8                      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define P9                      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
/*------------------------红外映射----------------------*/
#define HW_GPIO_Port  	GPIOB 

#define HW1_Pin 				GPIO_Pin_0 //摄像头信号端子1 单片机：pin口所在右1上
#define HW2_Pin 				GPIO_Pin_1 //摄像头信号端子2 单片机：pin口所在右2上
#define HW3_Pin 				GPIO_Pin_12 //摄像头信号端子3 单片机：pin口所在右2顶
/*------------------------物料盘、传送带（其它）映射----------------------*/
#define QT_GPIO_Port    GPIOA //其它映射端口

#define CS_Pin 				GPIO_Pin_4 //传送带信号 单片机：pin口所在右1中
#define WL_Pin 				GPIO_Pin_6 //物料盘PWM波 单片机：pin口所在右1中
#define WLF_Pin 				GPIO_Pin_15 //物料盘方向 单片机：pin口所在左1中
/*------------------------滑轨映射----------------------*/
#define HG_GPIO_Port  	GPIOC

#define HG1_Pin  				GPIO_Pin_7 //水平滑轨PWM波 单片机：pin口所在左1上
#define HF1_Pin  				GPIO_Pin_2 //水平滑轨方向 单片机：pin口所在右1中

#define HG2_Pin  				GPIO_Pin_13 //垂直滑轨PWM波 单片机：pin口所在右1底
#define HF2_Pin  				GPIO_Pin_3 //垂直滑轨方向 单片机：pin口所在右2中
/*------------------------中断映射----------------------*/
#define            ADVANCE_TIM                   TIM1 //高级定时器TIM1
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd //挂载时钟开启
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM1
#define            ADVANCE_TIM_Period            (10-1) //设置自动重装载值
#define            ADVANCE_TIM_Prescaler         167 //设置预分频值
#define            ADVANCE_TIM_IRQ               TIM1_UP_TIM10_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM1_UP_TIM10_IRQHandler
/*------------------------修饰映射----------------------*/
#define YES_YES_YES  All_Config(); //总配置文件映射
#define QD_QD_QD  All_Main(); //总执行文件映射

#define TO_CS			0 	//水平滑轨往传送带
#define TO_WL			1 	//水平滑轨往物料盘
#define TO_HIGH			0 	//垂直滑轨升高
#define TO_LOW			1 	//垂直滑轨降低
#define CLOCK_Z			0 	//物料盘顺时针
#define CLOCK_N			1 	//物料盘逆时针

#define kaishi			39 	//开始移动到静止的识别位置
#define QW_CS			19 	//前往传送带正上抓取
#define LOW_ZZ			20 	//降下爪子
#define QW_WLread		5 	//前往物料盘识别
#define LOW_read		19 	//降下摄像头
#define QW_WL			19 	//前往物料盘正上放置
#define LOW_WL			7 	//降下爪子
#define SG_FW			5 	//水平滑轨复位
#define CG_FW			31 	//垂直滑轨复位

/*-------------舵机映射修饰-------------*/
#define CLAW_GRASP_S	 	90  	//爪子抓取三角
#define CLAW_GRASP_T	 	105  	//爪子抓取梯形
#define CLAW_GRASP_Y	 	82  	//爪子抓取圆形
#define CLAW_GRASP_F	 	110  	//爪子抓取方形
#define CLAW_UNCLASP		176 	//爪子松开
#define S_T_Y_J  			119 	//三角和梯形和圆和方形 119
#define S	  				54 		//三角 54
#define T	  				119 	//梯形 119
#define Y	 				119		//圆形 119
#define F  					119 	//方形 119
#define DIR_WL	 			150+69  //朝向物料盘
#define DIR_CS 				150-63  //朝向传送带
/*------------------------函数列表----------------------*/
void All_Config(void); //总配置文件
void All_Main(void); //总执行文件

void PWM_Config(void); //PWM配置(舵机)
void Read_Config(void); //摄像头配置
void HW_Config(void); //红外配置
void QT_Config(void); //其它配置
void HG_Config(void); //滑轨配置
void ADVANCE_TIM_Init(void); //定时器TIM1初始化
void Syntax_ABC(uint16_t a1,uint16_t b1,uint32_t c1); //舵机一、二、三转动函数
void read_123(void); //读取1、2、3端口openmv信号
void yans(uint32_t t); //延时(旧)
void delay_ms(u16 nms); //延时函数,ms级别,nms:0~65535
void delay_us(u32 nus); //延时函数,us级别,nus的值,不要大于798915us
void DJ(uint8_t a,uint8_t past,uint8_t last); //底部舵机封装
void SG(unsigned int m,unsigned int qs); //水平滑轨封装
void CG(unsigned int m,unsigned int qs); //垂直滑轨封装
void XZ(unsigned int m,unsigned int qs); //物料盘
void yuan(void); //圆形分程序
void fang(void); //方形分程序
void san(void); //三角分程序
void ti(void); //梯形分程序
void beifen(void); //垫底方案
void zonghe(void); //综合圆形和方形程序//测试
void yuanceshi(void); //圆形测试
void quanbu(void); //完整
void yuan_F(void);//圆形红区
void yuanceshi_F(void);//圆形测试红区
/*-------------------------位置参数记录-------------------------*/
/*
垂直滑轨
上限高度为6.8左右
此高度为摄像头识别传送带物料合适高度

随后下降高度抓取物料，在抬升高度转向 //下降 抬升

转向后，有两个高度，其一为摄像头识别高度，其二为爪子放下物料高度 //下降 下降
这两个均为下降高度

即复原高度为四个高度叠加取反

水平滑轨
静止位置为无电机侧底边
贴黑胶位置为摄像头识别传送带物料的合适位置

向传送带移动有一参数A，为抓取物料的合适位置

转向物料盘后，有二参数B、C，其一为摄像头识别的合适位置，其二为爪子放下物料的合适位置

复原位置为三个参数叠加取反

*/
/*-------------------------底部舵机转动-------------------------*/
//	unsigned long int tt=past,tf=300000,ts=0;
//	if(past<last)
//	{
//		while(tt<last)
//		{
//			if(tt<(last-8)) 
//				Syntax_ABC(nn,tt,tf);
//			else
//				{Syntax_ABC(nn,tt,tf+ts);ts+=15000;}
//			tt++;
//		}
//		ts=0;
//		delay_ms(1000);
//	}
//	else if(past>last)
//	{
//		//超过一点，减小抖动
//		while(tt>(last-10)){
//			if(tt>last) 
//				Syntax_ABC(nn,tt,tf);
//			else
//				{Syntax_ABC(nn,tt,tf+ts);ts+=15000;}
//			tt--;
//		}
//		ts=0;
//		delay_ms(100);
//		while(tt<last){
//			if(tt<(last-10))
//				Syntax_ABC(nn,tt,tf);
//			else
//				{Syntax_ABC(nn,tt,tf+ts);ts+=15000;}
//			tt++;
//			delay_ms(1000);
//		}
//	}
