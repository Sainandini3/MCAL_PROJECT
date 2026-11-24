################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../MCAL/Dio/Dio.c" \
"../MCAL/Dio/Dio_Cfg.c" 

COMPILED_SRCS += \
"MCAL/Dio/Dio.src" \
"MCAL/Dio/Dio_Cfg.src" 

C_DEPS += \
"./MCAL/Dio/Dio.d" \
"./MCAL/Dio/Dio_Cfg.d" 

OBJS += \
"MCAL/Dio/Dio.o" \
"MCAL/Dio/Dio_Cfg.o" 


# Each subdirectory must supply rules for building sources it contributes
"MCAL/Dio/Dio.src":"../MCAL/Dio/Dio.c" "MCAL/Dio/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Dio/Dio.o":"MCAL/Dio/Dio.src" "MCAL/Dio/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MCAL/Dio/Dio_Cfg.src":"../MCAL/Dio/Dio_Cfg.c" "MCAL/Dio/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Dio/Dio_Cfg.o":"MCAL/Dio/Dio_Cfg.src" "MCAL/Dio/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MCAL-2f-Dio

clean-MCAL-2f-Dio:
	-$(RM) ./MCAL/Dio/Dio.d ./MCAL/Dio/Dio.o ./MCAL/Dio/Dio.src ./MCAL/Dio/Dio_Cfg.d ./MCAL/Dio/Dio_Cfg.o ./MCAL/Dio/Dio_Cfg.src

.PHONY: clean-MCAL-2f-Dio

