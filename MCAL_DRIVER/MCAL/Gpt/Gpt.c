#include<MCAL/Gpt/Gpt.h>
#include<MCAL/Gpt/Gpt_Cfg.h>
#include<MCAL/Gpt/IfxGpt12_reg.h>

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#define GPT_REPORT_ERROR(ApiId, ErrorId) do { (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)(ApiId), (uint8)(ErrorId)); } while (0)
#else
#define GPT_REPORT_ERROR(ApiId, ErrorId) do { (void)(ApiId); (void)(ErrorId); } while (0)
#endif

static boolean Validate_Config(const Gpt_ConfigType* SelectedConfig);

static boolean Enable_Module(void)
{
   CLC&=~(1U<<0U);
   if((CLC&(1U<<1U) )== 0U)
       return TRUE;
  return FALSE;
}

static boolean Gpt_Init_Status =FALSE;

static boolean Validate_Config(const Gpt_ConfigType* SelectedConfig)
{

    const Gpt_ChannelConfigType *Channel_cfg=NULL_PTR;


        if(SelectedConfig == NULL_PTR || SelectedConfig->NumberOfChannels < 1 || SelectedConfig->NumberOfChannels > GPT_MAX_CHANNELS ||  SelectedConfig -> ChannelConfigPtr == NULL_PTR )
        {
                return FALSE;
        }

        switch(Channel_cfg->HwChannel)
        {
            case GPT_HW_GPT12_T2:

            case GPT_HW_GPT12_T3:

            case GPT_HW_GPT12_T4:
            case GPT_HW_GPT12_T5:
            case GPT_HW_GPT12_T6:  break;

            default: return FALSE;
        }
        for(uint32 index=0;index< SelectedConfig->NumberOfChannels;index++)
        {
            Channel_cfg = &SelectedConfig->ChannelConfigPtr[index];

            if(Channel_cfg->TickValueMax < 0  || Channel_cfg->TickValueMax > 65535 )
            {
               return FALSE;
            }
            if(Channel_cfg->GptChannelMode!= GPT_CH_MODE_CONTINUOUS && Channel_cfg->GptChannelMode!=   GPT_CH_MODE_ONESHOT)
            {
                return FALSE;
            }


            if(Channel_cfg->InputSelection != GPT_T3_INPUT_NONE && Channel_cfg->InputSelection!= GPT_T3_INPUT_A  && Channel_cfg->InputSelection!= GPT_T3_INPUT_B)
            {
                return FALSE;
            }
        }

    return TRUE;
}

void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
    const Gpt_ConfigType *SelectedConfig;
    const Gpt_ChannelConfigType *Channel_cfg;

    SelectedConfig =(ConfigPtr == NULL_PTR) ? &Gpt_Config : ConfigPtr;

    if(Validate_Config(SelectedConfig)==FALSE)
    {
       GPT_REPORT_ERROR(GPT_INIT_ID, GPT_E_INIT_FAILED);
        return;
    }
    if(Enable_Module()==FALSE)
    {
        GPT_REPORT_ERROR(GPT_INIT_ID, GPT_E_INIT_FAILED);
        return;
    }

    for(uint32 index=0;index< SelectedConfig->NumberOfChannels;index++)
     {
        Channel_cfg = &SelectedConfig->ChannelConfigPtr[index];
        if(Gpt_Hw_InitChannel(&Channel_cfg) != E_OK)
         {
             GPT_REPORT_ERROR(GPT_INIT_ID, GPT_E_INIT_FAILED);
             return;
         }
      }

    Gpt_Init_Status =TRUE;
}

void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
    if(Gpt_Init_Status == FALSE)
    {
        GPT_REPORT_ERROR(GPT_INIT_ID, GPT_E_INIT_FAILED);
        return;
    }
}

void Gpt_StopTimer(Gpt_ChannelType Channel)
{
    if(Gpt_Init_Status == FALSE)
    {
        GPT_REPORT_ERROR(GPT_INIT_ID, GPT_E_INIT_FAILED);
        return;
    }
}
