################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../middleware/glm-0.9.8.2/glm/detail/glm.cpp 

OBJS += \
./middleware/glm-0.9.8.2/glm/detail/glm.o 

CPP_DEPS += \
./middleware/glm-0.9.8.2/glm/detail/glm.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/glm-0.9.8.2/glm/detail/%.o: ../middleware/glm-0.9.8.2/glm/detail/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/Shanty1/Downloads/Boilerplate/middleware/glad/include" -I"/Users/Shanty1/Downloads/Boilerplate/middleware/glfw/include" -I"/Users/Shanty1/Downloads/Boilerplate/middleware/glm-0.9.8.2" -I"/Users/Shanty1/Downloads/Boilerplate/middleware/stb" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


