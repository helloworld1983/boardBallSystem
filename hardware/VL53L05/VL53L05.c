#include "VL53L05.h"
#include "myiic5.h"


#define VL53L0X_REG_IDENTIFICATION_MODEL_ID         0xc0
#define VL53L0X_REG_IDENTIFICATION_REVISION_ID      0xc2
#define VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD   0x50
#define VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
#define VL53L0X_REG_SYSRANGE_START                  0x00
#define VL53L0X_REG_RESULT_INTERRUPT_STATUS         0x13
#define VL53L0X_REG_RESULT_RANGE_STATUS             0x14
#define VL53L0X_Add 0x29


//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 VL53L05X_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
  IIC5_Start(); 
	IIC5_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(IIC5_Wait_Ack())	//等待应答
	{
		IIC5_Stop();		 
		return 1;		
	}
    IIC5_Send_Byte(reg);	//写寄存器地址
    IIC5_Wait_Ack();		//等待应答
	for(i=0;i<len;i++)
	{
		IIC5_Send_Byte(buf[i]);	//发送数据
		if(IIC5_Wait_Ack())		//等待ACK
		{
			IIC5_Stop();	 
			return 1;		 
		}		
	}    
    IIC5_Stop();	 
	return 0;	
} 
//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 VL53L05X_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	IIC5_Start(); 
	IIC5_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(IIC5_Wait_Ack())	//等待应答
	{
		IIC5_Stop();		 
		return 1;		
	}
    IIC5_Send_Byte(reg);	//写寄存器地址
    IIC5_Wait_Ack();		//等待应答
    IIC5_Start();
	  IIC5_Send_Byte((addr<<1)|1);//发送器件地址+读命令	
    IIC5_Wait_Ack();		//等待应答 
	while(len)
	{
		if(len==1)
			*buf=IIC5_Read_Byte(0);//读数据,发送nACK 
		else 
			*buf=IIC5_Read_Byte(1);		//读数据,发送ACK 
		len--;
		buf++; 
	}    
    IIC5_Stop();	//产生一个停止条件 
	return 0;	
}
//IIC写一个字节 
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 VL53L05X_Write_Byte(u8 reg,u8 data) 				 
{ 
  IIC5_Start(); 
	IIC5_Send_Byte((VL53L0X_Add<<1)|0);//发送器件地址+写命令	
	if(IIC5_Wait_Ack())	//等待应答
	{
		IIC5_Stop();		 
		return 1;		
	}
  IIC5_Send_Byte(reg);	//写寄存器地址
  IIC5_Wait_Ack();		//等待应答 
	IIC5_Send_Byte(data);//发送数据
	if(IIC5_Wait_Ack())	//等待ACK
	{
		IIC5_Stop();	 
		return 1;		 
	}	 
  IIC5_Stop();	 
	return 0;
}
//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 VL53L05X_Read_Byte(u8 reg)
{
	u8 res;
  IIC5_Start(); 
	//IIC_Send_Byte((VL53L0X_Add<<1)|0);//发送器件地址+写命令	
	IIC5_Send_Byte(0x52);//发送器件地址+写命令	
	IIC5_Wait_Ack();		//等待应答 
  IIC5_Send_Byte(reg);	//写寄存器地址
  IIC5_Wait_Ack();		//等待应答
  IIC5_Start();
	IIC5_Send_Byte(0x53 );//发送器件地址+读命令	
  IIC5_Wait_Ack();		//等待应答 
	res=IIC5_Read_Byte(0);//读取数据,发送nACK 
  IIC5_Stop();			//产生一个停止条件 
	return res;		
}







