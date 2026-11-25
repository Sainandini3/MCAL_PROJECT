#ifndef MCAL_PORTHW_H
#define MCAL_PORTHW_H

#include <Includes/Std_Types.h>
#include <Libraries/iLLD/TC3xx/Tricore/Port/Std/IfxPort_reg.h>

#define MCAL_PORTHW_OUT_OFFSET       (0x00U)
#define MCAL_PORTHW_OMR_OFFSET       (0x04U)
#define MCAL_PORTHW_IN_OFFSET        (0x24U)

#define MCAL_PORTHW_IOCR0_OFFSET     (0x10U)
#define MCAL_PORTHW_IOCR4_OFFSET     (0x14U)
#define MCAL_PORTHW_IOCR8_OFFSET     (0x18U)
#define MCAL_PORTHW_IOCR12_OFFSET    (0x1CU)

#define MCAL_PORTHW_PIN_MASK         (0x0000FFFFUL)

volatile uint8 *Mcal_PortHw_GetBaseAddress(uint8 PortNumber);

uint32 Mcal_PortHw_ReadRegister(volatile uint8 *BaseAddress, uint32 Offset);

boolean Mcal_PortHw_WriteRegister(volatile uint8 *BaseAddress,uint32 Offset, uint32 Value);

boolean Mcal_PortHw_WritePinLevel(uint8 PortNumber, uint8 PinNumber,boolean LevelHigh);

#endif
