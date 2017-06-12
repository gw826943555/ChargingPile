#include "reg51.h"
#include "stdint.h"

typedef struct
{
	int16_t period_;
	int16_t reset_time_;
}TimerTypedef;

void Timer_Init();
uint8_t timer_is_timeup(TimerTypedef* this);
void timer_reset(TimerTypedef* this);
void timer_set_period(TimerTypedef* this, uint16_t base_tick);
uint16_t timer_get_time(TimerTypedef* this);
void delay_ms(uint16_t delay_time);
