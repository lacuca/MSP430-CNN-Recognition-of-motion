################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/msp430_4.3.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./source/WEIGHTS.obj" \
"./source/USER_UART.obj" \
"./source/USER_MATRIX.obj" \
"./source/USER_LCD.obj" \
"./source/USER_DIO.obj" \
"./source/USER_CNN.obj" \
"./source/MSP430_UCS.obj" \
"./source/MSP430_UART.obj" \
"./source/MSP430_TIMER.obj" \
"./source/MSP430_ADC.obj" \
"./source/LCD_FONTS.obj" \
"./source/DEV_LCD_HD66753.obj" \
"./main.obj" \
"../lnk_msp430f5438a.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MSP430_LCD_char.out \

EXE_OUTPUTS__QUOTED += \
"MSP430_LCD_char.out" \


# All Target
all: MSP430_LCD_char.out

# Tool invocations
MSP430_LCD_char.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmspx --abi=coffabi -Ooff -g --advice:power="all" --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal -z --stack_size=160 -m"MSP430_LCD_char.map" --heap_size=160 --use_hw_mpy=F5 -i"c:/ti/ccsv6/ccs_base/msp430/include" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/lib" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --reread_libs --warn_sections --display_error_number --xml_link_info="MSP430_LCD_char_linkInfo.xml" --rom_model -o "MSP430_LCD_char.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "source\DEV_LCD_HD66753.pp" "source\LCD_FONTS.pp" "source\MSP430_ADC.pp" "source\MSP430_UART.pp" "source\MSP430_UCS.pp" "source\USER_CNN.pp" "source\USER_UART.pp" "source\WEIGHTS.pp" 
	-$(RM) "source\MSP430_TIMER.pp" "source\USER_DIO.pp" "source\USER_LCD.pp" "source\USER_MATRIX.pp" 
	-$(RM) "main.obj" "source\DEV_LCD_HD66753.obj" "source\LCD_FONTS.obj" "source\MSP430_ADC.obj" "source\MSP430_TIMER.obj" "source\MSP430_UART.obj" "source\MSP430_UCS.obj" "source\USER_CNN.obj" "source\USER_DIO.obj" "source\USER_LCD.obj" "source\USER_MATRIX.obj" "source\USER_UART.obj" "source\WEIGHTS.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

