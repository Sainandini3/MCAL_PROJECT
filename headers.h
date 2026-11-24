/*
 * headers.h
 *
 *  Created on: Oct 16, 2026
 *      Author: Admin
 */

#ifndef HEADERS_H_
#define HEADERS_H_

typedef enum
{
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4,

}TimerType;
typedef enum
{
	CH1,
	CH2,
	CH3,
	CH4
}ChannelType;

#include <stdint.h>
#include "timer.h"
#include "led.h"
#include "pwm.h"
#include "rcc.h"

void led_init();
void pwm_init(TimerType timer,ChannelType channel,uint32_t duty_cycle);
void timer3_init(ChannelType,uint32_t);
void timer3_ch1(uint32_t duty_cycle);
void timer3_ch2(uint32_t duty_cycle);
void timer3_ch3(uint32_t duty_cycle);
void timer3_ch4(uint32_t duty_cycle);
void timer3_start();

#define DUTY_CYCLE_CH1 100
#define DUTY_CYCLE_CH2 500
#define DUTY_CYCLE_CH3 750
#define DUTY_CYCLE_CH4 1000
#define NULL (void *)0

#endif /* HEADERS_H_ */
