
#include <MCAL/Port/Port_Tc397Modes.h>

#define PORT_TC397_OUTPUT_O1       (0x01U)
#define PORT_TC397_OUTPUT_O2       (0x02U)
#define PORT_TC397_OUTPUT_O3       (0x04U)
#define PORT_TC397_OUTPUT_O4       (0x08U)
#define PORT_TC397_OUTPUT_O5       (0x10U)
#define PORT_TC397_OUTPUT_O6       (0x20U)
#define PORT_TC397_OUTPUT_O7       (0x40U)

#define PORT_TC397_P02_0_OUTPUTS   (0x7FU)
#define PORT_TC397_P13_0_OUTPUTS   (0x5FU)

typedef struct
{
    uint8 PortNumber;
    uint8 PinNumber;
    uint8 OutputMask;
} Port_Tc397PinCapabilityType;

static const Port_Tc397PinCapabilityType Port_Tc397PinDatabase[] =
{
    { 2U, 0U, PORT_TC397_P02_0_OUTPUTS },
    { 13U, 0U, PORT_TC397_P13_0_OUTPUTS }
};

boolean Port_Tc397IsPinSupported(
    uint8 PortNumber,
    uint8 PinNumber)
{
    uint32 Index;
    uint32 Count;

    Count = (uint32)(
        sizeof(Port_Tc397PinDatabase) /
        sizeof(Port_Tc397PinDatabase[0]));

    for (Index = 0U; Index < Count; Index++)
    {
        if ((Port_Tc397PinDatabase[Index].PortNumber == PortNumber) &&
            (Port_Tc397PinDatabase[Index].PinNumber == PinNumber))
        {
            return TRUE;
        }
    }

    return FALSE;
}

boolean Port_Tc397EncodeInput(
    Port_InputPullType InputPull,
    uint32 *HardwareMode)
{
    if (HardwareMode == NULL_PTR)
    {
        return FALSE;
    }

    switch (InputPull)
    {
        case PORT_INPUT_PULL_NONE:
            *HardwareMode = PORT_TC397_PC_INPUT_NO_PULL;
            return TRUE;

        case PORT_INPUT_PULL_DOWN:
            *HardwareMode = PORT_TC397_PC_INPUT_PULL_DOWN;
            return TRUE;

        case PORT_INPUT_PULL_UP:
            *HardwareMode = PORT_TC397_PC_INPUT_PULL_UP;
            return TRUE;

        default:
            return FALSE;
    }
}

boolean Port_Tc397EncodeOutput(
    uint8 PortNumber,
    uint8 PinNumber,
    uint8 OutputSelection,
    Port_OutputType OutputType,
    uint32 *HardwareMode)
{
    uint32 Index;
    uint32 Count;
    uint8 OutputMask;
    uint8 BaseValue;

    if ((HardwareMode == NULL_PTR) || (OutputSelection > 7U))
    {
        return FALSE;
    }

    if ((OutputType != PORT_OUTPUT_PUSH_PULL) &&
        (OutputType != PORT_OUTPUT_OPEN_DRAIN))
    {
        return FALSE;
    }

    Count = (uint32)(
        sizeof(Port_Tc397PinDatabase) /
        sizeof(Port_Tc397PinDatabase[0]));

    for (Index = 0U; Index < Count; Index++)
    {
        if ((Port_Tc397PinDatabase[Index].PortNumber == PortNumber) &&
            (Port_Tc397PinDatabase[Index].PinNumber == PinNumber))
        {
            break;
        }
    }

    if (Index >= Count)
    {
        return FALSE;
    }

    if (OutputSelection == 0U)
    {
        OutputMask = 0U;
    }
    else
    {
        OutputMask = (uint8)(1U << (OutputSelection - 1U));
    }

    if ((OutputSelection != 0U) &&
        ((Port_Tc397PinDatabase[Index].OutputMask & OutputMask) == 0U))
    {
        return FALSE;
    }

    if (OutputType == PORT_OUTPUT_PUSH_PULL)
    {
        BaseValue = PORT_TC397_PC_OUTPUT_PP_BASE;
    }
    else
    {
        BaseValue = PORT_TC397_PC_OUTPUT_OD_BASE;
    }

    *HardwareMode = (uint32)(BaseValue | OutputSelection);

    return TRUE;
}
