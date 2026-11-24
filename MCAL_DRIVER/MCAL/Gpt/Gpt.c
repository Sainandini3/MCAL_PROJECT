#include<MCAL/Gpt/Gpt.h>
#include<MCAL/Gpt/Gpt_Cfg.h>
#include<MCAL/Gpt/IfxGpt12_reg.h>

void Enable_Module(void)
{
   CLC&=~(1U<<0);
}
void Disable_Module(void)
{
   CLC|=(1U<<0);
}
void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
    Gpt_ConfigType *SelectedConfig = NULL_PTR;
    SelectedConfig =(ConfigPtr == NULL_PTR) ? &Gpt_Config : ConfigPtr;

    Enable_Module();
    if(Gpt_ChannelConfigType->GptChannelMode!= GPT_CH_MODE_CONTINUOUS && Gpt_ChannelConfigType->GptChannelMode!=   GPT_CH_MODE_ONESHOT)
    {
       return;
    }


}
