#include "key.h"
#include "delay.h" 
//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //GPIO设定|GPIO_Pin_5||GPIO_Pin_6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE
}

////按键扫描函数
//u8 KEY_Scan(void)
//{
//	u16 temp=0;
//	u8 key=0;
//	temp=GPIO_ReadInputData(GPIOE);
//	temp&=0x0F00;
//	if(temp==0x0E00)key=1;
//	else if(temp==0x0D00)key=2;
//	else if(temp==0x0B00)key=3;
//	else if(temp==0x0700)key=4;
//	else key=0;
//	temp=GPIO_ReadInputData(GPIOE);
//	temp&=0xF000;
//	if((temp==0XE000)&&(key!=0))key=(key-1)*4+1;
//	else if((temp==0XD000)&&(key!=0))key=(key-1)*4+2;
//	else if((temp==0XB000)&&(key!=0))key=(key-1)*4+3;
//	else if((temp==0X7000)&&(key!=0))key=(key-1)*4+4;
//	else key=0;
//	return key;
//}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY1按下
//2，KEY2按下
//3，KEY3按下 
//4，KEY3按下
//注意此函数有响应优先级,KEY1>KEY2>KEY3>KEY4按下!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3;
		else if(KEY4==0)return 4;
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	    
 	return 0;// 无按键按下
}
