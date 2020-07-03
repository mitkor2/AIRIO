################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-508155233:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-508155233-inproc

build-508155233-inproc: ../debug.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs1010/xdctools_3_61_02_27_core/xs" --xdcpath="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source;C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/tirtos/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P401R -r release -c "C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-508155233 ../debug.cfg
configPkg/compiler.opt: build-508155233
configPkg/: build-508155233


