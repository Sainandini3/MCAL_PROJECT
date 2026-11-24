
#include <MCAL/Gpt/Gpt_Hw.h>
#include <MCAL/Gpt/IfxGpt12_reg.h>


static const Gpt_HwRegisterType Gpt_HwRegisterMap[] =
{
    {
        GPT_HW_GPT12_T2,
        (volatile uint32 *)&GPT120_T2CON,
        (volatile uint32 *)&GPT120_T2
    },
    {
        GPT_HW_GPT12_T3,
        (volatile uint32 *)&GPT120_T3CON,
        (volatile uint32 *)&GPT120_T3
    },
    {
        GPT_HW_GPT12_T4,
        (volatile uint32 *)&GPT120_T4CON,
        (volatile uint32 *)&GPT120_T4
    }
};

/* Initialize GPT hardware channel */
Std_ReturnType Gpt_Hw_InitChannel(
    const Gpt_ChannelConfigType *ChannelPtr)
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
        if (Gpt_HwRegisterMap[Index].HwChannel ==
            ChannelPtr->HwChannel)
        {


            return E_OK;
        }
    }

    return E_NOT_OK;
}
