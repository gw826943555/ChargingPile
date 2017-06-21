#include "timer.h"
#include "stdio.h"

#define T1MS		(65536-18432000L/12/1000)

sfr		AUXR	=				0x8e;
sbit 	P15 	=				P1^5;

volatile uint16_t base_time_ = 0;

void Timer_Init()
{
	AUXR &= 0x7f;							//定时器0为12T模式
	TMOD &= 0xF0;							//定时器0为16位自动重装载
	TL0 = T1MS;
	TH0 = T1MS>>8;
	TR0 = 1;
	ET0 = 1;
}

void tm0_isr() interrupt 1 using 1
{
	++base_time_;
}

/**
  * @brief  judge if timer is time up since resetted
  * @param  this pointer
	* @retval 0: not time up
	* @retval 1: is time up
  */
uint8_t timer_is_timeup(TimerTypedef* this)
{
	if(base_time_ - this->reset_time_ > this->period_)
	{
		this -> is_reset = false;
		return 1;
	}else
	{
		return 0;
	}
}

/**
  * @brief  reset timer
  * @param  this pointer
	* @retval None
  */
void timer_reset(TimerTypedef* this)
{
	this -> is_reset = true;
	this->reset_time_ = base_time_;
}

/**
  * @brief  set the period of timer
	* @param  this: this pointer
	* @param  base_tick: period evaluated by ticks
	* @retval None
  */
void timer_set_period(TimerTypedef* this, uint16_t base_tick)
{
	this->period_ = base_tick;
}

/**
  * @brief  get time of a timer
	* @param  this: this pointer
	* @retval ticks since timer resetted
  */
uint16_t timer_get_time(TimerTypedef* this)
{
	return (base_time_ - this->reset_time_);
}

/**
  * @brief  delay some ms
	* @param  how many ms
	* @retval None
	* @Note: here regard base tick 1ms
  */
void delay_ms(uint16_t delay_time)
{
	int32_t enter_time = base_time_;
	while(base_time_ - enter_time < delay_time);
}