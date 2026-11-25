#ifndef DIO_CFG_H
#define DIO_CFG_H

#include <Includes/Std_Types.h>

#define DIO_DEV_ERROR_DETECT       STD_ON
#define DIO_VERSION_INFO_API       STD_ON

#define DIO_MAX_CHANNELS           2U

typedef struct
{
    uint16 ChannelId;
    uint8 PortNumber;
    uint8 PinNumber;

} Dio_ChannelConfigType;

extern const Dio_ChannelConfigType Dio_ChannelConfig[DIO_MAX_CHANNELS];

#endif
