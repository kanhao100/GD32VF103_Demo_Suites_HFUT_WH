################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Source/gd32vf103_adc.c \
../Peripherals/Source/gd32vf103_bkp.c \
../Peripherals/Source/gd32vf103_can.c \
../Peripherals/Source/gd32vf103_crc.c \
../Peripherals/Source/gd32vf103_dac.c \
../Peripherals/Source/gd32vf103_dbg.c \
../Peripherals/Source/gd32vf103_dma.c \
../Peripherals/Source/gd32vf103_eclic.c \
../Peripherals/Source/gd32vf103_exmc.c \
../Peripherals/Source/gd32vf103_exti.c \
../Peripherals/Source/gd32vf103_fmc.c \
../Peripherals/Source/gd32vf103_fwdgt.c \
../Peripherals/Source/gd32vf103_gpio.c \
../Peripherals/Source/gd32vf103_i2c.c \
../Peripherals/Source/gd32vf103_pmu.c \
../Peripherals/Source/gd32vf103_rcu.c \
../Peripherals/Source/gd32vf103_rtc.c \
../Peripherals/Source/gd32vf103_spi.c \
../Peripherals/Source/gd32vf103_timer.c \
../Peripherals/Source/gd32vf103_usart.c \
../Peripherals/Source/gd32vf103_wwdgt.c 

OBJS += \
./Peripherals/Source/gd32vf103_adc.o \
./Peripherals/Source/gd32vf103_bkp.o \
./Peripherals/Source/gd32vf103_can.o \
./Peripherals/Source/gd32vf103_crc.o \
./Peripherals/Source/gd32vf103_dac.o \
./Peripherals/Source/gd32vf103_dbg.o \
./Peripherals/Source/gd32vf103_dma.o \
./Peripherals/Source/gd32vf103_eclic.o \
./Peripherals/Source/gd32vf103_exmc.o \
./Peripherals/Source/gd32vf103_exti.o \
./Peripherals/Source/gd32vf103_fmc.o \
./Peripherals/Source/gd32vf103_fwdgt.o \
./Peripherals/Source/gd32vf103_gpio.o \
./Peripherals/Source/gd32vf103_i2c.o \
./Peripherals/Source/gd32vf103_pmu.o \
./Peripherals/Source/gd32vf103_rcu.o \
./Peripherals/Source/gd32vf103_rtc.o \
./Peripherals/Source/gd32vf103_spi.o \
./Peripherals/Source/gd32vf103_timer.o \
./Peripherals/Source/gd32vf103_usart.o \
./Peripherals/Source/gd32vf103_wwdgt.o 

C_DEPS += \
./Peripherals/Source/gd32vf103_adc.d \
./Peripherals/Source/gd32vf103_bkp.d \
./Peripherals/Source/gd32vf103_can.d \
./Peripherals/Source/gd32vf103_crc.d \
./Peripherals/Source/gd32vf103_dac.d \
./Peripherals/Source/gd32vf103_dbg.d \
./Peripherals/Source/gd32vf103_dma.d \
./Peripherals/Source/gd32vf103_eclic.d \
./Peripherals/Source/gd32vf103_exmc.d \
./Peripherals/Source/gd32vf103_exti.d \
./Peripherals/Source/gd32vf103_fmc.d \
./Peripherals/Source/gd32vf103_fwdgt.d \
./Peripherals/Source/gd32vf103_gpio.d \
./Peripherals/Source/gd32vf103_i2c.d \
./Peripherals/Source/gd32vf103_pmu.d \
./Peripherals/Source/gd32vf103_rcu.d \
./Peripherals/Source/gd32vf103_rtc.d \
./Peripherals/Source/gd32vf103_spi.d \
./Peripherals/Source/gd32vf103_timer.d \
./Peripherals/Source/gd32vf103_usart.d \
./Peripherals/Source/gd32vf103_wwdgt.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Source/%.o: ../Peripherals/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Application" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Peripherals" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Peripherals\Include" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Peripherals\Source" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\RISCV\stubs" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\RISCV\drivers" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\RISCV\env_Eclipse" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Utilities" -I"D:\NucleiStudio_IDE_201908\GPIO_°´¼ü_ÂÖÑ¯²éÑ¯\Utilities\LCD_common" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


