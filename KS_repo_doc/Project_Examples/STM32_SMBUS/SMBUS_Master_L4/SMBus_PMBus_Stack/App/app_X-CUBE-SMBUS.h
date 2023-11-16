
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_X-CUBE-SMBUS.h
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "stm32_SMBUS_stack.h"

extern SMBUS_StackHandleTypeDef context;
extern SMBUS_StackHandleTypeDef *pcontext;

void MX_SMBus_PMBus_Stack_Process(void);
void MX_SMBus_PMBus_Stack_Init(void);
void MX_STACK_SMBUS_Init(void);
void MX_SMBUS_Error_Check( SMBUS_StackHandleTypeDef *pStackContext);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
