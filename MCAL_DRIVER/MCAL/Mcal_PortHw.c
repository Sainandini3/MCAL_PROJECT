
#include <MCAL/Mcal_PortHw.h>
#include <Libraries/iLLD/TC3xx/Tricore/Port/Std/IfxPort_reg.h>

volatile uint8 *Mcal_PortHw_GetBaseAddress(uint8 PortNumber)
{
    volatile uint8 *BaseAddress = NULL_PTR;

    switch (PortNumber)
    {
        case 0U:
            BaseAddress = (volatile uint8 *)&MODULE_P00;
            break;

        case 1U:
            BaseAddress = (volatile uint8 *)&MODULE_P01;
            break;

        case 2U:
            BaseAddress = (volatile uint8 *)&MODULE_P02;
            break;

        case 10U:
            BaseAddress = (volatile uint8 *)&MODULE_P10;
            break;

        case 11U:
            BaseAddress = (volatile uint8 *)&MODULE_P11;
            break;

        case 12U:
            BaseAddress = (volatile uint8 *)&MODULE_P12;
            break;

        case 13U:
            BaseAddress = (volatile uint8 *)&MODULE_P13;
            break;

        case 14U:
            BaseAddress = (volatile uint8 *)&MODULE_P14;
            break;

        case 15U:
            BaseAddress = (volatile uint8 *)&MODULE_P15;
            break;

        case 20U:
            BaseAddress = (volatile uint8 *)&MODULE_P20;
            break;

        case 21U:
            BaseAddress = (volatile uint8 *)&MODULE_P21;
            break;

        case 22U:
            BaseAddress = (volatile uint8 *)&MODULE_P22;
            break;

        case 23U:
            BaseAddress = (volatile uint8 *)&MODULE_P23;
            break;

        case 24U:
            BaseAddress = (volatile uint8 *)&MODULE_P24;
            break;

        case 25U:
            BaseAddress = (volatile uint8 *)&MODULE_P25;
            break;

        case 26U:
            BaseAddress = (volatile uint8 *)&MODULE_P26;
            break;

        case 30U:
            BaseAddress = (volatile uint8 *)&MODULE_P30;
            break;

        case 31U:
            BaseAddress = (volatile uint8 *)&MODULE_P31;
            break;

        case 32U:
            BaseAddress = (volatile uint8 *)&MODULE_P32;
            break;

        case 33U:
            BaseAddress = (volatile uint8 *)&MODULE_P33;
            break;

        case 34U:
            BaseAddress = (volatile uint8 *)&MODULE_P34;
            break;

        case 40U:
            BaseAddress = (volatile uint8 *)&MODULE_P40;
            break;

        case 41U:
            BaseAddress = (volatile uint8 *)&MODULE_P41;
            break;

        default:
            BaseAddress = NULL_PTR;
            break;
    }

    return BaseAddress;
}

uint32 Mcal_PortHw_ReadRegister(
    volatile uint8 *BaseAddress,
    uint32 Offset)
{
    uint32 RegisterValue = 0U;

    if (BaseAddress != NULL_PTR)
    {
        RegisterValue =
            (*(volatile uint32 *)(BaseAddress + Offset));
    }

    return RegisterValue;
}

boolean Mcal_PortHw_WriteRegister(
    volatile uint8 *BaseAddress,
    uint32 Offset,
    uint32 Value)
{
    if (BaseAddress == NULL_PTR)
    {
        return FALSE;
    }

    (*(volatile uint32 *)(BaseAddress + Offset)) = Value;

    return TRUE;
}


boolean Mcal_PortHw_WritePinLevel(
    uint8 PortNumber,
    uint8 PinNumber,
    boolean LevelHigh)
{
    volatile uint8 *BaseAddress;
    uint32 PinMask;
    uint32 OmrValue;

    if ((PinNumber > 15U) ||
        ((LevelHigh != TRUE) && (LevelHigh != FALSE)))
    {
        return FALSE;
    }

    BaseAddress = Mcal_PortHw_GetBaseAddress(PortNumber);

    if (BaseAddress == NULL_PTR)
    {
        return FALSE;
    }

    PinMask = ((uint32)1U << PinNumber);

    if (LevelHigh == TRUE)
    {
        OmrValue = PinMask;
    }
    else
    {
        OmrValue = (PinMask << 16U);
    }

    if (Mcal_PortHw_WriteRegister(
            BaseAddress,
            MCAL_PORTHW_OMR_OFFSET,
            OmrValue) == FALSE)
    {
        return FALSE;
    }

    return TRUE;

    return TRUE;
}
