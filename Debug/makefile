################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./startup_msp432p401r_ccs.obj" \
"./system_msp432p401r.obj" \
"./vector.obj" \
"./src/devicelib/dac8571.obj" \
"./src/devicelib/ssd1351.obj" \
"./src/driverlib/adc14.obj" \
"./src/driverlib/clock_system_init.obj" \
"./src/driverlib/soft_i2c.obj" \
"./src/driverlib/soft_spi.obj" \
"./src/driverlib/usci_a0_uart.obj" \
"./src/driverlib/usci_b0_i2c.obj" \
"./src/driverlib/usci_b3_spi.obj" \
"./src/driverlib/wdt.obj" \
"./src/system/fonts.obj" \
"./src/system/init.obj" \
"./src/system/user.obj" \
"./src/user/display.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/devicelib/subdir_vars.mk
-include src/driverlib/subdir_vars.mk
-include src/system/subdir_vars.mk
-include src/user/subdir_vars.mk
-include subdir_rules.mk
-include src/devicelib/subdir_rules.mk
-include src/driverlib/subdir_rules.mk
-include src/system/subdir_rules.mk
-include src/user/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
msp432p401r_nosdk_red.out \

EXE_OUTPUTS__QUOTED += \
"msp432p401r_nosdk_red.out" \

BIN_OUTPUTS += \
msp432p401r_nosdk_red.hex \

BIN_OUTPUTS__QUOTED += \
"msp432p401r_nosdk_red.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "msp432p401r_nosdk_red.out"

# Tool invocations
msp432p401r_nosdk_red.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"msp432p401r_nosdk_red.map" --heap_size=1024 --stack_size=512 -i"C:/ti/ccs930/ccs/ccs_base/arm/include" -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/lib" -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="msp432p401r_nosdk_red_linkInfo.xml" --rom_model -o "msp432p401r_nosdk_red.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

msp432p401r_nosdk_red.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armhex" --memwidth=8 --romwidth=8 -o "msp432p401r_nosdk_red.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "startup_msp432p401r_ccs.obj" "system_msp432p401r.obj" "vector.obj" "src\devicelib\dac8571.obj" "src\devicelib\ssd1351.obj" "src\driverlib\adc14.obj" "src\driverlib\clock_system_init.obj" "src\driverlib\soft_i2c.obj" "src\driverlib\soft_spi.obj" "src\driverlib\usci_a0_uart.obj" "src\driverlib\usci_b0_i2c.obj" "src\driverlib\usci_b3_spi.obj" "src\driverlib\wdt.obj" "src\system\fonts.obj" "src\system\init.obj" "src\system\user.obj" "src\user\display.obj" 
	-$(RM) "main.d" "startup_msp432p401r_ccs.d" "system_msp432p401r.d" "vector.d" "src\devicelib\dac8571.d" "src\devicelib\ssd1351.d" "src\driverlib\adc14.d" "src\driverlib\clock_system_init.d" "src\driverlib\soft_i2c.d" "src\driverlib\soft_spi.d" "src\driverlib\usci_a0_uart.d" "src\driverlib\usci_b0_i2c.d" "src\driverlib\usci_b3_spi.d" "src\driverlib\wdt.d" "src\system\fonts.d" "src\system\init.d" "src\system\user.d" "src\user\display.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

