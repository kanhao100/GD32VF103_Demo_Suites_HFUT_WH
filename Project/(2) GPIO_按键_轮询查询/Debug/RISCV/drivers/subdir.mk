################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RISCV/drivers/n200_func.c 

OBJS += \
./RISCV/drivers/n200_func.o 

C_DEPS += \
./RISCV/drivers/n200_func.d 


# Each subdirectory must supply rules for building sources it contributes
RISCV/drivers/%.o: ../RISCV/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\Application" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\Peripherals" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\Peripherals\Include" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\Peripherals\Source" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\RISCV\stubs" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\RISCV\drivers" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\RISCV\env_Eclipse" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\Utilities" -I"D:\OneDrive - mail.hfut.edu.cn\�ĵ�\GitHub\GD32VF103_Demo_Suites_HFUT_WH\Project\(2) GPIO_����_��ѯ��ѯ\Utilities\LCD_common" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


