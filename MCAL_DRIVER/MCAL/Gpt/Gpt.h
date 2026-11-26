#ifndef GPT_H
#define GPT_H

#include<Includes/Std_Types.h>
#include <MCAL/Ecu.h>
#include <MCAL/Gpt/Gpt_Cfg.h>

//Development Errors
#define GPT_E_UNINIT              0x0A
#define GPT_E_ALREADY_INITIALIZED 0x0D
#define GPT_E_INIT_FAILED         0x0E
#define GPT_E_PARAM_CHANNEL       0x014
#define GPT_E_PARAM_VALUE         0x15
#define GPT_E_PARAM_POINTER       0x16
#define GPT_E_PARAM_PREDEF_TIMER  0x17
#define GPT_E_PARAM_MODE          0x1F

//Runtime Errors
#define GPT_E_BUSY 0x0B
#define GPT_E_MODE 0x0C

//Service IDs
#define GPT_GETVERSIONINFO_ID          0x00U
#define GPT_INIT_ID                    0x01U
#define GPT_DEINIT_ID                  0x02U
#define GPT_GET_TIME_ELAPSED_ID           0x03U
#define GPT_GETTIMEREMAINING_ID         0x04U
#define GPT_STARTTIMER_ID               0x05U
#define GPT_STOPTIMER_ID                0x06U
#define GPT_ENABLENOTIFICATION_ID       0x07U
#define GPT_DISABLENOTIFICATION_ID      0x08U
#define GPT_SETMODE_ID                  0x09U
#define GPT_DISABLEWAKEUP_ID            0x0AU
#define GPT_CHECKWAKEUP_ID              0x0CU
#define GPT_GETPREDEFTIMERVALUE_ID      0x0DU

#define GPT_MODE_NORMAL 0x00U
#define GPT_MODE_SLEEP 0x01U

#define  GPT_PREDEF_TIMER_1US_16BIT 0x00U
#define  GPT_PREDEF_TIMER_1US_24BIT 0x01U
#define  GPT_PREDEF_TIMER_1US_32BIT 0x02U
#define  GPT_PREDEF_TIMER_100US_32BIT 0x03U

#define ENABLE_MODULE 0
#define DISABLE_MODULE 1

#define  Gpt_ChannelType unsigned int
#define Gpt_ValueType  unsigned int


typedef enum
{
    GPT_CH_MODE_CONTINUOUS,
    GPT_CH_MODE_ONESHOT

}GptChannelMode;

typedef enum
{
    GPT_HW_GPT12_T2=0U,
    GPT_HW_GPT12_T3,
    GPT_HW_GPT12_T4,
    GPT_HW_GPT12_T5,
    GPT_HW_GPT12_T6
}Gpt_HwChannelType;

typedef uint64 GptChannelTickValueMax;
#define GptEnableWakeup  boolean
typedef uint32 GptChannelId;

typedef enum
{
    GPT_T3_INPUT_NONE = 0U,
    GPT_T3_INPUT_A,
    GPT_T3_INPUT_B
} Gpt_T3InputType;

typedef enum
{
    GPT_T3_OUTPUT_NONE = 0U,
    GPT_T3_OUTPUT_P10_6,
    GPT_T3_OUTPUT_P21_6
} Gpt_T3OutputType;

//GptChannelClkSrcRef SrcRef;
//GptChannelEcucPartitionRef Ecupartition;
//GptClockReferencePoint RefPoint;
// GptChannelTickFrequency Tick_Frequency;
typedef struct
{
  GptChannelId GptChannelId;
  Gpt_HwChannelType HwChannel;
  GptChannelMode GptChannelMode;
  uint32 TickValueMax;
  uint32 TickFrequency;
  Gpt_T3InputType  InputSelection;
  Gpt_T3OutputType OutputSelection;
  boolean EnableWakeup;
  void (*GptNotification) (void);
  boolean NotificationEnabled;

}Gpt_ChannelConfigType;

typedef struct
{
    boolean Initialized;
    boolean Running;
    boolean NotificationEnabled;
    Gpt_ValueType InitialValue;
    Gpt_ValueType MaximumValue;
    const Gpt_ChannelConfigType *ConfigPtr;
} Gpt_ChannelRuntimeType;

typedef struct
{
   const Gpt_ChannelConfigType *ChannelConfigPtr;
   uint8 NumberOfChannels;
}Gpt_ConfigType;

extern const Gpt_ConfigType Gpt_Config;


typedef enum{
   NORMAL_MODE,
   SLEEP_MODE
}Gpt_ModeType;

typedef enum
{
  TIMER_1US_16BIT,
  TIMER_1US_24BIT,
  TIMER_1US_32BIT,
  TIMER_100US_32BIT
}Gpt_PredefTimerType;

void Gpt_Init(const Gpt_ConfigType* ConfigPtr);
void Gpt_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr);

#if (GPT_DEINIT_API == STD_ON)
void Gpt_DeInit(void);
#endif

#if (GPT_TIME_ELAPSED_API == STD_ON)
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);
#endif


Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);
void Gpt_StopTimer(Gpt_ChannelType Channel);
void Gpt_EnableNotification(Gpt_ChannelType Channel);
void Gpt_DisableNotification(Gpt_ChannelType Channel);
void Gpt_SetMode(Gpt_ModeType Mode);
void Gpt_DisableWakeup(Gpt_ChannelType Channel);
void Gpt_EnableWakeup(Gpt_ChannelType Channel);
void Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimerValuePtr);
//void Gpt_Notification_<channel>Isr (void);



#endif

