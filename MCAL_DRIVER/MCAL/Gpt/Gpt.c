#include<MCAL/Gpt/Gpt.h>
#include<MCAL/Gpt/Gpt_Hw.h>
#include<MCAL/Gpt/Gpt_Cfg.h>
#include<MCAL/Gpt/IfxGpt12_reg.h>

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#define GPT_REPORT_ERROR(ApiId, ErrorId) do { (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)(ApiId), (uint8)(ErrorId)); } while (0)
#else
#define GPT_REPORT_ERROR(ApiId, ErrorId) do { (void)(ApiId); (void)(ErrorId); } while (0)
#endif

static boolean Gpt_Init_Status =FALSE;
static boolean Running= FALSE;
static boolean Stopped= FALSE;
//static boolean Expired= FALSE;

static boolean Validate_Config(const Gpt_ConfigType* SelectedConfig);

static boolean Enable_Module(void)
{
   CLC&=~(1U<<DISR);
   if((CLC&(1U<<DISS) )== 0U)
       return TRUE;
  return FALSE;
}

static void Check_Status(volatile unsigned int *REGISTER)
{
    if(*REGISTER &(1U<<T2R)==0U){
          GPT_REPORT_ERROR(GPT_STARTTIMER_ID ,GPT_E_BUSY);
    }else{
       *REGISTER|= (1U<<T2R);
       Running =TRUE;
    }
}


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

    SelectedConfig = ConfigPtr;

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
        if(Gpt_Hw_InitChannel(Channel_cfg) != E_OK)
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
        GPT_REPORT_ERROR(GPT_STARTTIMER_ID , GPT_E_UNINIT);
        return;
    }

    if(Channel>4)
    {
        GPT_REPORT_ERROR(GPT_STARTTIMER_ID ,GPT_E_PARAM_CHANNEL);
        return;
    }
    if(Value<0 && Value>65535)
    {
        GPT_REPORT_ERROR(GPT_STARTTIMER_ID ,GPT_E_PARAM_VALUE);
    }
    switch(Channel)
    {
    case GPT_HW_GPT12_T2:   Check_Status(&T2CON); break;
    case GPT_HW_GPT12_T3:   Check_Status(&T3CON); break;
    case GPT_HW_GPT12_T4:   Check_Status(&T4CON); break;
    case GPT_HW_GPT12_T5:   Check_Status(&T5CON); break;
    case GPT_HW_GPT12_T6:   Check_Status(&T6CON); break;
    }
    /*
    switch(Channel)
    {
        case GPT_HW_GPT12_T2:   T2CON |= (1U<<6);  break;
        case GPT_HW_GPT12_T3:   T3CON |= (1U<<6);  break;
        case GPT_HW_GPT12_T4:   T4CON |= (1U<<6);  break;
        case GPT_HW_GPT12_T5:   T5CON |= (1U<<6);  break;
        case GPT_HW_GPT12_T6:   T6CON |= (1U<<6);  break;
    }
   */

}

void Gpt_StopTimer(Gpt_ChannelType Channel)
{
    if(Gpt_Init_Status == FALSE)
    {
        GPT_REPORT_ERROR(GPT_STOPTIMER_ID, GPT_E_UNINIT);
        return;
    }

    if(Channel>4)
    {
        GPT_REPORT_ERROR(GPT_STOPTIMER_ID,GPT_E_PARAM_CHANNEL);
        return;
    }
    switch(Channel)
    {
     case GPT_HW_GPT12_T2:  if(( T2CON &(1U<<6))!=0)   T2CON |= (0U<<6);  break;
     case GPT_HW_GPT12_T3:  if(( T3CON &(1U<<6))!=0)   T3CON |= (0U<<6);  break;
     case GPT_HW_GPT12_T4:  if(( T4CON &(1U<<6))!=0)   T4CON |= (0U<<6);  break;
     case GPT_HW_GPT12_T5:  if(( T5CON &(1U<<6))!=0)   T5CON |= (0U<<6);  break;
     case GPT_HW_GPT12_T6:  if(( T6CON &(1U<<6))!=0)   T6CON |= (0U<<6);  break;

    }
 /*   switch(Channel)
    {
        case GPT_HW_GPT12_T2:   T2CON |= (0U<<6);  break;
        case GPT_HW_GPT12_T3:   T3CON |= (0U<<6);  break;
        case GPT_HW_GPT12_T4:   T4CON |= (0U<<6);  break;
        case GPT_HW_GPT12_T5:   T5CON |= (0U<<6);  break;
        case GPT_HW_GPT12_T6:   T6CON |= (0U<<6);  break;
    }
*/

}

