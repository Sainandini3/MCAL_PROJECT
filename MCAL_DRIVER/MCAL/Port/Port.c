
#include <Libraries/iLLD/TC3xx/Tricore/Port/Std/IfxPort_reg.h>
#include <MCAL/Port/Port.h>
#include <MCAL/Port/Port_Cfg.h>
#include <MCAL/Mcal_PortHw.h>
#include <Includes/Std_Types.h>

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include <MCAL/Det/Det.h>
#endif

#define PORT_INIT_ID                    (0x00U)
#define PORT_SET_PIN_DIRECTION_ID       (0x01U)
#define PORT_REFRESH_PORT_DIRECTION_ID  (0x02U)
#define PORT_GET_VERSION_INFO_ID        (0x03U)
#define PORT_SET_PIN_MODE_ID            (0x04U)

#define PORT_E_PARAM_PIN                (0x0AU)
#define PORT_E_DIRECTION_UNCHANGEABLE   (0x0BU)
#define PORT_E_INIT_FAILED              (0x0CU)
#define PORT_E_PARAM_INVALID_MODE       (0x0DU)
#define PORT_E_MODE_UNCHANGEABLE        (0x0EU)
#define PORT_E_UNINIT                   (0x0FU)
#define PORT_E_PARAM_POINTER            (0x10U)
#define PORT_E_PARAM_INVALID_DIRECTION  (0x11U)

#define PORT_IOCR0_OFFSET               (0x10U)
#define PORT_IOCR4_OFFSET               (0x14U)
#define PORT_IOCR8_OFFSET               (0x18U)
#define PORT_IOCR12_OFFSET              (0x1CU)

#define PORT_IOCR_SLOT_WIDTH            (8U)
#define PORT_IOCR_PC_MASK               (0x1FU)
#define PORT_IOCR_PC_BIT_OFFSET         (3U)

#define PORT_HW_MODE_GPIO_INPUT         (0x00U)
#define PORT_HW_MODE_GPIO_OUTPUT        (0x10U)

#define PORT_HW_MODE_ALT1               (0x11U)
#define PORT_HW_MODE_ALT2               (0x12U)
#define PORT_HW_MODE_ALT3               (0x13U)
#define PORT_HW_MODE_ALT4               (0x14U)
#define PORT_HW_MODE_ALT5               (0x15U)
#define PORT_HW_MODE_ALT6               (0x16U)
#define PORT_HW_MODE_ALT7               (0x17U)

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#define PORT_REPORT_ERROR(ApiId, ErrorId)                    \
    do                                                       \
    {                                                        \
        (void)Det_ReportError((uint16)PORT_MODULE_ID,        \
                              (uint8)PORT_INSTANCE_ID,       \
                              (uint8)(ApiId),                \
                              (uint8)(ErrorId));             \
    } while (0)

#else

#define PORT_REPORT_ERROR(ApiId, ErrorId)                    \
    do                                                       \
    {                                                        \
        (void)(ApiId);                                       \
        (void)(ErrorId);                                     \
    } while (0)

#endif

static boolean Port_InitStatus = FALSE;

static const Port_ConfigType *Port_ConfigPtr = NULL_PTR;

static Port_PinDirectionType
    Port_RuntimeDirection[PORT_MAX_CONFIGURED_PINS];

static Port_PinModeType
    Port_RuntimeMode[PORT_MAX_CONFIGURED_PINS];


static uint32 Port_lGetIocrOffset(uint8 PinNumber)
{
    if (PinNumber < 4U)
    {
        return PORT_IOCR0_OFFSET;
    }
    else if (PinNumber < 8U)
    {
        return PORT_IOCR4_OFFSET;
    }
    else if (PinNumber < 12U)
    {
        return PORT_IOCR8_OFFSET;
    }
    else
    {
        return PORT_IOCR12_OFFSET;
    }
}


