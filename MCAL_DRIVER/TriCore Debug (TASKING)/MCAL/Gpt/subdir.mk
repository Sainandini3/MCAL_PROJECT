################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../MCAL/Gpt/Gpt.c" \
"../MCAL/Gpt/Gpt_Cfg.c" \
"../MCAL/Gpt/Gpt_Hw.c" 

COMPILED_SRCS += \
"MCAL/Gpt/Gpt.src" \
"MCAL/Gpt/Gpt_Cfg.src" \
"MCAL/Gpt/Gpt_Hw.src" 

C_DEPS += \
"./MCAL/Gpt/Gpt.d" \
"./MCAL/Gpt/Gpt_Cfg.d" \
"./MCAL/Gpt/Gpt_Hw.d" 

OBJS += \
"MCAL/Gpt/Gpt.o" \
"MCAL/Gpt/Gpt_Cfg.o" \
"MCAL/Gpt/Gpt_Hw.o" 


# Each subdirectory must supply rules for building sources it contributes
"MCAL/Gpt/Gpt.src":"../MCAL/Gpt/Gpt.c" "MCAL/Gpt/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Gpt/Gpt.o":"MCAL/Gpt/Gpt.src" "MCAL/Gpt/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MCAL/Gpt/Gpt_Cfg.src":"../MCAL/Gpt/Gpt_Cfg.c" "MCAL/Gpt/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Gpt/Gpt_Cfg.o":"MCAL/Gpt/Gpt_Cfg.src" "MCAL/Gpt/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MCAL/Gpt/Gpt_Hw.src":"../MCAL/Gpt/Gpt_Hw.c" "MCAL/Gpt/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Gpt/Gpt_Hw.o":"MCAL/Gpt/Gpt_Hw.src" "MCAL/Gpt/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MCAL-2f-Gpt

clean-MCAL-2f-Gpt:
	-$(RM) ./MCAL/Gpt/Gpt.d ./MCAL/Gpt/Gpt.o ./MCAL/Gpt/Gpt.src ./MCAL/Gpt/Gpt_Cfg.d ./MCAL/Gpt/Gpt_Cfg.o ./MCAL/Gpt/Gpt_Cfg.src ./MCAL/Gpt/Gpt_Hw.d ./MCAL/Gpt/Gpt_Hw.o ./MCAL/Gpt/Gpt_Hw.src

.PHONY: clean-MCAL-2f-Gpt

