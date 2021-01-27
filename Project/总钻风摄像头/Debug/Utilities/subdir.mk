################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/gd32vf103v_eval.c \
../Utilities/gd32vf103v_lcd_eval.c 

OBJS += \
./Utilities/gd32vf103v_eval.o \
./Utilities/gd32vf103v_lcd_eval.o 

C_DEPS += \
./Utilities/gd32vf103v_eval.d \
./Utilities/gd32vf103v_lcd_eval.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\Application" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\Peripherals" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\Peripherals\Include" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\Peripherals\Source" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\RISCV\stubs" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\RISCV\drivers" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\RISCV\env_Eclipse" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\Utilities" -I"D:\NucleiStudio_IDE_201908\NucleiStudio_IDE_201908_Workspace\总钻风摄像头\Utilities\LCD_common" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


