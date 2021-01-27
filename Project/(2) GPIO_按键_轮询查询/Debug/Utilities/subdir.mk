################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/gd32vf103c_start.c \
../Utilities/gd32vf103v_lcd_eval.c 

OBJS += \
./Utilities/gd32vf103c_start.o \
./Utilities/gd32vf103v_lcd_eval.o 

C_DEPS += \
./Utilities/gd32vf103c_start.d \
./Utilities/gd32vf103v_lcd_eval.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Application" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Peripherals" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Peripherals\Include" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Peripherals\Source" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\RISCV\stubs" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\RISCV\drivers" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\RISCV\env_Eclipse" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Utilities" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Utilities\LCD_common" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


