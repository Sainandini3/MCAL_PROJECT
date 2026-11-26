
#ifndef GPT_HW_H
#define GPT_HW_H

#include <MCAL/Gpt/Gpt.h>
//#include <MCAL/Gpt/Gpt_Reg.h>

typedef struct
{
    Gpt_HwChannelType HwChannel;
    volatile uint32 *ControlRegPtr;
    volatile uint32 *CounterRegPtr;

} Gpt_HwRegisterType;

Std_ReturnType Gpt_Hw_InitChannel(const Gpt_ChannelConfigType *ChannelPtr);

void Gpt_Hw_StartT3(Gpt_ValueType Value);
void Gpt_Hw_StopT3(void);
Gpt_ValueType Gpt_Hw_GetT3Value(void);

#endif