void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
    if( Gpt_Init_Status!=TRUE)
    {
          GPT_REPORT_ERROR(GPT_ENABLENOTIFICATION_ID  , GPT_E_UNINIT);
          return;
    }

    if(Channel>4)
    {
            GPT_REPORT_ERROR(GPT_ENABLENOTIFICATION_ID ,GPT_E_PARAM_CHANNEL);
            return;
    }
    const Gpt_ConfigType *SelectedConfig =&Gpt_Config;
    const Gpt_ChannelConfigType *Channel_cfg = NULL_PTR;

    for(uint32 index=0;index<SelectedConfig->NumberOfChannels;index++)
     {
           Channel_cfg= &SelectedConfig->ChannelConfigPtr[index];
     }

}

void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    if( Gpt_Init_Status!=TRUE)
    {
      GPT_REPORT_ERROR(GPT_ENABLENOTIFICATION_ID  , GPT_E_UNINIT);
      return;
    }
    if(Channel>4)
    {
      GPT_REPORT_ERROR(GPT_ENABLENOTIFICATION_ID ,GPT_E_PARAM_CHANNEL);
      return;
    }

}

void Gpt_EnableWakeup(Gpt_ChannelType Channel)
{
    if( Gpt_Init_Status!=TRUE)
    {
          GPT_REPORT_ERROR(GPT_ENABLEWAKEUP_ID , GPT_E_UNINIT);
          return;
    }
    if(Channel>4)
    {
        GPT_REPORT_ERROR(GPT_ENABLEWAKEUP_ID , GPT_E_PARAM_CHANNEL);
          return;
    }
    const Gpt_ConfigType *SelectedConfig=&Gpt_Config;
    const Gpt_ChannelConfigType *Channel_Config=NULL_PTR;
      for(uint32 index=0;index<SelectedConfig->NumberOfChannels;index++)
      {
          Channel_Config= &SelectedConfig->ChannelConfigPtr[index];
          if(Channel_Config->GptChannelId == Channel && Channel_Config->EnableWakeup == TRUE)
          {

          }
      }
}

void Gpt_SetMode(Gpt_ModeType Mode)
{
    if( Gpt_Init_Status!=TRUE)
    {
        GPT_REPORT_ERROR(GPT_SETMODE_ID,  GPT_E_PARAM_MODE);
        return;
    }

    if(Mode != SLEEP_MODE && Mode != NORMAL_MODE)
    {
        GPT_REPORT_ERROR(GPT_SETMODE_ID,  GPT_E_PARAM_MODE);
    }
    const Gpt_ConfigType *SelectedConfig=&Gpt_Config;
    const Gpt_ChannelConfigType *Channel_Config=NULL_PTR;
    for(uint32 index=0;index<SelectedConfig->NumberOfChannels;index++)
    {
         Channel_Config= &SelectedConfig->ChannelConfigPtr[index];
         if( Channel_Config->EnableWakeup == FALSE )  //enable ch
         {
             continue;
         }else
         {
             Gpt_StartTimer(Channel_Config->GptChannelId,Channel_Config->TickValueMax);  //what value
             Gpt_EnableWakeup(Channel_Config->GptChannelId); //which timer channel
         }

         if(Mode == SLEEP_MODE )
         {

              CLC&=~(1U<<EDIS);
              if(Channel_Config->EnableWakeup == FALSE &&  Running==TRUE)
              {
                  Running = FALSE;  //Timerchannel should be stopped
                  Stopped = TRUE;  //TCON appropriated timer should be stopped
              }
         }else
         {
               //check if driver is in sleep mode
               /*if()
               {

               }*/
               if(Channel_Config->GptNotification!=NULL_PTR)
               {
                   Gpt_EnableNotification(Channel_Config->GptChannelId); //which timer channel
               }
         }
    }
}

Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
        if( Gpt_Init_Status!=TRUE)
        {
            GPT_REPORT_ERROR(GPT_GET_TIME_ELAPSED_ID , GPT_E_UNINIT);
            return 0;
        }
        if(Channel>4)
        {
            GPT_REPORT_ERROR(GPT_GET_TIME_ELAPSED_ID , GPT_E_PARAM_CHANNEL);
            return 0;
        }

       const Gpt_ConfigType *SelectedConfig=&Gpt_Config;
       const Gpt_ChannelConfigType *Channel_Config=NULL_PTR;
       for(uint32 index=0;index<SelectedConfig->NumberOfChannels;index++)
       {
           Channel_Config= &SelectedConfig->ChannelConfigPtr[index];
           if(Channel_Config->GptChannelMode == GPT_CH_MODE_ONESHOT)
           {

           }
       }
       return 1;
}


Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
    if( Gpt_Init_Status!=TRUE)
    {
       GPT_REPORT_ERROR(GPT_GETTIMEREMAINING_ID   , GPT_E_UNINIT);
       return 0;
    }
    if(Channel>4)
    {
       GPT_REPORT_ERROR(GPT_GETTIMEREMAINING_ID   , GPT_E_PARAM_CHANNEL);
       return 0;
    }
}
