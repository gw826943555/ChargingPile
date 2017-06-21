#ifndef __GLOBALDATA__H
#define __GLOBALDATA__H

#include "stdint.h"
#include "reg51.h"

sbit ChargingCtrl=P1^4;

typedef enum
{
	LOW,
	HIGH
} IOTypedef;

typedef enum 
{
	Charging,
	Discharge
}ChargingStatusTypedef;

typedef struct
{
	enum
	{
		NOFAULT=0,
		INFAREDLOW,
		VOLOW,
		VOHIGH,
		VILOW,
		VIHIGH,
		IOHIGH,
		VTHIGH,
		FORCEMODE,
	}Fault;
	IOTypedef	IO0,IO1,IO2;
	int16_t Voltage[4];
	ChargingStatusTypedef isCharging;
} DeviceTypedef;	

extern DeviceTypedef ChargingStatus;
extern code char FaultMessage[9][32];


void Charge_Monitor();


#endif
