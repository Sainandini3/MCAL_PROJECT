
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include <MCAL/Port/Port.h>
#include <MCAL/Port/Port_Cfg.h>

#include <MCAL/Dio/Dio.h>
#include <MCAL/Dio/Dio_Cfg.h>

#include <Includes/Std_Types.h>

IFX_ALIGN(4) IfxCpu_syncEvent cpuSyncEvent = 0;

static void delay(void)
{
    volatile unsigned int count;

    for (count = 0U; count < 5000000U; count++)
    {
    }
}

int core0_main(void)
{
    IfxCpu_enableInterrupts();

    IfxScuWdt_disableCpuWatchdog(
        IfxScuWdt_getCpuWatchdogPassword()
    );

    IfxScuWdt_disableSafetyWatchdog(
        IfxScuWdt_getSafetyWatchdogPassword()
    );


    Port_Init(NULL_PTR);

    while (1)
    {

        Dio_WriteChannel(0U, STD_HIGH);

        delay();


        Dio_WriteChannel(0U, STD_LOW);

        delay();
    }

    return 0;
}

