/*
 * led.c
 *
 *  Created on: Oct 16, 2026
 *      Author: Admin
 */


#include "headers.h"
int count=0;
void led_init()
{
	RCC_AHB1ENR|=GPIOD_EN;
	GPIOD_MODER&=GPIOD_MODER13_CLEAR ;
	GPIOD_MODER|=GPIOD_MODER13_OUTPUT;

}
void TIM3_IRQHandler()
{
    if(TIM3_SR&TIM3_UIF)
    {
        TIM3_SR&=~TIM3_UIF;
        count++;
        if(count>=500)
        {
        	count=0;
        	GPIOD_ODR=GPIOD_ODR^ORANGE_LED;
        }
    }
}
