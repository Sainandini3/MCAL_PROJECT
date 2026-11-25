#include <MCAL/Dio/Dio.h>
#include <MCAL/Dio/Dio_Cfg.h>

const Dio_ChannelConfigType
Dio_ChannelConfig[DIO_MAX_CHANNELS] =
{
    {
        .ChannelId  = (uint16)0U,
        .PortNumber = (uint8)13U,
        .PinNumber  = (uint8)0U
    },    {
        .ChannelId  = (uint16)1U,
        .PortNumber = (uint8)2U,
        .PinNumber  = (uint8)0U
    }
};
