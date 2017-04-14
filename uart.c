#include "uart.h"

sfr T2H				=				0xd6;
sfr T2L				=				0xd7;
sfr AUXR			=				0x8e;

void InitUart()
{
	SCON = 0x5a;
	T2L = 0xd8;
	T2H = 0xff;
	AUXR = 0x14;
	AUXR |= 0x01;
}



