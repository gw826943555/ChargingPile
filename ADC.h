#ifndef __ADC__H
#define __ADC__H
#include "reg51.h"
#include "stdint.h"
#include "globaldata.h"

#define OutputVoltageGain 		6
#define VORATE								OutputVoltageGain*5000/255
#define VOMAX									153							//最大输出电压：33V
#define VOMIN									51							//最小输出电压：11V
#define VIMAX									153							//最大输入电压：33V
#define VIMIN									51							//最小输入电压：11V
#define	IOMAX									255							//最大输出电流：30A
#define VTMAX									255							//最大温度：

#define ADCITEN					0x20

//extern uint16_t ADC_Buf[4];
//extern uint8_t ADC_CH;

void InitADC();
uint16_t GetADCResult(unsigned char ch);
void StartADC();
void ADC_Monitor();

#endif

