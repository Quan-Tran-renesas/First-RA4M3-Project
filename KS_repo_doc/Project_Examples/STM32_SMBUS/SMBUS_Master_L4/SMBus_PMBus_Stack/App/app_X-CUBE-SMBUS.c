
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_X-CUBE-SMBUS.c
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

#include "stm32_PMBUS_stack.h"
/* USER CODE END Header */

#include "app_X-CUBE-SMBUS.h"

void MX_SMBus_PMBus_Stack_Process()
{
  /* this function is a sanity check on the stack context */
  /* optional but may help implementation robustness */
  MX_SMBUS_Error_Check(pcontext);
/* USER CODE BEGIN 0 */
  HAL_SMBUS_DisableListen_IT(pcontext->Device);

  if (HAL_SMBUS_IsDeviceReady(pcontext->Device, (0x12 << 1), 2, 100) == HAL_OK) {
	STACK_SMBUS_HostCommand(pcontext, (st_command_t *)&PMBUS_COMMANDS_TEST[4],  (0x12 << 1), WRITE);
  }

  HAL_Delay(100);

  HAL_SMBUS_DisableListen_IT(pcontext->Device);

  if (HAL_SMBUS_IsDeviceReady(pcontext->Device, (0x12 << 1), 2, 100) == HAL_OK) {
	  STACK_SMBUS_HostCommand(pcontext, (st_command_t *) &PMBUS_COMMANDS_TEST[9],  (0x12 << 1), READ);
  }

  HAL_Delay(100);
/* USER CODE END 0 */
}

void MX_SMBus_PMBus_Stack_Init()
{
  uint32_t      index;
  uint8_t*      piobuf;

  MX_STACK_SMBUS_Init();

  piobuf = STACK_SMBUS_GetBuffer( pcontext );

  /* initializing the IO buffer */
  /* this part is optional */
  if (piobuf != NULL )
  {
    for (index = 0U; index < STACK_NBYTE_SIZE; index++)
    {
      piobuf[index] = (uint8_t)index;
    }
  }
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
}

