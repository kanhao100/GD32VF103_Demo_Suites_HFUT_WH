################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/LCD_common/subdir.mk
-include Utilities/subdir.mk
-include RISCV/stubs/subdir.mk
-include RISCV/env_Eclipse/subdir.mk
-include RISCV/drivers/subdir.mk
-include Peripherals/Source/subdir.mk
-include Peripherals/subdir.mk
-include Application/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
GPIO_按键_轮询查询.hex \

SECONDARY_LIST += \
GPIO_按键_轮询查询.lst \

SECONDARY_SIZE += \
GPIO_按键_轮询查询.siz \


# All Target
all: GPIO_按键_轮询查询.elf secondary-outputs

# Tool invocations
GPIO_按键_轮询查询.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C++ Linker'
	riscv-none-embed-g++ -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "D:\OneDrive - mail.hfut.edu.cn\文档\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_按键_轮询查询\RISCV\env_Eclipse\GD32VF103xB.lds" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"GPIO_按键_轮询查询.map" --specs=nano.specs -o "GPIO_按键_轮询查询.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

GPIO_按键_轮询查询.hex: GPIO_按键_轮询查询.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "GPIO_按键_轮询查询.elf"  "GPIO_按键_轮询查询.hex"
	@echo 'Finished building: $@'
	@echo ' '

GPIO_按键_轮询查询.lst: GPIO_按键_轮询查询.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "GPIO_按键_轮询查询.elf" > "GPIO_按键_轮询查询.lst"
	@echo 'Finished building: $@'
	@echo ' '

GPIO_按键_轮询查询.siz: GPIO_按键_轮询查询.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "GPIO_按键_轮询查询.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) GPIO_按键_轮询查询.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