static boolean Port_lIsIocrRegisterPresent(uint8 PortNumber, uint8 PinNumber)
{
    uint8 Group;

    Group = (uint8)(PinNumber / 4U);

    switch (PortNumber)
    {
        case 0U:
        case 1U:
        case 2U:
        case 10U:
        case 11U:
        case 13U:
        case 14U:
        case 15U:
        case 20U:
        case 24U:
        case 25U:
        case 30U:
        case 31U:
        case 33U:
        case 40U:
            return (boolean)(PinNumber <= 15U);

        case 12U:
        case 26U:
            return (boolean)(Group == 0U);

        case 21U:
        case 23U:
        case 32U:
        case 34U:
            return (boolean)(Group <= 1U);

        case 22U:
        case 41U:
            return (boolean)(Group <= 2U);

        default:
            return FALSE;
    }
}



static boolean Port_lResolveHardwareMode(const Port_PinConfigType *PinConfigPtr,Port_PinModeType Mode,Port_PinDirectionType Direction,uint32 *HardwareMode)
{
    uint8 OutputSelection;

    if ((PinConfigPtr == NULL_PTR) ||
        (HardwareMode == NULL_PTR))
    {
        return FALSE;
    }

    if (Port_Tc397IsPinSupported(
            PinConfigPtr->PortNumber,
            PinConfigPtr->PinNumber) == FALSE)
    {
        return FALSE;
    }

    if (Mode == PORT_PIN_MODE_GPIO)
    {
        if (Direction == PORT_PIN_IN)
        {
            return Port_Tc397EncodeInput( PinConfigPtr->InputPull,HardwareMode);
        }

        if (Direction == PORT_PIN_OUT)
        {
            return Port_Tc397EncodeOutput(
                PinConfigPtr->PortNumber,
                PinConfigPtr->PinNumber,
                0U,
                PinConfigPtr->OutputType,
                HardwareMode);
        }

        return FALSE;
    }

    if ((Mode < PORT_PIN_MODE_ALT1) ||
        (Mode > PORT_PIN_MODE_ALT7))
    {
        return FALSE;
    }

    if (Direction != PORT_PIN_OUT)
    {
        return FALSE;
    }

    OutputSelection =
        (uint8)(Mode - PORT_PIN_MODE_ALT1 + 1U);

    return Port_Tc397EncodeOutput(
        PinConfigPtr->PortNumber,
        PinConfigPtr->PinNumber,
        OutputSelection,
        PinConfigPtr->OutputType,
        HardwareMode);
}

static const Port_PinConfigType *Port_lFindPinConfig(
    Port_PinType Pin,
    uint32 *ConfigIndex)
{
    uint32 Index;

    if ((Port_ConfigPtr == NULL_PTR) ||
        (ConfigIndex == NULL_PTR))
    {
        return NULL_PTR;
    }

    for (Index = 0U;
         Index < (uint32)Port_ConfigPtr->NumPins;
         Index++)
    {
        if (Port_ConfigPtr->PinConfig[Index].PinId == Pin)
        {
            *ConfigIndex = Index;
            return &Port_ConfigPtr->PinConfig[Index];
        }
    }

    return NULL_PTR;
}


static void Port_lSetPinLevelHw(
    const Port_PinConfigType *PinConfigPtr,
    Port_PinLevelType Level)
{
    boolean LevelHigh;

    if (PinConfigPtr == NULL_PTR)
    {
        return;
    }

    if (Level == PORT_PIN_LEVEL_HIGH)
    {
        LevelHigh = TRUE;
    }
    else if (Level == PORT_PIN_LEVEL_LOW)
    {
        LevelHigh = FALSE;
    }
    else
    {
        return;
    }

    (void)Mcal_PortHw_WritePinLevel(
        PinConfigPtr->PortNumber,
        PinConfigPtr->PinNumber,
        LevelHigh);
}


