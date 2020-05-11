################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/system_stm32f0xx.c 

S_UPPER_SRCS += \
../system/src/cmsis/startup_stm32f072xb.S 

OBJS += \
./system/src/cmsis/startup_stm32f072xb.o \
./system/src/cmsis/system_stm32f0xx.o 

S_UPPER_DEPS += \
./system/src/cmsis/startup_stm32f072xb.d 

C_DEPS += \
./system/src/cmsis/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/%.o: ../system/src/cmsis/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -x assembler-with-cpp -DDEBUG -DSTM32F072xB -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F072 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"G:\Meine Ablage\Projekte\Reflow Oven\firmware\workspace\ReflowOvenFirmware_V1.0\system\include\STM32F0xx" -I"../system/include" -I"../system/include/cmsis" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/cmsis/%.o: ../system/src/cmsis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F072xB -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F072 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"G:\Meine Ablage\Projekte\Reflow Oven\firmware\workspace\ReflowOvenFirmware_V1.0\system\include\STM32F0xx" -I"../system/include" -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


