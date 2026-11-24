################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../MCAL/Det/Det.c" 

COMPILED_SRCS += \
"MCAL/Det/Det.src" 

C_DEPS += \
"./MCAL/Det/Det.d" 

OBJS += \
"MCAL/Det/Det.o" 


# Each subdirectory must supply rules for building sources it contributes
"MCAL/Det/Det.src":"../MCAL/Det/Det.c" "MCAL/Det/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Det/Det.o":"MCAL/Det/Det.src" "MCAL/Det/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MCAL-2f-Det

clean-MCAL-2f-Det:
	-$(RM) ./MCAL/Det/Det.d ./MCAL/Det/Det.o ./MCAL/Det/Det.src

.PHONY: clean-MCAL-2f-Det

