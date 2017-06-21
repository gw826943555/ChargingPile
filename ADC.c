#include "ADC.h"
#include "intrins.h"
#include "stdio.h"

#define ADC_POWER		0x80
#define ADC_FLAG		0x10
#define ADC_START		0x08
#define ADC_SPEEDLL	0x00
#define ADC_SPEEDL	0x20
#define ADC_SPEEDH	0x40
#define ADC_SPEEDHH	0x60

sfr	ADC_CONTR	=				0xBC;
sfr ADC_RES		=				0xBD;
sfr ADC_LOW2	=				0xBE;
sfr P1ASF			=				0x9d;

void InitADC()
{
	P1ASF=0x0F;														//P1.0~P1.3设置为模拟输入
	ADC_RES=0;														
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL;
	//Delay(2);
}

//void StartADC()
//{
//	ADC_CONTR =ADC_POWER|ADC_SPEEDLL|ADC_START;
//	IE |= ADCITEN;												//开启ADC转换中断
//}

uint16_t GetADCResult(unsigned char ch)
{
	ADC_CONTR=ADC_POWER|ADC_SPEEDHH|ch|ADC_START;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while(!(ADC_CONTR&ADC_FLAG)) ;
	ADC_CONTR&=~ADC_FLAG;
	return ADC_RES;
}

void adc_isr() interrupt 5
{
	ADC_CONTR &=!ADC_FLAG;
}

void ADC_Monitor()
{
	static uint16_t ch=0;
	uint16_t Buf;
	Buf = GetADCResult(ch);
	ChargingStatus.Voltage[ch] = (Buf << 2) + (ADC_LOW2 & 0x03);
//	printf("ADCch%d:%d\r\n",ch,Buf);
	if(++ch>3) ch=0;
}




