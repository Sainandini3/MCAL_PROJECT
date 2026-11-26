#include <MCAL/Gpt/Gpt.h>
#include <MCAL/Gpt/Gpt_Cfg.h>

static const Gpt_ChannelConfigType Gpt_ChannelConfig[] =
{
    {
        .GptChannelId = GPT_CHANNEL_0,
        .HwChannel = GPT_HW_GPT12_T3,
        .GptChannelMode = GPT_CH_MODE_CONTINUOUS,
        .TickValueMax = 65535U,
        .TickFrequency = 1000000U,
        .InputSelection = GPT_T3_INPUT_NONE,
        .OutputSelection = GPT_T3_OUTPUT_NONE,
        .EnableWakeup = FALSE,
        .GptNotification = NULL_PTR,
        .NotificationEnabled = FALSE
    }
};

const Gpt_ConfigType Gpt_Config =
{
    .ChannelConfigPtr = Gpt_ChannelConfig,
    .NumberOfChannels = (uint8)(sizeof(Gpt_ChannelConfig)/sizeof(Gpt_ChannelConfig[0]))
};
