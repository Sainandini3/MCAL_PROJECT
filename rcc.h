/*
 * rcc.h
 *
 *  Created on: Oct 16, 2026
 *      Author: Admin
 */
#ifndef RCC_H_
#define RCC_H_

#define RCC_AHB1ENR (*(volatile unsigned int *)0x40023830)
#define RCC_APB1ENR (*(volatile unsigned int *)0x40023840)

#define GPIOD_EN    (1U<<3)
#define GPIOA_EN    (1U<<0)
#define GPIOB_EN    (1U<<1)
#endif /* RCC_H_ */
