################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LM35/LM35_app.c \
../HAL/LM35/LM35_program.c 

OBJS += \
./HAL/LM35/LM35_app.o \
./HAL/LM35/LM35_program.o 

C_DEPS += \
./HAL/LM35/LM35_app.d \
./HAL/LM35/LM35_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LM35/%.o: ../HAL/LM35/%.c HAL/LM35/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


