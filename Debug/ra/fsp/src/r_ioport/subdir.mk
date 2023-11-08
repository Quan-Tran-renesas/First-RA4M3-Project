################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_ioport/r_ioport.c 

C_DEPS += \
./ra/fsp/src/r_ioport/r_ioport.d 

OBJS += \
./ra/fsp/src/r_ioport/r_ioport.o 

SREC += \
can_ek_ra4m3_EP_Q.srec 

MAP += \
can_ek_ra4m3_EP_Q.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_ioport/%.o: ../ra/fsp/src/r_ioport/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/src" -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/ra/fsp/inc" -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/ra/fsp/inc/api" -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/ra/fsp/inc/instances" -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/ra_gen" -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/ra_cfg/fsp_cfg/bsp" -I"C:/Users/a5146761/e2_studio/workspace/can_ek_ra4m3_EP_Q/ra_cfg/fsp_cfg" -I"." -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

