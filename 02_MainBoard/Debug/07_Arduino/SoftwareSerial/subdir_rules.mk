################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
07_Arduino/SoftwareSerial/%.obj: ../07_Arduino/SoftwareSerial/%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/01_Applications" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/02_Config" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/03_Services" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/03_Services/01_Connectivity" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/03_Services/01_Connectivity/Protocol" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/03_Services/01_Connectivity/Protocol/msrData" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/04_Utils" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/05_Drivers" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/06_Board" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/07_Arduino/HttpClient" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/07_Arduino/SerialTransfer" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/07_Arduino/StreamDebugger" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/07_Arduino/SoftwareSerial" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/07_Arduino/TinyGSM" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/07_Arduino/TinyGPS" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard/08_Defines" --include_path="E:/Intership/Other_projects/MsysCode/02_MainBoard" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/drivers/bsp/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/drivers/bsp/package/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/avr/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/package/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/variants/MSP_EXP432P401R/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/msp432/variants/MSP_EXP432P401R/package/" --include_path="E:/Intership/Other_projects/MSP432_core/cores/msp432r/ti/runtime/wiring/package/" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --define=__MSP432P401R__ --define=__DEBUG --define=ARDUINO=101 --define=xDUMP_AT_COMMANDS --define=xdc__nolocalstring --define=PROTOCOL_VERSION=0x0200 --define=DEBUG_CONN_SERVICE -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="07_Arduino/SoftwareSerial/$(basename $(<F)).d_raw" --obj_directory="07_Arduino/SoftwareSerial" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


