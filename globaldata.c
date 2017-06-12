#include "globaldata.h"
#include "ADC.h"

code char FaultMessage[7][32]=
{
	"Infared is high\r\n",
	"OutputVoltage is low\r\n",
	"OutputVoltage is high\r\n",
	"InputVoltage is low\r\n",
	"InputVoltage is high\r\n",
	"OutputCurrent too high\r\n",
	"Temperature too high\r\n"
};

DeviceTypedef ChargingStatus;

void Charge_Monitor()
{
	if((ChargingStatus.IO1==LOW)&(ChargingStatus.Voltage[0]>VOMIN))				//满足条件，充电
	{
		ChargingStatus.isCharging = Charging;
	}
	
	if(ChargingStatus.IO1==HIGH)																					//红外未被触发
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = INFAREDLOW;
	}
	
	if(ChargingStatus.Voltage[0]>VOMIN)																		//充电口电压过低
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = VOLOW;
	}
	
	if(ChargingStatus.Voltage[0]>VOMAX)																		//电池电压过高
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = VOHIGH;
	}
	
	if(ChargingStatus.Voltage[1]>VIMAX)																		//输入电压过高
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = VIHIGH;
	}
	
	if(ChargingStatus.Voltage[1]<VIMIN)																		//输入电压过过低
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = VILOW;
	}
	
	if(ChargingStatus.Voltage[2]>IOMAX)																		//充电电流过大
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = IOHIGH;
	}
	
	if(ChargingStatus.Voltage[3]>VTMAX)																		//温度过高
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = VTHIGH;
	}
	
	if(ChargingStatus.isCharging==Discharge)
	{
		ChargingCtrl = 0;
	}
	if(ChargingStatus.isCharging==Charging)
	{
		ChargingCtrl = 1;
	}
}

