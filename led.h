/*
 * led.h
 *
 *  Created on: Oct 16, 2026
 *      Author: Admin
 */

#ifndef LED_H_
#define LED_H_

#define GPIOD_MODER (*(volatile unsigned int*)0x40020c00)
#define GPIOD_ODR   (*(volatile unsigned int *)0x40020c14)

#define GPIOD_MODER13_CLEAR (~(3U<<26))
#define GPIOD_MODER13_OUTPUT (1U<<26)
#define TIM3_UIF    	(1U << 0)
#define ORANGE_LED  	(1U << 13)
#endif /* LED_H_ */
