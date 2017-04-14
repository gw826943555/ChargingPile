#include "reg51.h"
#include "intrins.h"
#include "stdio.h"
#include "uart.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define VoltGain 			11
#define VoltConnectMin	(20*255/11/5)

sfr T2H				=				0xd6;
sfr T2L				=				0xd7;
sfr AUXR			=				0x8e;
sfr	ADC_CONTR	=				0xBC;
sfr ADC_RES		=				0xBD;
sfr ADC_LOW2	=				0xBE;
sfr P1ASF			=				0x9d;
sfr P3M1		 	= 			0xb1;
sfr P3M0 			= 			0xb2;

#define InfaredSignal 0x04
sbit ChargeCtrl = P3^7;

#define ADC_POWER		0x80
#define ADC_FLAG		0x10
#define ADC_START		0x08
#define ADC_SPEEDLL	0x00
#define ADC_SPEEDL	0x20
#define ADC_SPEEDH	0x40
#define ADC_SPEEDHH	0x60

enum 
{
	Discharge,
	Charging
}Charge_Status;

void InitADC();
void SendData(BYTE dat);
BYTE GetADCResult(BYTE ch);
void Delay(WORD n);
void ShowResult(BYTE ch);
void InitIO();

void main()
{
	BYTE VoltOut=0x00;
	BYTE VoltIn=0x00;
	InitUart();
	InitADC();
	InitIO();
	Charge_Status=Discharge;
	printf("System Start\r\n");
	while(1)
	{
		if(Charge_Status==Discharge)
		{
			ChargeCtrl = 0;
			VoltOut=GetADCResult(0);
			//printf("Discharge\r\n");
			//printf("Out Voltage:%2.3f\r\n",(float)VoltOut*5*VoltGain/255);
			if((VoltOut > VoltConnectMin)&&(P3&InfaredSignal))
			{
				Charge_Status = Charging;
			}
		}
		if(Charge_Status==Charging)
		{
			VoltOut=GetADCResult(0);
			if((VoltOut <= VoltConnectMin))
			{
				ChargeCtrl = 0;
				Charge_Status = Discharge;
			}
			if((P3&InfaredSignal)==0)
			{
				ChargeCtrl = 0;
				Charge_Status = Discharge;
			}
			ChargeCtrl = 1;
			//printf("Charging\r\n");
			//printf("Out Voltage:%2.3f\r\n",(float)VoltOut*5*VoltGain/255);
		}
		if(P3&InfaredSignal)
		{
			printf("Infared High\r\n");
		}else{
			printf("Infared LOW\r\n");
		}
	}
}

void ShowResult(BYTE ch)
{
	SendData(ch);
	SendData(GetADCResult(ch));
	SendData(00);
}

BYTE GetADCResult(BYTE ch)
{
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL|ch|ADC_START;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while(!(ADC_CONTR&ADC_FLAG)) ;
	ADC_CONTR&=~ADC_FLAG;
	return ADC_RES;
}

void InitADC()
{
	P1ASF=0xff;
	ADC_RES=0;
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL;
	Delay(2);
}

void InitIO()
{
	P3M0 = P3M0|0x80;	//P3^7推挽输出
	P3M1 = P3M1&0x7F;
	P3M0 = P3M0|0x04;	//P3^2高阻输入
	P3M1 = P3M1|0x04;
}

void SendData(BYTE dat)
{
	while(!TI) ;
	TI= 0;
	SBUF = dat;
}

void Delay(WORD n)
{
	WORD x;
	while(n--)
	{
		x=5000;
		while(x--) ;
	}
}