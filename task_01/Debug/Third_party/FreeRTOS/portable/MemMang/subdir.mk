################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third_party/FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./Third_party/FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./Third_party/FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Third_party/FreeRTOS/portable/MemMang/%.o Third_party/FreeRTOS/portable/MemMang/%.su: ../Third_party/FreeRTOS/portable/MemMang/%.c Third_party/FreeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -c -I../Core/Inc -I"C:/Users/ajitp/OneDrive/Documents/Embedded_systems_courses/FREERTOS_COURSE/WORKSPACE/task_01/Third_party/FreeRTOS" -I"C:/Users/ajitp/OneDrive/Documents/Embedded_systems_courses/FREERTOS_COURSE/WORKSPACE/task_01/Third_party/FreeRTOS/include" -I"C:/Users/ajitp/OneDrive/Documents/Embedded_systems_courses/FREERTOS_COURSE/WORKSPACE/task_01/Third_party/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Third_party-2f-FreeRTOS-2f-portable-2f-MemMang

clean-Third_party-2f-FreeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./Third_party/FreeRTOS/portable/MemMang/heap_4.d ./Third_party/FreeRTOS/portable/MemMang/heap_4.o ./Third_party/FreeRTOS/portable/MemMang/heap_4.su

.PHONY: clean-Third_party-2f-FreeRTOS-2f-portable-2f-MemMang

