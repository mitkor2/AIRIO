################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
cores/msp432r/ti/runtime/wiring/avr/dtostrf.obj: E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/avr/dtostrf.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1010/xdctools_3_61_02_27_core/packages" --include_path="C:/ti/ccs1010/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1010/ccs/ccs_base/arm/include/CMSIS" --include_path="E:/Intership/Other_projects/MsysCode/EnergiaCoreMSP432" --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/tirtos/packages" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/drivers/" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/drivers/bsp/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/drivers/bsp/package/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/avr/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/package/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/variants/MSP_EXP432P401R/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/variants/MSP_EXP432P401R/package/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/package/" --include_path="E:/Intership/Other_projects/MSP432_core/variants/MSP_EXP432P401R_AIRIO" --include_path="E:/Intership/Other_projects/MSP432_core/variants/MSP_EXP432P401R_AIRIO/package" --advice:power="all" --define=__MSP432P401R__ --define=ccs --define=xdc__nolocalstring --define=ENERGIA_BOARD_SERIAL1_RING_BUFFER_SIZE=2048 --define=ENERGIA_BOARD_SERIAL3_ENABLE --define=ENERGIA_BOARD_SERIAL2_ENABLE -g --gcc --diag_warning=225 --diag_wrap=off --no_warnings --abi=eabi --preproc_with_compile --preproc_dependency="cores/msp432r/ti/runtime/wiring/avr/$(basename $(<F)).d_raw" --obj_directory="cores/msp432r/ti/runtime/wiring/avr" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


