#include "reg51.h"
#include "intrins.h"
#include "stdio.h"
#include "uart.h"
#include "ADC.h"
#include "globaldata.h"
#include "timer.h"
#include "DIO.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define VoltGain 			11
#define VoltConnectMin	(20*255/11/5)

sfr T2H				=				0xd6;
sfr T2L				=				0xd7;
sfr AUXR			=				0x8e;
sfr P1M1			=				0x91;
sfr P1M0			=				0x92;
sfr P3M1		 	= 			0xb1;
sfr P3M0 			= 			0xb2;

#define InfaredSignal 0x04
sbit ChargeCtrl = 	P1^4;
sbit P15				=		P1^5;

char buf[]="System Running...\r\n";

void Show_Status();

void main()
{
	TimerTypedef HeartBeat;
	InitUart();													//初始化串口1
	InitADC();
	Key_Init();
	printf("System Start\r\n");
	Timer_Init();
	IE |= 0x80;
	timer_set_period(&HeartBeat,500);
	timer_reset(&HeartBeat);
	while(1)
	{
		Key_Monitor();
		ADC_Monitor();
		Charge_Monitor();
		if(timer_is_timeup(&HeartBeat))
		{
			timer_reset(&HeartBeat);
			Show_Status();
		}
	}
}

void Show_Status()
{
	static uint16_t step;
	switch(step)
	{
		case 0:
		{
			++step;
			printf("OutputVoltage:%dmV\r\n",ChargingStatus.Voltage[0]*117);
			break;
		}
		case 1:
		{
			++step;
			printf("InputVoltage:%dmV\r\n",0);
			break;
		}
		case 2:
		{
			++step;
			printf("InputVoltage:%dmV\r\n",0);
			break;
		}
		default:
		{
			printf(FaultMessage[ChargingStatus.Fault]);
			printf(buf);
			step =0;
			break;
		}
	}
}



