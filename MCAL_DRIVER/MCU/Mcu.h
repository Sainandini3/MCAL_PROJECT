
//production errors
#define MCU_E_CLOCK_FAILURE 0x00
#define Mcu_ModeType unsigned int
#define Mcu_RamSectionType unsigned int
#define Mcu_RamStateType unsigned int
#define Mcu_RawResetType unsigned int
#define Mcu_ModeType unsigned int

//service ids
#define MCU_INIT_ID 0x00
#define MCU_INITRAMSECTION_ID 0x01
#define MCU_INITCLOCK_ID 0x02
#define MCU_DISTRIBUTEPLLCLOCK_ID 0x03
#define MCU_GETPLLSTATUS_ID 0x04
#define MCU_GETRESETREASON_ID 0x05
#define MCU_GETRESETRAWVALUE_ID 0x06
#define MCU_PERFORMRESET_ID 0x07
#define MCU_SETMODE_ID 0x08
#define MCU_GETVERSIONINFO_ID 0x09
#define MCU_GETRAMSTATE_ID 0x0a



struct Mcu_ConfigType
{

};

enum Mcu_PllStatusType
{
  PLL_LOCKED,
  PLL_UNLOCKED,
  PLL_STATUS_UNDEFINED
};

enum Mcu_ResetType
{
    POWER_ON_RESET,
    WATCHDOG_RESET,
    SW_RESET,
    RESET_UNDEFINED
};


void Mcu_Init(const Mcu_ConfigType* ConfigPtr);
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection);
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);
Std_ReturnType Mcu_DistributePllClock(void);
Mcu_ResetType Mcu_GetResetReason(void);
Mcu_PllStatusType Mcu_GetPllStatus(void);
Mcu_RawResetType Mcu_GetResetRawValue(void);
void Mcu_PerformReset(void);
void Mcu_SetMode(Mcu_ModeType McuMode);
void Mcu_GetVersionInfo(Std_VersionInfoType* versioninfo);
Mcu_RamStateType Mcu_GetRamState(void);

