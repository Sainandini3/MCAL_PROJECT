

#ifndef ECU_H_
#define ECU_H_

#include<Includes/Std_Types.h>


#define PORT_E_PARAM_PIN 0x0A
#define PORT_E_DIRECTION_UNCHANGEABLE 0x0B
#define PORT_E_INIT_FAILED 0x0C
#define PORT_E_PARAM_INVALID_MODE 0x0D
#define PORT_E_MODE_UNCHANGEABLE 0x0E
#define PORT_E_UNINIT 0x0F
#define PORT_E_PARAM_POINTER 0x10

//DEVELOPMENT ERRORS
#define ECUM_E_UNINIT   0x00
#define ECUM_E_SERVICE_DISABLED 0x01
#define ECUM_E_NULL_POINTER     0x02
#define ECUM_E_INVALID_PAR      0x03
#define ECUM_E_STATE_PAR_OUT_OF_RANGE 0x04
#define ECUM_E_UNKNOWN_WAKEUP_SOURCE  0x05
#define ECUM_E_INIT_FAILED            0x06


//Runtime Errors
#define ECUM_E_RAM_CHECK_FAILED                 0x07
#define ECUM_E_CONFIGURATION_DATA_INCONSISTENT  0x08

//Service ID
#define ECUM_GETVERSIONINFO_ID 0x00
#define ECUM_GODOWNHALTPOLL_ID 0x2c
#define ECUM_INIT_ID 0x01
#define ECUM_STARTUPTWO_ID 0x1a
#define ECUM_SHUTDOWN_ID   0x02
#define ECUM_SETSTATE_ID   0x2b
#define ECUM_REQUESTRUN_ID 0x03
#define ECUM_RELEASERUN_ID 0x04
#define ECUM_REQUESTPOST_RUN_ID 0x0a
#define ECUM_RELEASEPOST_RUN_ID 0x0b
#define ECUM_SELECTSHUTDOWNTARGET_ID 0x06
#define ECUM_GETSHUTDOWNTARGET_ID  0x09
#define ECUM_GETLASTSHUTDOWNTARGET_ID 0x08
#define ECUM_SELECTSHUTDOWNCAUSE_ID 0x1b
#define ECUM_GETSHUTDOWNCAUSE_ID 0x1c
#define ECUM_GETPENDINGWAKEUPEVENTS_ID 0x0d
#define ECUM_CLEARWAKEUPEVENT_ID 0x16
#define ECUM_GETVALIDATEDWAKEUPEVENTS_ID 0x15
#define ECUM_GETEXPIREDWAKEUPEVENTS_ID 0x19
#define ECUM_SETRELWAKEUPALARM_ID 0x22
#define ECUM_SETABSWAKEUPALARM_ID 0x23
#define ECUM_ABORTWAKEUPALARM_ID 0x24
#define ECUM_GETCURRENTTIME_ID   0x25
#define ECUM_GETWAKEUPTIME_ID    0x26
#define ECUM_SETCLOCK_ID         0x27
#define ECUM_SELECTBOOTTARGET_ID 0x12
#define ECUM_GETBOOTTARGET_ID    0x13
#define ECUM_MAINFUNCTION_ID     0x18
#define ECUM_SETWAKEUPEVENT_ID   0x0c
#define ECUM_VALIDATEWAKEUPEVENT_ID 0x14
#define ECUM_ERRORHOOK_ID        0x30
#define ECUM_AL_SETPROGRAMMABLEINTERRUPTS_ID 0x4A
#define ECUM_AL_DRIVERINITZERO_ID 0x31
#define ECUM_DETERMINEPBCONFIGURATION_ID 0x32
#define ECUM_AL_DRIVERINITONE_ID 0x33
#define ECUM_LOOPDETECTION_ID    0x4B
#define ECUM_ONGOOFFONE_ID       0x3C
#define ECUM_ONGOOFFTWO_ID       0x3D
#define ECUM_AL_SWITCHOFF_ID     0x3E
#define ECUM_AL_RESET_ID         0x4C
#define ECUM_ENABLEWAKEUPSOURCES_ID 0x3F
#define ECUM_GENERATERAMHASH_ID     0x40
#define ECUM_SLEEPACTIVITY_ID       0x41
#define ECUM_STARTCHECKWAKEUP_ID    0x00
#define ECUM_CHECKWAKEUP_ID          0x42
#define ECUM_ENDCHECKWAKEUP_ID       0x00
#define ECUM_CHECKRAMHASH_ID         0x43
#define ECUM_DISABLEWAKEUPSOURCES_ID 0x44
#define ECUM_AL_DRIVERRESTART_ID     0x45
#define ECUM_STARTWAKEUPSOURCES_ID   0x46
#define ECUM_CHECKVALIDATION_ID      0x47
#define ECUM_STOPWAKEUPSOURCES_ID    0x48



