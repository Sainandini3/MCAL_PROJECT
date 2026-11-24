
#include <MCAL/Port/Port.h>
#include <MCAL/Port/Port_Cfg.h>

static const Port_PinConfigType Port_PinConfig[] =
{
    {
        .PinId = 0U,
        .PortNumber = 13U,
        .PinNumber = 0U,
        .PinDirection = PORT_PIN_OUT,
        .PinLevel = PORT_PIN_LEVEL_LOW,
        .PinMode = PORT_PIN_MODE_GPIO,
        .PinDirectionChangeable = TRUE,
        .PinModeChangeable = FALSE,
        .InputPull = PORT_INPUT_PULL_NONE,
        .OutputType = PORT_OUTPUT_PUSH_PULL,
        .ModeMap = NULL_PTR,
        .NumModeMapEntries = 0U
    },
    {

        .PinId = 1U,
        .PortNumber = 2U,
        .PinNumber = 0U,
        .PinDirection = PORT_PIN_OUT,
        .PinLevel = PORT_PIN_LEVEL_LOW,
        .PinMode = PORT_PIN_MODE_ALT1,
        .PinDirectionChangeable = FALSE,
        .PinModeChangeable = TRUE,
        .InputPull = PORT_INPUT_PULL_NONE,
        .OutputType = PORT_OUTPUT_PUSH_PULL,
        .ModeMap = NULL_PTR,
        .NumModeMapEntries = 0U

    }
};

const Port_ConfigType Port_Config =
{
    .NumPins = (uint16)(sizeof(Port_PinConfig) /sizeof(Port_PinConfig[0])),
    .PinConfig = Port_PinConfig
};
