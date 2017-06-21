#ifndef __ADC__H
#define __ADC__H
#include "reg51.h"
#include "stdint.h"
#include "globaldata.h"

#define VOGAIN								215							//5000mV/256*11
#define VOMAX									614							//最大输出电压：33V/11/5*1024
#define VOMIN									204							//最小输出电压：11V/11/5*1024
#define VIMAX									614							//最大输入电压：33V/11/5*1024
#define VIMIN									204							//最小输入电压：11V/11/5*1024
#define	IOMAX									831							//最大输出电流：(30*66*3/4+2575)/5000*1024
#define VTMAX									301							//最大温度：(149°-2)*10/5000*1024

#define ADCITEN					0x20

//extern uint16_t ADC_Buf[4];
//extern uint8_t ADC_CH;

void InitADC();
uint16_t GetADCResult(unsigned char ch);
void StartADC();
void ADC_Monitor();

#endif

