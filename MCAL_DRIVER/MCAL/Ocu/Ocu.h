//DEVELOPMENT ERRORS
#define OCU_E_UNINIT 0x02
#define OCU_E_PARAM_INVALID_CHANNEL 0x03
#define OCU_E_PARAM_INVALID_STATE   0x04
#define OCU_E_PARAM_INVALID_ACTION  0x05
#define OCU_E_NO_VALID_NOTIF   0x06
#define OCU_E_ALREADY_INITIALIZED  0x07
#define OCU_E_PARAM_POINTER 0x08
#define OCU_E_BUSY          0x09
#define OCU_E_PARAM_NO_PIN  0x0A
#define OCU_E_INIT_FAILED   0x0B


//service ids
#define OCU_INIT_ID 0x00
#define OCU_DELINIT_ID 0x01
#define OCU_STARTCHANNEL_ID 0x02
#define OCU_STOPCHANNEL_ID  0x03
#define OCU_SETPINSTATE_ID  0x04
#define OCU_SETPINACTION_ID 0x05
#define OCU_GETCOUNTER_ID   0x06
#define OCU_SETABSOLUTE_THRESHOLD_ID 0x07
#define OCU_SETRELATIVE_THRESHOLD_ID  0x08
#define OCU_DISABLENOTIFICATION_ID    0x0a
#define OCU_ENABLENOTIFICATION_ID     0x0b
#define OCU_GETVERSIONINFO_ID         0x09


#define Ocu_ChannelType unsigned int
#define Ocu_ValueType   unsigned int
typedef enum
{
   HIGH,
   LOW
}Ocu_PinStateType;

typedef enum
{
    HIGH,
    LOW,
    TOGGLE,
    DISABLE
}Ocu_PinActionType;

typedef struct
{

}Ocu_ConfigType;

typedef enum
{
   OCU_CM_IN_REF_INTERVAL,
   OCU_CM_OUT_REF_INTERVAL
}Ocu_ReturnType;


void Ocu_Init(const Ocu_ConfigType* ConfigPtr);
void Ocu_DeInit(void);
void Ocu_StartChannel(Ocu_ChannelType ChannelNumber);
void Ocu_StopChannel(Ocu_ChannelType ChannelNumber);
void Ocu_SetPinState(Ocu_ChannelType ChannelNumber, Ocu_PinStateType PinState);
void Ocu_SetPinAction(Ocu_ChannelType ChannelNumber, Ocu_PinActionType PinAction);
Ocu_ValueType Ocu_GetCounter(Ocu_ChannelType ChannelNumber);
Ocu_ReturnType Ocu_SetAbsoluteThreshold(Ocu_ChannelType ChannelNumber,Ocu_ValueType ReferenceValue, Ocu_ValueType AbsoluteValue);
Ocu_ReturnType Ocu_SetRelativeThreshold(Ocu_ChannelType ChannelNumber, Ocu_ValueType RelativeValue);
void Ocu_DisableNotification(Ocu_ChannelType ChannelNumber);
void Ocu_EnableNotification(Ocu_ChannelType ChannelNumber);
void Ocu_GetVersionInfo(Std_VersionInfoType* versioninfo);
void Ocu_Notification_<Channel>(void);
