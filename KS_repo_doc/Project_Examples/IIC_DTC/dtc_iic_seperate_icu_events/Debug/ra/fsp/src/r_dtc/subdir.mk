################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_dtc/r_dtc.c 

C_DEPS += \
./ra/fsp/src/r_dtc/r_dtc.d 

OBJS += \
./ra/fsp/src/r_dtc/r_dtc.o 

SREC += \
dtc_iic_seperate_icu_events.srec 

MAP += \
dtc_iic_seperate_icu_events.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_dtc/%.o: ../ra/fsp/src/r_dtc/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM4 -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/src" -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/ra/fsp/inc" -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/ra/fsp/inc/api" -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/ra/fsp/inc/instances" -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/ra_gen" -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/ra_cfg/fsp_cfg/bsp" -I"C:/Users/tuan.nguyen-minh/e2_studio/workspace/dma_dtc_iic/ra_cfg/fsp_cfg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