static boolean Port_lSetPinModeHw(
    const Port_PinConfigType *PinConfigPtr,
    uint32 HardwareMode)
{
    volatile uint8 *Base;
    uint32 IocrOffset;
    uint32 Shift;
    uint32 Mask;
    uint32 RegisterValue;

    if (PinConfigPtr == NULL_PTR)
    {
        return FALSE;
    }

    if (PinConfigPtr->PinNumber > 15U)
    {
        return FALSE;
    }

    Base = Mcal_PortHw_GetBaseAddress(
        PinConfigPtr->PortNumber);

    if (Base == NULL_PTR)
    {
        return FALSE;
    }

    if (Port_lIsIocrRegisterPresent(
            PinConfigPtr->PortNumber,
            PinConfigPtr->PinNumber) == FALSE)
    {
        return FALSE;
    }

    IocrOffset = Port_lGetIocrOffset(
        PinConfigPtr->PinNumber);

    Shift =
        (((uint32)PinConfigPtr->PinNumber % 4U) *
         PORT_IOCR_SLOT_WIDTH) +
        PORT_IOCR_PC_BIT_OFFSET;

    Mask = ((uint32)PORT_IOCR_PC_MASK << Shift);

    RegisterValue = Mcal_PortHw_ReadRegister(
        Base,
        IocrOffset);

    RegisterValue &= ~Mask;

    RegisterValue |=
        ((HardwareMode & (uint32)PORT_IOCR_PC_MASK) << Shift);

    Mcal_PortHw_WriteRegister(
        Base,
        IocrOffset,
        RegisterValue);

    return TRUE;
}


static void Port_lSetPinDirectionHw(
    const Port_PinConfigType *PinConfigPtr,
    Port_PinDirectionType Direction)
{
    uint32 HardwareMode;

    if (Port_lResolveHardwareMode(
            PinConfigPtr,
            PORT_PIN_MODE_GPIO,
            Direction,
            &HardwareMode) == TRUE)
    {
        (void)Port_lSetPinModeHw(
            PinConfigPtr,
            HardwareMode);
    }
}


