/*
 * pwm.h
 *
 *  Created on: Oct 16, 2026
 *      Author: Admin
 */



#ifndef PWM_H_
#define PWM_H_

#define GPIOA_MODER (*(volatile unsigned int *)0x40020000)
#define GPIOA_AFRL  (*(volatile unsigned int *)0x40020020)

#define GPIOB_MODER (*(volatile unsigned int *)0x40020400)
#define GPIOB_AFRL 	(*(volatile unsigned int *)0x40020420)

#define PA6_MODE_CLEAR    (~(3U << 12))
#define PA6_AF_MODE       (1U << 13)
#define PA6_AF_CLEAR    (~(15U << 24))
#define PA6_TIM3_AF     (1U << 25)
#define CH1_OCM_CLEAR       (~(7U << 4))
#define CH1_PWM_MODE        (6U << 4)
#define CH1_OC_PRELOAD      (1U << 3)
#define CH1_CC_POLARITY    (~(1U << 1))
#define CH1_CC_ENABLE       (1U << 0)
#define TIM3_UPDATE_EVENT   (1U << 0)
#define TIM3_COUNTER_ENABLE (1U << 0)

#define PA7_MODE_CLEAR          (~(3U << 14))
#define PA7_AF_MODE             (1U << 15)
#define PA7_AF_CLEAR            (~(15U << 28))
#define PA7_TIM3_AF             (1U << 29)
#define CH2_OCM_CLEAR           (~(7U << 12))
#define CH2_PWM_MODE            (6U << 12)
#define CH2_OC_PRELOAD          (1U << 11)
#define CH2_CC_POLARITY_CLEAR   (~(1U << 5))
#define CH2_CC_ENABLE           (1U << 4)

#define PB0_MODE_CLEAR          (~(3U << 0))
#define PB0_AF_MODE             (2U << 0)
#define PB0_AF_CLEAR            (~(15U << 0))
#define PB0_TIM3_AF             (2U << 0)
#define CH3_OCM_CLEAR           (~(7U << 4))
#define CH3_PWM_MODE            (6U << 4)
#define CH3_OC_PRELOAD          (1U << 3)
#define CH3_CC_POLARITY_CLEAR   (~(1U << 9))
#define CH3_CC_ENABLE           (1U << 8)

#define PB1_MODE_CLEAR          (~(3U << 2))
#define PB1_AF_MODE             (2U << 2)
#define PB1_AF_CLEAR            (~(15U << 4))
#define PB1_TIM3_AF             (2U << 4)
#define CH4_OCM_CLEAR           (~(7U << 12))
#define CH4_PWM_MODE            (6U << 12)
#define CH4_OC_PRELOAD          (1U << 11)
#define CH4_CC_POLARITY_CLEAR   (~(1U << 13))
#define CH4_CC_ENABLE           (1U << 12)
#endif /* PWM_H_ */
