################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_SMBus_Stack/src/stm32_PMBUS_stack.c \
../Middlewares/ST/STM32_SMBus_Stack/src/stm32_SMBUS_stack.c 

OBJS += \
./Middlewares/ST/STM32_SMBus_Stack/src/stm32_PMBUS_stack.o \
./Middlewares/ST/STM32_SMBus_Stack/src/stm32_SMBUS_stack.o 

C_DEPS += \
./Middlewares/ST/STM32_SMBus_Stack/src/stm32_PMBUS_stack.d \
./Middlewares/ST/STM32_SMBus_Stack/src/stm32_SMBUS_stack.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_SMBus_Stack/src/%.o Middlewares/ST/STM32_SMBus_Stack/src/%.su Middlewares/ST/STM32_SMBus_Stack/src/%.cyclo: ../Middlewares/ST/STM32_SMBus_Stack/src/%.c Middlewares/ST/STM32_SMBus_Stack/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../SMBus_PMBus_Stack/Target -I../Middlewares/ST/STM32_SMBus_Stack/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_SMBus_Stack-2f-src

clean-Middlewares-2f-ST-2f-STM32_SMBus_Stack-2f-src:
	-$(RM) ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_PMBUS_stack.cyclo ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_PMBUS_stack.d ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_PMBUS_stack.o ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_PMBUS_stack.su ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_SMBUS_stack.cyclo ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_SMBUS_stack.d ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_SMBUS_stack.o ./Middlewares/ST/STM32_SMBus_Stack/src/stm32_SMBUS_stack.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_SMBus_Stack-2f-src

