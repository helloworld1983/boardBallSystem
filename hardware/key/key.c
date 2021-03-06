/**
  ******************************************************************************
  * @file    bsp_key.c
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  ******************************************************************************
  */ 
	

#include "key.h" 
#include "delay.h"
#include "sys.h"

key_t key;
/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口（PF）的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//选择通用推挽输出 
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Key_button(void)
{	
	int8_t KeyVal = -1;//返回键值
	GPIO_Write(GPIOC,(GPIOC->ODR & 0xf0ff | 0x0100)); //让F口的8-11输出二进制数0001
	
	if((GPIOC->IDR & 0xf000)>0x0000)
	{
		delay_ms(10);
		if((GPIOC->IDR & 0xf000)>0x0000)
		{
		
	      switch(GPIOC->IDR & 0xf000)//对输入的12-15键值进行判断每列开始扫描 
	       {
		         case 0x1000: KeyVal=2; break;    
		         case 0x2000: KeyVal=3; break;    
		         case 0x4000: KeyVal=1; break;   
		         case 0x8000: KeyVal=4; break;   
			}
    	}
  }
	
	GPIO_Write(GPIOC,(GPIOC->ODR & 0xf0ff | 0x0200));   
	
	if((GPIOC->IDR & 0xf000)>0x0000)
	{
		delay_ms(10);
		if((GPIOC->IDR & 0xf000)>0x0000)
		{
		
	      switch(GPIOC->IDR & 0xf000)//对输入的12-15键值进行判断每列开始扫描 
	       {

				 case 0x1000: KeyVal=6; break;    
		         case 0x2000: KeyVal=7; break;   
		         case 0x4000: KeyVal=5; break;    
		         case 0x8000: KeyVal=8; break;
         }
    }
  }
	
	GPIO_Write(GPIOC,(GPIOC->ODR & 0xf0ff | 0x0400));   
	
	if((GPIOC->IDR & 0xf000)>0x0000)
	{
		delay_ms(10);
		if((GPIOC->IDR & 0xf000)>0x0000)
		{
		
	      switch(GPIOC->IDR & 0xf000)//对输入的12-15键值进行判断每列开始扫描 
	       {
		         case 0x1000: KeyVal=10; break;    
		         case 0x2000: KeyVal=11; break;   
		         case 0x4000: KeyVal=9; break;    
		         case 0x8000: KeyVal=12; break;
         }
    }
  }
	
	GPIO_Write(GPIOC,(GPIOC->ODR & 0xf0ff | 0x0800));   
	
	if((GPIOC->IDR & 0xf000)>0x0000)
	{
		delay_ms(10);
		if((GPIOC->IDR & 0xf000)>0x0000)
		{
		
	      switch(GPIOC->IDR & 0xf000)//对输入的12-15键值进行判断每列开始扫描 
	       {
				 case 0x1000: KeyVal=14; break;    
		         case 0x2000: KeyVal=15; break;   
		         case 0x4000: KeyVal=13; break;    
		         case 0x8000: KeyVal=16; break;
         }
    }
  }
	if(KeyVal != -1){
		key.isPress = true;
		key.data = KeyVal;
		delay_ms(100);
	}
}
/*********************************************END OF FILE**********************/
