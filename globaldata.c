#include "globaldata.h"
#include "ADC.h"
#include "timer.h"

code char FaultMessage[9][32]=
{
	"Info:Charging\r\n",
	"Warning:Infared not triggerd\r\n",
	"Warning:Low OutputVoltage\r\n",
	"Warning:High OutputVoltage\r\n",
	"Warning:Low InputVoltage\r\n",
	"Warning:High InputVoltage\r\n",
	"Warning:High OutputCurrent\r\n",
	"Warning:High Temperature\r\n",
	"Warning:Forced Charging Mode\r\n"
};

DeviceTypedef ChargingStatus;

void Charge_Monitor()
{
//	static TimerTypedef HysteresisTimer;
//	static ChargingStatusTypedef st = Discharge;
	ChargingStatus.Fault = NOFAULT;
	if((ChargingStatus.IO1 == LOW)&&(ChargingStatus.Voltage[0]>VOMIN))				//满足条件，充电
	{
		ChargingStatus.isCharging = Charging;
	}
	
	if(ChargingStatus.IO1 == HIGH)																					//红外未被触发
	{
		ChargingStatus.isCharging = Discharge;
		ChargingStatus.Fault = INFAREDLOW;
	}
	
	if(ChargingStatus.Voltage[0]<VOMIN)																		//充电口电压过低
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
	
	if(ChargingStatus.IO0 == HIGH)																					//强制开关，最高优先级
	{
//		ChargingStatus.isCharging = Charging;
//		st = Charging;
//		ChargingStatus.isCharging = Charging;
//		ChargingStatus.Fault = FORCEMODE;
	}
	
//	if((st == Charging)&(ChargingStatus.IO0 == LOW))											//强制开关断开
//	{
//		st = Discharge;
//		timer_set_period(&HysteresisTimer,1000);
//		timer_reset(&HysteresisTimer);
//	}
//	
//	if(HysteresisTimer.is_reset == true)
//	{
//		if( timer_is_timeup(&HysteresisTimer) == 0)													//迟滞定时未到
//		{
//			ChargingStatus.isCharging = Discharge;
//		}
//	}
	
	if(ChargingStatus.isCharging==Discharge)
	{
		ChargingCtrl = 0;
	}
	if(ChargingStatus.isCharging==Charging)
	{
		ChargingCtrl = 1;
	}
}

