#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stddef.h>
#include "Cpu/Std/Platform_Types.h"

typedef uint8   Std_ReturnType;


#ifndef TRUE
#define TRUE       ((boolean)1U)
#endif
#ifndef FALSE
#define FALSE      ((boolean)0U)
#endif
#ifndef NULL_PTR
#define NULL_PTR   ((void *)0)
#endif

#ifndef STD_ON
#define STD_ON     (1U)
#endif
#ifndef STD_OFF
#define STD_OFF    (0U)
#endif

#define E_OK       ((Std_ReturnType)0U)
#define E_NOT_OK   ((Std_ReturnType)1U)

typedef struct
{
    uint16 vendorID;
    uint16 moduleID;
    uint8  sw_major_version;
    uint8  sw_minor_version;
    uint8  sw_patch_version;
} Std_VersionInfoType;

#endif