//structure members
typedef struct EcuM_ConfigType EcuM_ConfigType;

typedef enum
{
    UNKNOWN,
    REQUESTED,
    RELEASED
}EcuM_RunStatusType;

typedef uint32 EcuM_UserType;
typedef uint32 EcuM_WakeupSourceType;
typedef uint32 EcuM_WakeupStatusType;

typedef uint8 EcuM_BootTargetType;
typedef uint8 EcuM_ResetType;
typedef uint8 EcuM_ShutdownCauseType;
typedef uint16 EcuM_ShutdownModeType;
typedef uint32 EcuM_TimeType;
typedef uint8 EcuM_ShutdownTargetType;


void EcuM_GetVersionInfo(Std_VersionInfoType *versioninfo);
Std_ReturnType EcuM_GoDownHaltPoll(uint16 caller);
void EcuM_Init(void);
void EcuM_StartupTwo(void);
void EcuM_Shutdown(void);
void EcuM_SetState(EcuM_ShutdownTargetType state);
Std_ReturnType EcuM_RequestRUN(EcuM_UserType user);
Std_ReturnType EcuM_ReleaseRUN(EcuM_UserType user);
Std_ReturnType EcuM_RequestPOST_RUN(EcuM_UserType user);
Std_ReturnType EcuM_ReleasePOST_RUN(EcuM_UserType user);
Std_ReturnType EcuM_SelectShutdownTarget(EcuM_ShutdownTargetType shutdownTarget,EcuM_ShutdownModeType shutdownMode);
Std_ReturnType EcuM_GetShutdownTarget(EcuM_ShutdownTargetType* shutdownTarget,EcuM_ShutdownModeType* shutdownMode);
Std_ReturnType EcuM_GetLastShutdownTarget(EcuM_ShutdownTargetType* shutdownTarget, EcuM_ShutdownModeType* shutdownMode);
Std_ReturnType EcuM_SelectShutdownCause(EcuM_ShutdownCauseType target);
Std_ReturnType EcuM_GetShutdownCause(EcuM_ShutdownCauseType* shutdownCause);
EcuM_WakeupSourceType EcuM_GetPendingWakeupEvents(void);
void EcuM_ClearWakeupEvent(EcuM_WakeupSourceType source);
EcuM_WakeupSourceType EcuM_GetValidateWakeupEvents(void);
EcuM_WakeupSourceType EcuM_GetExpiredWakeupEvents(void);
Std_ReturnType EcuM_SetRelWakeupAlarm(EcuM_UserType user, EcuM_TimeType time);
Std_ReturnType EcuM_SetAbsWakeupAlarm(EcuM_UserType user, EcuM_TimeType time);
Std_ReturnType EcuM_AbortWakeupAlarm(EcuM_UserType user);
Std_ReturnType EcuM_GetCurrentTime(EcuM_TimeType* time);
Std_ReturnType EcuM_GetWakeupTime(EcuM_TimeType* time);
Std_ReturnType EcuM_SetClock(EcuM_UserType user,EcuM_TimeType time);
Std_ReturnType EcuM_SelectBootTarget(EcuM_BootTargetType target);
Std_ReturnType EcuM_GetBootTarget(EcuM_BootTargetType* target);
void EcuM_MainFunction(void);
void EcuM_SetWakeupEvent(EcuM_WakeupSourceType soruces);
void EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources);
void EcuM_ErrorHook(uint16 reason);
void EcuM_AL_SetProgrammableInterrupts(void);
void EcuM_AL_DriverInitZero(void);
const EcuM_ConfigType* EcuM_DeterminePbConfiguration(void);
void EcuM_AL_DriverInitOne(void);
void EcuM_LoopDetection(void);
void EcuM_OnGoOffOne(void);
void EcuM_OnGoOffTwo(void);
void EcuM_AL_Switchoff(void);
void EcuM_AL_Reset(EcuM_ResetType reset);
void EcuM_EnableWakeupSources(EcuM_WakeupSourceType wakeupSource);
void EcuM_GenerateRamHash(void);
void EcuM_SleepActivity(void);
void EcuM_StartCheckWakeup(EcuM_WakeupSourceType wakeupSource);
void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource);
void EcuM_EndCheckWakeup(EcuM_WakeupSourceType WakeupSource);
void EcuM_CheckRamHash(void);
void EcuM_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource);
void EcuM_AL_DriverRestart(void);
void EcuM_StartWakeupSources(EcuM_WakeupSourceType wakeupSource);
void EcuM_CheckValidation(EcuM_WakeupSourceType wakeupSource);
void EcuM_StopWakeupSources(EcuM_WakeupSourceType wakeupSource);



#endif
