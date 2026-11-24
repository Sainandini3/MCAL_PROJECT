
#ifndef PORT_H
#define PORT_H

#include <Includes/Std_Types.h>
#include <MCAL/Port/Port_Cfg.h>
#include <MCAL/Port/Port_Tc397Modes.h>

typedef uint16 Port_PinType;

typedef uint8 Port_PinModeType;

typedef enum
{
    PORT_PIN_IN  = 0U,
    PORT_PIN_OUT = 1U
} Port_PinDirectionType;

typedef enum
{
    PORT_PIN_LEVEL_LOW  = 0U,
    PORT_PIN_LEVEL_HIGH = 1U
} Port_PinLevelType;

#define PORT_PIN_MODE_GPIO  ((Port_PinModeType)0U)
#define PORT_PIN_MODE_ALT1  ((Port_PinModeType)1U)
#define PORT_PIN_MODE_ALT2  ((Port_PinModeType)2U)
#define PORT_PIN_MODE_ALT3  ((Port_PinModeType)3U)
#define PORT_PIN_MODE_ALT4  ((Port_PinModeType)4U)
#define PORT_PIN_MODE_ALT5  ((Port_PinModeType)5U)
#define PORT_PIN_MODE_ALT6  ((Port_PinModeType)6U)
#define PORT_PIN_MODE_ALT7  ((Port_PinModeType)7U)

typedef struct
{
    Port_PinModeType Mode;
    uint8 IocrPcValue;
} Port_PinModeMapType;

typedef struct
{
    Port_PinType PinId;
    uint8 PortNumber;
    uint8 PinNumber;
    Port_PinDirectionType PinDirection;
    Port_PinLevelType PinLevel;
    Port_PinModeType PinMode;
    boolean PinDirectionChangeable;
    boolean PinModeChangeable;
    Port_InputPullType InputPull;
    Port_OutputType OutputType;
    const Port_PinModeMapType *ModeMap;
    uint8 NumModeMapEntries;
} Port_PinConfigType;

typedef struct
{
    uint16 NumPins;
    const Port_PinConfigType *PinConfig;
} Port_ConfigType;

extern const Port_ConfigType Port_Config;

void Port_Init(const Port_ConfigType *ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
#endif

void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#endif
