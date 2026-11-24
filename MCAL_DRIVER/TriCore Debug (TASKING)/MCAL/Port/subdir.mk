################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../MCAL/Port/Port.c" \
"../MCAL/Port/Port_Cfg.c" \
"../MCAL/Port/Port_Tc397Modes.c" 

COMPILED_SRCS += \
"MCAL/Port/Port.src" \
"MCAL/Port/Port_Cfg.src" \
"MCAL/Port/Port_Tc397Modes.src" 

C_DEPS += \
"./MCAL/Port/Port.d" \
"./MCAL/Port/Port_Cfg.d" \
"./MCAL/Port/Port_Tc397Modes.d" 

OBJS += \
"MCAL/Port/Port.o" \
"MCAL/Port/Port_Cfg.o" \
"MCAL/Port/Port_Tc397Modes.o" 


# Each subdirectory must supply rules for building sources it contributes
"MCAL/Port/Port.src":"../MCAL/Port/Port.c" "MCAL/Port/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Port/Port.o":"MCAL/Port/Port.src" "MCAL/Port/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MCAL/Port/Port_Cfg.src":"../MCAL/Port/Port_Cfg.c" "MCAL/Port/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Port/Port_Cfg.o":"MCAL/Port/Port_Cfg.src" "MCAL/Port/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MCAL/Port/Port_Tc397Modes.src":"../MCAL/Port/Port_Tc397Modes.c" "MCAL/Port/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc39xb "-fC:/Users/Admin/AURIX-v1.10.36-workspace/MCAL_DRIVER/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Wc-w508 -Ctc39xb -Y0 -N0 -Z0 -o "$@" "$<"
"MCAL/Port/Port_Tc397Modes.o":"MCAL/Port/Port_Tc397Modes.src" "MCAL/Port/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MCAL-2f-Port

clean-MCAL-2f-Port:
	-$(RM) ./MCAL/Port/Port.d ./MCAL/Port/Port.o ./MCAL/Port/Port.src ./MCAL/Port/Port_Cfg.d ./MCAL/Port/Port_Cfg.o ./MCAL/Port/Port_Cfg.src ./MCAL/Port/Port_Tc397Modes.d ./MCAL/Port/Port_Tc397Modes.o ./MCAL/Port/Port_Tc397Modes.src

.PHONY: clean-MCAL-2f-Port

