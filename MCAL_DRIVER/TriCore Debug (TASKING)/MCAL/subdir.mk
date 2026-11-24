################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../MCAL/Mcal_PortHw.c" 

COMPILED_SRCS += \
"MCAL/Mcal_PortHw.src" 

C_DEPS += \
"./MCAL/Mcal_PortHw.d" 

OBJS += \
"MCAL/Mcal_PortHw.o" 


# Each subdirectory must supply rules for building sources it contributes
"MCAL/Mcal_PortHw.src":"../MCAL/Mcal_PortHw.c" "MCAL/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Mcal_PortHw.o":"MCAL/Mcal_PortHw.src" "MCAL/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MCAL

clean-MCAL:
	-$(RM) ./MCAL/Mcal_PortHw.d ./MCAL/Mcal_PortHw.o ./MCAL/Mcal_PortHw.src

.PHONY: clean-MCAL