static boolean Port_lValidateModeMap(
    const Port_PinConfigType *PinCfg)
{
    uint8 Index;
    uint8 OtherIndex;
    uint8 Mode;
    uint8 PcValue;

    if (PinCfg == NULL_PTR)
    {
        return FALSE;
    }

    if (((PinCfg->NumModeMapEntries > 0U) &&
         (PinCfg->ModeMap == NULL_PTR)) ||
        ((PinCfg->NumModeMapEntries == 0U) &&
         (PinCfg->ModeMap != NULL_PTR)))
    {
        return FALSE;
    }

    for (Index = 0U;
         Index < PinCfg->NumModeMapEntries;
         Index++)
    {
        Mode = PinCfg->ModeMap[Index].Mode;
        PcValue = PinCfg->ModeMap[Index].IocrPcValue;

        if ((Mode < PORT_PIN_MODE_ALT1) ||
            (Mode > PORT_PIN_MODE_ALT7))
        {
            return FALSE;
        }

        if ((PcValue < PORT_HW_MODE_ALT1) ||
            (PcValue > PORT_HW_MODE_ALT7))
        {
            return FALSE;
        }

        if (PcValue != (uint8)(0x10U | Mode))
        {
            return FALSE;
        }

        for (OtherIndex = 0U;
             OtherIndex < Index;
             OtherIndex++)
        {
            if (PinCfg->ModeMap[OtherIndex].Mode == Mode)
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}


static boolean Port_lValidateConfig(
    const Port_ConfigType *ConfigPtr)
{
    uint32 Index;
    uint32 OtherIndex;
    uint32 HardwareMode;

    const Port_PinConfigType *PinCfg;
    const Port_PinConfigType *Previous;

    if ((ConfigPtr == NULL_PTR) ||(ConfigPtr->NumPins == 0U) ||(ConfigPtr->NumPins > PORT_MAX_CONFIGURED_PINS) ||
        (ConfigPtr->PinConfig == NULL_PTR))
    {
        return FALSE;
    }

    for (Index = 0U; Index < (uint32)ConfigPtr->NumPins;Index++)
    {
        PinCfg = &ConfigPtr->PinConfig[Index];

        if ((Mcal_PortHw_GetBaseAddress(PinCfg->PortNumber) == NULL_PTR) ||(PinCfg->PinNumber > 15U) ||
            (Port_lIsIocrRegisterPresent( PinCfg->PortNumber,PinCfg->PinNumber) == FALSE))
        {
            return FALSE;
        }

        if ((PinCfg->PinLevel != PORT_PIN_LEVEL_LOW) && (PinCfg->PinLevel != PORT_PIN_LEVEL_HIGH))
        {
            return FALSE;
        }

        if ((PinCfg->PinDirection != PORT_PIN_IN) && (PinCfg->PinDirection != PORT_PIN_OUT))
        {
            return FALSE;
        }

        if ((PinCfg->PinDirectionChangeable != FALSE) &&(PinCfg->PinDirectionChangeable != TRUE))
        {
            return FALSE;
        }

        if ((PinCfg->PinModeChangeable != FALSE) && (PinCfg->PinModeChangeable != TRUE))
        {
            return FALSE;
        }

        if (Port_lValidateModeMap(PinCfg) == FALSE)
        {
            return FALSE;
        }

        if (Port_lResolveHardwareMode(PinCfg,PinCfg->PinMode,PinCfg->PinDirection,&HardwareMode) == FALSE)
        {
            return FALSE;
        }

        for (OtherIndex = 0U;OtherIndex < Index;OtherIndex++)
        {
            Previous = &ConfigPtr->PinConfig[OtherIndex];

            if ((Previous->PinId == PinCfg->PinId) || ((Previous->PortNumber == PinCfg->PortNumber) &&(Previous->PinNumber == PinCfg->PinNumber)))
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}


void Port_Init(const Port_ConfigType *ConfigPtr)
{
    const Port_ConfigType *SelectedConfig;
    const Port_PinConfigType *PinCfg;

    uint32 Index;
    uint32 HardwareMode;

    Port_InitStatus = FALSE;
    Port_ConfigPtr = NULL_PTR;

    SelectedConfig =(ConfigPtr == NULL_PTR) ? &Port_Config : ConfigPtr;

    if (Port_lValidateConfig(SelectedConfig) == FALSE)
    {
        PORT_REPORT_ERROR(PORT_INIT_ID,PORT_E_INIT_FAILED);
        return;
    }

    Port_ConfigPtr = SelectedConfig;

    for (Index = 0U; Index < (uint32)Port_ConfigPtr->NumPins;Index++)
    {
        PinCfg = &Port_ConfigPtr->PinConfig[Index];

        if (Port_lResolveHardwareMode(PinCfg,PinCfg->PinMode,PinCfg->PinDirection,&HardwareMode) == FALSE)
        {
            Port_ConfigPtr = NULL_PTR;

            PORT_REPORT_ERROR(PORT_INIT_ID, PORT_E_INIT_FAILED);
            return;
        }

        if (PinCfg->PinDirection == PORT_PIN_OUT)
        {
            Port_lSetPinLevelHw(PinCfg,PinCfg->PinLevel);
        }

        if (Port_lSetPinModeHw(PinCfg,HardwareMode) == FALSE)
        {
            Port_ConfigPtr = NULL_PTR;

            PORT_REPORT_ERROR(PORT_INIT_ID,PORT_E_INIT_FAILED);
            return;
        }

        Port_RuntimeDirection[Index] = PinCfg->PinDirection;
        Port_RuntimeMode[Index] = PinCfg->PinMode;
    }

    Port_InitStatus = TRUE;
}


void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)

    const Port_PinConfigType *PinCfg;
    uint32 ConfigIndex;
    uint32 HardwareMode;

    if (Port_InitStatus != TRUE)
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_DIRECTION_ID, PORT_E_UNINIT);
        return;
    }

    PinCfg = Port_lFindPinConfig(Pin, &ConfigIndex);

    if (PinCfg == NULL_PTR)
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_DIRECTION_ID,PORT_E_PARAM_PIN);
        return;
    }

    if (PinCfg->PinDirectionChangeable != TRUE)
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_DIRECTION_ID,PORT_E_DIRECTION_UNCHANGEABLE);
        return;
    }

    if ((Direction != PORT_PIN_IN) &&
        (Direction != PORT_PIN_OUT))
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_DIRECTION_ID,PORT_E_PARAM_INVALID_DIRECTION);
        return;
    }

    if (Port_RuntimeMode[ConfigIndex] != PORT_PIN_MODE_GPIO)
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_DIRECTION_ID,PORT_E_PARAM_INVALID_MODE);
        return;
    }

    if (Port_lResolveHardwareMode(PinCfg,PORT_PIN_MODE_GPIO,Direction,&HardwareMode) == FALSE)
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_DIRECTION_ID,PORT_E_PARAM_INVALID_DIRECTION);
        return;
    }

    if (Direction == PORT_PIN_OUT)
    {
        Port_lSetPinLevelHw(PinCfg,PinCfg->PinLevel);
    }

    if (Port_lSetPinModeHw(PinCfg,HardwareMode) == FALSE)
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_DIRECTION_ID,PORT_E_PARAM_INVALID_DIRECTION);
        return;
    }

    Port_RuntimeDirection[ConfigIndex] = Direction;

