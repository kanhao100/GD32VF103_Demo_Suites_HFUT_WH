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
总钻风摄像头.hex \

SECONDARY_LIST += \
总钻风摄像头.lst \

SECONDARY_SIZE += \
总钻风摄像头.siz \


# All Target
all: 总钻风摄像头.elf secondary-outputs

# Tool invocations
总钻风摄像头.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C++ Linker'
	riscv-none-embed-g++ -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\RISCV\env_Eclipse\GD32VF103xB.lds" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"总钻风摄像头.map" --specs=nano.specs -o "总钻风摄像头.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

总钻风摄像头.hex: 总钻风摄像头.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "总钻风摄像头.elf"  "总钻风摄像头.hex"
	@echo 'Finished building: $@'
	@echo ' '

总钻风摄像头.lst: 总钻风摄像头.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "总钻风摄像头.elf" > "总钻风摄像头.lst"
	@echo 'Finished building: $@'
	@echo ' '

总钻风摄像头.siz: 总钻风摄像头.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "总钻风摄像头.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) 总钻风摄像头.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
