#ifndef IFXGPT120_REG_H
#define IFXGPT120_REG_H

#define GPT120_BASE          0xF0001800U

#define T2                   (*(volatile unsigned int *)0xF0001834U)
#define T3                   (*(volatile unsigned int *)0xF0001838U)
#define T4                   (*(volatile unsigned int *)0xF000183CU)
#define T5                   (*(volatile unsigned int *)0xF0001840U)
#define T6                   (*(volatile unsigned int *)0xF0001844U)
#define OCS                  (*(volatile unsigned int *)0xF00018E8U)
#define KRSTCLR              (*(volatile unsigned int *)0xF00018ECU)
#define KRST1                (*(volatile unsigned int *)0xF00018F0U)
#define KRST0                (*(volatile unsigned int *)0xF00018F4U)
#define ACCEN0               (*(volatile unsigned int *)0xF00018FCU)
#define T2CON                (*(volatile unsigned int *)0xF0001810U)
#define T3CON                (*(volatile unsigned int *)0xF0001814U)
#define T4CON                (*(volatile unsigned int *)0xF0001818U)
#define T5CON                (*(volatile unsigned int *)0xF000181CU)
#define T6CON                (*(volatile unsigned int *)0xF0001820U)
#define CAPREL               (*(volatile unsigned int *)0xF0001830U)
#define PISEL                (*(volatile unsigned int *)0xF0001804U)
#define ID                   (*(volatile unsigned int *)0xF0001808U)
#define CLC                  (*(volatile unsigned int *)0xF0001800U)

#endif

