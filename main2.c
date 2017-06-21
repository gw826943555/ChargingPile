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
	int16_t temp=0;
	switch(step)
	{
		case 0:
		{
			++step;
			temp = (int32_t)ChargingStatus.Voltage[0] * 5000 * 11 / 1024;
			printf("Info:OutputVoltage %dmV\r\n",temp);
			break;
		}
		case 1:
		{
			++step;
			temp = (int32_t)ChargingStatus.Voltage[1] * 5000 * 11 / 1024;
			printf("Info:InputVoltage %dmV\r\n",temp);
			break;
		}
		case 2:
		{
			++step;
			temp = ((int32_t)ChargingStatus.Voltage[2] * 5000 / 1024 -2575)* 3 / 4 / 66;			//66mV/A 0.75倍衰减
			printf("Info:OutputCurrent %dA\r\n",temp);
			break;
		}
		case 3:
		{
			++step;
			temp = ((int32_t)ChargingStatus.Voltage[3] * 5000 / 1024)/10-2;										//10mV/A 2~150
			printf("Info:Temperature %d\r\n",temp);
			break;
		}
		default:
		{
			printf(FaultMessage[ChargingStatus.Fault]);
			step =0;
			break;
		}
	}
}



