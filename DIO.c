#include "DIO.h"
#include "stdio.h"

sfr P1M1			=				0x91;
sfr P1M0			=				0x92;
sfr P3M1		 	= 			0xb1;
sfr P3M0 			= 			0xb2;

sbit DI0			=				P3^6;
sbit DI1			=				P3^3;
sbit DI2			=				P3^2;

void Key_Init()
{
	P3M0 = P3M0|0x10;				//P1^4推挽输出
	P3M1 = P3M0&0xEF;
	P3M0 = P3M0|0x04;				//P3^2开漏输入
	P3M1 = P3M1|0x04;
	P3M0 = P3M0|0x08;				//P3^3开漏输入
	P3M1 = P3M1|0x08;
	P3M0 = P3M0|0x40;				//P3^6开漏输入
	P3M1 = P3M1|0x40;
}

void Key_Monitor()
{
	if(DI0 == 0)
	{
		ChargingStatus.IO0 = LOW;
//		printf("DI0 LOW\r\n");
	}else
	{
		ChargingStatus.IO0 = HIGH;
//		printf("DI0 HIGH\r\n");
	}
	
	if(DI1 == 1)
	{
		ChargingStatus.IO1 = HIGH;
	}else
	{
		ChargingStatus.IO1 = LOW;
	}
	
	if(DI2 == 0)
	{
		ChargingStatus.IO2 = LOW;
	}else
	{
		ChargingStatus.IO2 = HIGH;
	}
}