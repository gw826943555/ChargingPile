#include "reg51.h"
#include "stdint.h"

typedef enum
{
	false = 0,
	true,
}bool;

typedef struct
{
	int16_t period_;
	int16_t reset_time_;
	bool is_reset;
}TimerTypedef;

void Timer_Init();
uint8_t timer_is_timeup(TimerTypedef* this);
void timer_reset(TimerTypedef* this);
void timer_set_period(TimerTypedef* this, uint16_t base_tick);
uint16_t timer_get_time(TimerTypedef* this);
void delay_ms(uint16_t delay_time);
