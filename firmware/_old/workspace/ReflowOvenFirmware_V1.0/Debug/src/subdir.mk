################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f0xx_hal_msp.c \
../src/stm32f0xx_it.c 

OBJS += \
./src/main.o \
./src/stm32f0xx_hal_msp.o \
./src/stm32f0xx_it.o 

C_DEPS += \
./src/main.d \
./src/stm32f0xx_hal_msp.d \
./src/stm32f0xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F072xB -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F072 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"G:\Meine Ablage\Projekte\Reflow Oven\firmware\workspace\ReflowOvenFirmware_V1.0\system\include\STM32F0xx" -I"../system/include" -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


