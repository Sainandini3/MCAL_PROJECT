#ifndef DIO_H
#define DIO_H

#include <Includes/Std_Types.h>

typedef uint16 Dio_ChannelType;
typedef uint8  Dio_PortType;
typedef uint16 Dio_LevelType;


typedef struct
{
    uint32 mask;
    uint8 offset;
    Dio_PortType port;
} Dio_ChannelGroupType;

#define DIO_INSTANCE_ID            0U
#define DIO_VENDOR_ID              (17U)
#define DIO_MODULE_ID              (120U)

#define DIO_SW_MAJOR_VERSION       (1U)
#define DIO_SW_MINOR_VERSION      (0U)
#define DIO_SW_PATCH_VERSION      (0U)


#define STD_LOW     ((Dio_LevelType)0U)
#define STD_HIGH    ((Dio_LevelType)1U)

#define Dio_PortLevelType uint32

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

void Dio_WriteChannel(
    Dio_ChannelType ChannelId,
    Dio_LevelType Level
);

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

void Dio_WritePort(
    Dio_PortType PortId,
    Dio_PortLevelType Level
);

Dio_PortLevelType Dio_ReadChannelGroup(
    const Dio_ChannelGroupType *ChannelGroupIdPtr
);

void Dio_WriteChannelGroup(
    const Dio_ChannelGroupType *ChannelGroupIdPtr,
    Dio_PortLevelType Level
);

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#endif
