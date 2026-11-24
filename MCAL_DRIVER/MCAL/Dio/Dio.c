#include <MCAL/Dio/Dio.h>
#include <MCAL/Dio/Dio_Cfg.h>
#include <MCAL/Mcal_PortHw.h>
#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include <MCAL/Det/Det.h>
#endif
#define DIO_READ_CHANNEL_ID          0x00U
#define DIO_WRITE_CHANNEL_ID         0x01U
#define DIO_READ_PORT_ID             0x02U
#define DIO_WRITE_PORT_ID            0x03U
#define DIO_READ_GROUP_ID            0x04U
#define DIO_WRITE_GROUP_ID           0x05U
#define DIO_FLIP_CHANNEL_ID          0x06U
#define DIO_GET_VERSION_INFO_ID      0x07U
#define DIO_E_PARAM_INVALID_CHANNEL  0x0AU
#define DIO_E_PARAM_INVALID_PORT     0x0BU
#define DIO_E_PARAM_POINTER          0x0CU
#define DIO_E_PARAM_INVALID_GROUP    0x10U
#define DIO_PIN_MASK                 0x0000FFFFU

#if (DIO_DEV_ERROR_DETECT == STD_ON)
#define DIO_REPORT_ERROR(ApiId, ErrorId)                         \
    do                                                           \
    {                                                            \
        (void)Det_ReportError((uint16)DIO_MODULE_ID,             \
                              (uint8)DIO_INSTANCE_ID,            \
                              (uint8)(ApiId),                     \
                              (uint8)(ErrorId));                  \
    } while (0)
#else
#define DIO_REPORT_ERROR(ApiId, ErrorId) \
    do { (void)(ApiId); (void)(ErrorId); } while (0)
