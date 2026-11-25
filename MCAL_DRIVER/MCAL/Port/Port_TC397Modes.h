
#ifndef PORT_TC397MODES_H
#define PORT_TC397MODES_H

#include <Includes/Std_Types.h>

typedef enum
{
    PORT_INPUT_PULL_NONE = 0U,
    PORT_INPUT_PULL_DOWN,
    PORT_INPUT_PULL_UP
} Port_InputPullType;

typedef enum
{
    PORT_OUTPUT_PUSH_PULL = 0U,
    PORT_OUTPUT_OPEN_DRAIN
} Port_OutputType;

#define PORT_TC397_PC_INPUT_NO_PULL       (0x00U)
#define PORT_TC397_PC_INPUT_PULL_DOWN     (0x01U)
#define PORT_TC397_PC_INPUT_PULL_UP       (0x02U)

#define PORT_TC397_PC_GPIO_PUSH_PULL      (0x10U)
#define PORT_TC397_PC_GPIO_OPEN_DRAIN     (0x18U)

#define PORT_TC397_PC_OUTPUT_PP_BASE      (0x10U)
#define PORT_TC397_PC_OUTPUT_OD_BASE      (0x18U)

#define PORT_TC397_PC_MASK                (0x1FU)

boolean Port_Tc397EncodeInput( Port_InputPullType InputPull, uint32 *HardwareMode);

boolean Port_Tc397EncodeOutput( uint8 PortNumber,uint8 PinNumber,uint8 OutputSelection,Port_OutputType OutputType, uint32 *HardwareMode);

boolean Port_Tc397IsPinSupported( uint8 PortNumber,uint8 PinNumber);

#endif
