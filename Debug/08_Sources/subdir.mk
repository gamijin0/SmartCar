################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../08_Sources/isr.c \
../08_Sources/main.c 

OBJS += \
./08_Sources/isr.o \
./08_Sources/main.o 

C_DEPS += \
./08_Sources/isr.d \
./08_Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
08_Sources/%.o: ../08_Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/02_CPU" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/05_Driver/pwm" -I"D:\IntelligentVehicleProjects\K60_SmartCar_20160411\05_Driver\pit" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/05_Driver" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/05_Driver/gpio" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/05_Driver/uart" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/05_Driver/adc" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/03_MCU" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/04_Linker_File" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/06_App_Component" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/06_App_Component/speed" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/06_App_Component/light" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/06_App_Component/GyroAcce" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/06_App_Component/motor" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/07_Soft_Component" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/07_Soft_Component/control" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/07_Soft_Component/common" -I"D:/IntelligentVehicleProjects/K60_SmartCar_20160411/08_Sources" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