#else

    (void)Pin;
    (void)Direction;

#endif
}


void Port_RefreshPortDirection(void)
{
    uint32 Index;
    const Port_PinConfigType *PinCfg;

    if (Port_InitStatus != TRUE)
    {
        PORT_REPORT_ERROR(
            PORT_REFRESH_PORT_DIRECTION_ID,
            PORT_E_UNINIT);
        return;
    }

    for (Index = 0U;
         Index < (uint32)Port_ConfigPtr->NumPins;
         Index++)
    {
        PinCfg = &Port_ConfigPtr->PinConfig[Index];

        if ((PinCfg->PinDirectionChangeable == FALSE) &&
            (Port_RuntimeMode[Index] == PORT_PIN_MODE_GPIO))
        {
            Port_lSetPinDirectionHw(
                PinCfg,
                PinCfg->PinDirection);

            Port_RuntimeDirection[Index] =
                PinCfg->PinDirection;
        }
    }
}


void Port_GetVersionInfo(
    Std_VersionInfoType *versioninfo)
{
#if (PORT_VERSION_INFO_API == STD_ON)

    if (versioninfo == NULL_PTR)
    {
        PORT_REPORT_ERROR(
            PORT_GET_VERSION_INFO_ID,
            PORT_E_PARAM_POINTER);
        return;
    }

    versioninfo->vendorID =
        (uint16)PORT_VENDOR_ID;

    versioninfo->moduleID =
        (uint16)PORT_MODULE_ID;

    versioninfo->sw_major_version =
        (uint8)PORT_SW_MAJOR_VERSION;

    versioninfo->sw_minor_version =
        (uint8)PORT_SW_MINOR_VERSION;

    versioninfo->sw_patch_version =
        (uint8)PORT_SW_PATCH_VERSION;

#else

    (void)versioninfo;

#endif
}


void Port_SetPinMode(
    Port_PinType Pin,
    Port_PinModeType Mode)
{
#if (PORT_SET_PIN_MODE_API == STD_ON)

    const Port_PinConfigType *PinCfg;
    uint32 ConfigIndex;
    uint32 HardwareMode;

    if (Port_InitStatus != TRUE)
    {
        PORT_REPORT_ERROR(
            PORT_SET_PIN_MODE_ID,
            PORT_E_UNINIT);
        return;
    }

    PinCfg = Port_lFindPinConfig(Pin, &ConfigIndex);

    if (PinCfg == NULL_PTR)
    {
        PORT_REPORT_ERROR(
            PORT_SET_PIN_MODE_ID,
            PORT_E_PARAM_PIN);
        return;
    }

    if (PinCfg->PinModeChangeable != TRUE)
    {
        PORT_REPORT_ERROR(
            PORT_SET_PIN_MODE_ID,
            PORT_E_MODE_UNCHANGEABLE);
        return;
    }

    if (Port_lResolveHardwareMode(
            PinCfg,
            Mode,
            Port_RuntimeDirection[ConfigIndex],
            &HardwareMode) == FALSE)
    {
        PORT_REPORT_ERROR(
            PORT_SET_PIN_MODE_ID,
            PORT_E_PARAM_INVALID_MODE);
        return;
    }

    if (Port_lSetPinModeHw(PinCfg,HardwareMode) == FALSE)
    {
        PORT_REPORT_ERROR(PORT_SET_PIN_MODE_ID,PORT_E_PARAM_INVALID_MODE);
        return;
    }

    Port_RuntimeMode[ConfigIndex] = Mode;

#else

    (void)Pin;
    (void)Mode;

#endif
}
