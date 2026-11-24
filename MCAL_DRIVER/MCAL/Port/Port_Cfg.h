
#ifndef PORT_CFG_H
#define PORT_CFG_H

#include <Includes/Std_Types.h>


#define PORT_DEV_ERROR_DETECT          STD_ON



#define PORT_SET_PIN_DIRECTION_API    STD_ON

#define PORT_SET_PIN_MODE_API         STD_ON

#define PORT_VERSION_INFO_API         STD_ON


#define PORT_MAX_CONFIGURED_PINS      2U


#define PORT_VENDOR_ID                (17U)
#define PORT_MODULE_ID                (124U)
#define PORT_INSTANCE_ID              ((uint8)0x00U)


#define PORT_SW_MAJOR_VERSION        (1U)
#define PORT_SW_MINOR_VERSION        (0U)
#define PORT_SW_PATCH_VERSION        (0U)

#define PORT_PIN_ID_LED_PIN \
    ((Port_PinType)0U)
#define PORT_PIN_ID_INPUT_PIN \
    ((Port_PinType)1U)

#endif
