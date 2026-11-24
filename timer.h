/*
 * timer.h
 *
 *  Created on: Oct 16, 2026
 *      Author: Admin
 */

#ifndef TIMER_H_
#define TIMER_H_

#define TIM3_CR1    (*(volatile unsigned int *)0x40000400)
#define TIM3_CNT    (*(volatile unsigned int *)0x40000424)
#define TIM3_PSC    (*(volatile unsigned int *)0x40000428)
#define TIM3_ARR    (*(volatile unsigned int *)0x4000042C)
#define TIM3_CCMR1  (*(volatile unsigned int *)0x40000418)
#define TIM3_CCR1   (*(volatile unsigned int *)0x40000434)
#define TIM3_CCER   (*(volatile unsigned int *)0x40000420)
#define TIM3_SR 	(*(volatile unsigned int *)0x40000410)
#define TIM3_DIER 	(*(volatile unsigned int *)0x4000040c)
#define NVIC_ISER0 	(*(volatile unsigned int *)0xE000E100)
#define TIM3_CCR2	(*(volatile unsigned int *)0x40000438)
#define TIM3_EGR 	(*(volatile unsigned int *)0x40000414)
#define TIM3_CCMR2  (*(volatile unsigned int *)0x4000041c)
#define TIM3_CCR3   (*(volatile unsigned int *)0x4000043c)
#define TIM3_CCR4   (*(volatile unsigned int *)0x40000440)

#define TIM3_EN     (1U<<1)
#define TIM3_UIE    (1U<<0)
#define TIM3_IRQ    (1U<<29)
#define TIM3_ARPE   (1U<<7)

#endif /* TIMER_H_ */