#endif
static const Dio_ChannelConfigType *Dio_lFindChannel(
    Dio_ChannelType ChannelId)
{
    uint32 Index;
    const Dio_ChannelConfigType *ChannelConfigPtr = NULL_PTR;
    for (Index = 0U; Index < DIO_MAX_CHANNELS; Index++)
    {
        if (Dio_ChannelConfig[Index].ChannelId == ChannelId)
        {
            ChannelConfigPtr = &Dio_ChannelConfig[Index];
            break;
        }
    }
    return ChannelConfigPtr;
}
static boolean Dio_lValidateChannel(
    const Dio_ChannelConfigType *ChannelConfigPtr)
{
    if (ChannelConfigPtr == NULL_PTR)
    {
        return FALSE;
    }
    if (ChannelConfigPtr->PinNumber > 15U)
    {
        return FALSE;
    }
    if (Mcal_PortHw_GetBaseAddress(ChannelConfigPtr->PortNumber) == NULL_PTR)
    {
        return FALSE;
    }
    return TRUE;
}
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    const Dio_ChannelConfigType *ChannelConfigPtr;
    volatile uint8 *BaseAddress;
    uint32 RegisterValue;
    uint32 PinMask;
    Dio_LevelType Level = STD_LOW;
    ChannelConfigPtr = Dio_lFindChannel(ChannelId);
    if (Dio_lValidateChannel(ChannelConfigPtr) == FALSE)
    {
        DIO_REPORT_ERROR(DIO_READ_CHANNEL_ID,
                        DIO_E_PARAM_INVALID_CHANNEL);
        return STD_LOW;
    }
    BaseAddress = Mcal_PortHw_GetBaseAddress(
        ChannelConfigPtr->PortNumber);
    PinMask = (1UL << ChannelConfigPtr->PinNumber);
    RegisterValue = Mcal_PortHw_ReadRegister(BaseAddress, MCAL_PORTHW_IN_OFFSET);
    if ((RegisterValue & PinMask) != 0U)
    {
        Level = STD_HIGH;
    }
    return Level;
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    const Dio_ChannelConfigType *ChannelConfigPtr;
    boolean LevelHigh;
    ChannelConfigPtr = Dio_lFindChannel(ChannelId);
    if (Dio_lValidateChannel(ChannelConfigPtr) == FALSE)
    {
        DIO_REPORT_ERROR(DIO_WRITE_CHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL);
        return;
    }
    if ((Level != STD_LOW) && (Level != STD_HIGH))
    {
        DIO_REPORT_ERROR(DIO_WRITE_CHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL);
        return;
    }
    LevelHigh = (Level == STD_HIGH) ? TRUE : FALSE;
    (void)Mcal_PortHw_WritePinLevel(ChannelConfigPtr->PortNumber,
                                    ChannelConfigPtr->PinNumber,
                                    LevelHigh);
}
uint32 Dio_ReadPort(Dio_PortType PortId)
{
    volatile uint8 *BaseAddress;
    uint32 RegisterValue = 0U;
    BaseAddress = Mcal_PortHw_GetBaseAddress(PortId);
    if (BaseAddress == NULL_PTR)
    {
        DIO_REPORT_ERROR(DIO_READ_PORT_ID,
                        DIO_E_PARAM_INVALID_PORT);
        return 0U;
    }
    RegisterValue = Mcal_PortHw_ReadRegister(BaseAddress, MCAL_PORTHW_IN_OFFSET);
    return (RegisterValue & DIO_PIN_MASK);
}
void Dio_WritePort(
    Dio_PortType PortId,
    uint32 Level)
{
    volatile uint8 *BaseAddress;
    uint32 SetMask;
    uint32 ClearMask;
    uint32 OmrValue;
    BaseAddress = Mcal_PortHw_GetBaseAddress(PortId);
    if (BaseAddress == NULL_PTR)
    {
        DIO_REPORT_ERROR(DIO_WRITE_PORT_ID,
                        DIO_E_PARAM_INVALID_PORT);
        return;
    }
    if ((Level & ~DIO_PIN_MASK) != 0U)
    {
        DIO_REPORT_ERROR(DIO_WRITE_PORT_ID,
                        DIO_E_PARAM_INVALID_PORT);
        return;
    }
    SetMask = Level & DIO_PIN_MASK;
    ClearMask = (~Level) & DIO_PIN_MASK;
    OmrValue = SetMask | (ClearMask << 16U);
    Mcal_PortHw_WriteRegister(BaseAddress, MCAL_PORTHW_OMR_OFFSET, OmrValue);
}
uint32 Dio_ReadChannelGroup(
    const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
    volatile uint8 *BaseAddress;
    uint32 RegisterValue;
    uint32 Result = 0U;
    if (ChannelGroupIdPtr == NULL_PTR)
    {
        DIO_REPORT_ERROR(DIO_READ_GROUP_ID,
                        DIO_E_PARAM_POINTER);
        return 0U;
    }
    if ((ChannelGroupIdPtr->offset > 15U) ||
        (ChannelGroupIdPtr->mask == 0U) ||
        ((ChannelGroupIdPtr->mask & ~DIO_PIN_MASK) != 0U) ||
        ((ChannelGroupIdPtr->mask & 0xFFFFFFFFUL) == 0U))
    {
        DIO_REPORT_ERROR(DIO_READ_GROUP_ID,
                        DIO_E_PARAM_INVALID_GROUP);
        return 0U;
    }
    BaseAddress = Mcal_PortHw_GetBaseAddress(
        ChannelGroupIdPtr->port);
    if (BaseAddress == NULL_PTR)
    {
        DIO_REPORT_ERROR(DIO_READ_GROUP_ID,
                        DIO_E_PARAM_INVALID_PORT);
        return 0U;
    }
    RegisterValue = Mcal_PortHw_ReadRegister(BaseAddress, MCAL_PORTHW_IN_OFFSET);
    Result = (RegisterValue & ChannelGroupIdPtr->mask)
             >> ChannelGroupIdPtr->offset;
    return Result;
}
void Dio_WriteChannelGroup(
    const Dio_ChannelGroupType *ChannelGroupIdPtr,
    uint32 Level)
{
    volatile uint8 *BaseAddress;
    uint32 SetMask;
    uint32 ClearMask;
    uint32 OmrValue;
    if (ChannelGroupIdPtr == NULL_PTR)
    {
        DIO_REPORT_ERROR(DIO_WRITE_GROUP_ID,
                        DIO_E_PARAM_POINTER);
        return;
    }
    if ((ChannelGroupIdPtr->offset > 15U) ||
        (ChannelGroupIdPtr->mask == 0U) ||
        ((ChannelGroupIdPtr->mask & ~DIO_PIN_MASK) != 0U))
    {
        DIO_REPORT_ERROR(DIO_WRITE_GROUP_ID,
                        DIO_E_PARAM_INVALID_GROUP);
        return;
    }
    BaseAddress = Mcal_PortHw_GetBaseAddress(
        ChannelGroupIdPtr->port);
    if (BaseAddress == NULL_PTR)
    {
        DIO_REPORT_ERROR(DIO_WRITE_GROUP_ID,
                        DIO_E_PARAM_INVALID_PORT);
        return;
    }
    if ((Level & ~(ChannelGroupIdPtr->mask >>
                   ChannelGroupIdPtr->offset)) != 0U)
    {
        DIO_REPORT_ERROR(DIO_WRITE_GROUP_ID,
                        DIO_E_PARAM_INVALID_GROUP);
        return;
    }
    SetMask = (Level << ChannelGroupIdPtr->offset) &
              ChannelGroupIdPtr->mask;
    ClearMask = ChannelGroupIdPtr->mask & (~SetMask);
    OmrValue = SetMask | (ClearMask << 16U);
    Mcal_PortHw_WriteRegister(BaseAddress, MCAL_PORTHW_OMR_OFFSET, OmrValue);
}
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    const Dio_ChannelConfigType *ChannelConfigPtr;
    volatile uint8 *BaseAddress;
    uint32 PinMask;
    uint32 OutputValue;
    Dio_LevelType Level = STD_LOW;
    ChannelConfigPtr = Dio_lFindChannel(ChannelId);
    if (Dio_lValidateChannel(ChannelConfigPtr) == FALSE)
    {
        DIO_REPORT_ERROR(DIO_FLIP_CHANNEL_ID,
                        DIO_E_PARAM_INVALID_CHANNEL);
        return STD_LOW;
    }
    BaseAddress = Mcal_PortHw_GetBaseAddress(
        ChannelConfigPtr->PortNumber);
    PinMask = (1UL << ChannelConfigPtr->PinNumber);
    OutputValue = Mcal_PortHw_ReadRegister(BaseAddress, MCAL_PORTHW_OUT_OFFSET);
    if ((OutputValue & PinMask) != 0U)
    {
        Mcal_PortHw_WriteRegister(BaseAddress, MCAL_PORTHW_OMR_OFFSET,
                                  (PinMask << 16U));
        Level = STD_LOW;
    }
    else
    {
        Mcal_PortHw_WriteRegister(BaseAddress, MCAL_PORTHW_OMR_OFFSET, PinMask);
        Level = STD_HIGH;
    }
    return Level;
}
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
    if (versioninfo == NULL_PTR)
    {
        DIO_REPORT_ERROR(DIO_GET_VERSION_INFO_ID,
                         DIO_E_PARAM_POINTER);
        return;
    }
    versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
    versioninfo->moduleID = (uint16)DIO_MODULE_ID;
    versioninfo->sw_major_version =
        (uint8)DIO_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version =
        (uint8)DIO_SW_MINOR_VERSION;
    versioninfo->sw_patch_version =
        (uint8)DIO_SW_PATCH_VERSION;
}
#endif
