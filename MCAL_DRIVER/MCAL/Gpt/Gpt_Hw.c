
#include <MCAL/Gpt/Gpt_Hw.h>
#include <MCAL/Gpt/IfxGpt12_reg.h>


static const Gpt_HwRegisterType Gpt_HwRegisterMap[] =
{
    {
        GPT_HW_GPT12_T2,
        (volatile uint32 *)&T2CON,
        (volatile uint32 *)&T2
    },
    {
        GPT_HW_GPT12_T3,
        (volatile uint32 *)&T3CON,
        (volatile uint32 *)&T3
    },
    {
        GPT_HW_GPT12_T4,
        (volatile uint32 *)&T4CON,
        (volatile uint32 *)&T4
    },

    {
        GPT_HW_GPT12_T5,
        (volatile uint32*)&T5CON,
        (volatile uint32*)&T5
    },
    {
        GPT_HW_GPT12_T6,
        (volatile uint32*)&T6CON,
        (volatile uint32*)&T6
    }
};


Std_ReturnType Gpt_Hw_InitChannel(const Gpt_ChannelConfigType *ChannelPtr)
{
    uint8 Index;
    uint8 RegisterCount;

    if (ChannelPtr == NULL_PTR)
    {
        return E_NOT_OK;
    }

    RegisterCount = (uint8)(sizeof(Gpt_HwRegisterMap) /sizeof(Gpt_HwRegisterMap[0]));

    for (Index = 0U; Index < RegisterCount; Index++)
    {
        if (Gpt_HwRegisterMap[Index].HwChannel ==ChannelPtr->HwChannel)
        {
            *Gpt_HwRegisterMap[Index].ControlRegPtr|= (0U<<6);  //stop the timer

            *Gpt_HwRegisterMap[Index].ControlRegPtr =   (*Gpt_HwRegisterMap[Index].ControlRegPtr & ~(((1U<<3)-1)<<3 )) |  ((0U)&(1U<<3)-1)<<3;

            *Gpt_HwRegisterMap[Index].ControlRegPtr|= (0U<<7);  //up counter

           // prescaler pending
            *Gpt_HwRegisterMap[Index].ControlRegPtr = (*Gpt_HwRegisterMap[Index].ControlRegPtr & ~(((1U<<2)-1)<<11 )) | ((2U)&(1U<<2)-1)<<11;

            *Gpt_HwRegisterMap[Index].CounterRegPtr=0u; //initialize the counter
            return E_OK;
        }
    }

    return E_NOT_OK;
}
