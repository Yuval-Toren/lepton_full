################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Yuval/workspace/Psyphas/Src/dma.c \
C:/Users/Yuval/workspace/Psyphas/Src/gpio.c \
C:/Users/Yuval/workspace/Psyphas/Src/i2c.c \
C:/Users/Yuval/workspace/Psyphas/Src/main.c \
C:/Users/Yuval/workspace/Psyphas/Src/spi.c \
C:/Users/Yuval/workspace/Psyphas/Src/stm32f4xx_hal_msp.c \
C:/Users/Yuval/workspace/Psyphas/Src/stm32f4xx_it.c \
C:/Users/Yuval/workspace/Psyphas/Src/usart.c 

OBJS += \
./Application/User/dma.o \
./Application/User/gpio.o \
./Application/User/i2c.o \
./Application/User/main.o \
./Application/User/spi.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_it.o \
./Application/User/usart.o 

C_DEPS += \
./Application/User/dma.d \
./Application/User/gpio.d \
./Application/User/i2c.d \
./Application/User/main.d \
./Application/User/spi.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_it.d \
./Application/User/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/dma.o: C:/Users/Yuval/workspace/Psyphas/Src/dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/gpio.o: C:/Users/Yuval/workspace/Psyphas/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/i2c.o: C:/Users/Yuval/workspace/Psyphas/Src/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: C:/Users/Yuval/workspace/Psyphas/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/spi.o: C:/Users/Yuval/workspace/Psyphas/Src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: C:/Users/Yuval/workspace/Psyphas/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: C:/Users/Yuval/workspace/Psyphas/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usart.o: C:/Users/Yuval/workspace/Psyphas/Src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Yuval/workspace/Psyphas/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Include" -I"C:/Users/Yuval/workspace/Psyphas/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Yuval/workspace/Psyphas/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


