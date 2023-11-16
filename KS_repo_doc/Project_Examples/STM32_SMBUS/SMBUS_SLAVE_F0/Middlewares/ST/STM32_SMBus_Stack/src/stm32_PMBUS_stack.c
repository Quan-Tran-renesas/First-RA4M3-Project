/**
  ******************************************************************************
  * @file    stm32_PMBUS_stack.c
  * @author  MCD Application Team
  * @version V2.0.2
  * @date    31-Oct-2017
  * @brief   This file provides a set of functions needed to manage the PMBus
  *          on top of the SMBus stack.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_PMBUS_stack.h"
#include "stm32_SMBUS_stack.h"

/** @addtogroup STM32_PMBUS_STACK
  * @{
  */

/** @defgroup STM32_PMBUS_STACK_Constants
  * @{
  */

/* ----------- definition of PMBUS commands ---------------- */
st_command_t const PMBUS_COMMANDS_TEST[] =
{
  { 0, WRITE, 0, 0 },
  { 1, WRITE, 2, 0 },
  { 2, WRITE, 3, 0 },
  { 3, WRITE, 5, 0 },
  { 4, WRITE, 9, 0 },
  { 5, BLOCK_WRITE, 3, 0 },
  { 6, BLOCK_WRITE, 11, 0 },
  { 7, READ, 0, 1 },
  { 8, READ, 0, 2 },
  { 9, READ, 0, 4 },
  { 10, READ, 0, 8 },
  { 11, BLOCK_READ, 0, 4 },
  { 12, BLOCK_READ, 0, 11 },
  { 13, BLOCK_READ, 0, STACK_NBYTE_SIZE },
  { 14, BLOCK_WRITE, STACK_NBYTE_SIZE, 0 },
  { 15, PROCESS_CALL, 3, 2},
  { 16, BLK_PRC_CALL, 13, 9 },
  { 17, READ_OR_WRITE, 2, 2 },
  { 18, READ_OR_WRITE, 4, 4 },
  { 19, BLK_RD_OR_WR, 3, 1 },
  { 20, BLK_RD_OR_WR, 1, 3 }
};

/*
    dedicated command definitions for the extended command support
 */
st_command_t const EXTENDED_READ_BYTE = { PMBC_PMBUS_COMMAND_EXT, PROCESS_CALL, 2, 1 };
st_command_t const EXTENDED_READ_WORD = { PMBC_PMBUS_COMMAND_EXT, PROCESS_CALL, 2, 2 };
st_command_t const EXTENDED_WRITE_BYTE = { PMBC_PMBUS_COMMAND_EXT, WRITE, 3, 0 };
st_command_t const EXTENDED_WRITE_WORD = { PMBC_PMBUS_COMMAND_EXT, WRITE, 4, 0 };

/*
    dedicated command definition for the Zone read support
 */
st_command_t const ZONE_READ_COMMAND = { 0, PROCESS_CALL, 2, 2 };

/* Private define ------------------------------------------------------------*/
#define NOT_USED(p) ((void)(p))

/**
  * @}
  */

/** @defgroup STM32_PMBUS_STACK_Functions
  * @{
  */

/**
  * @brief  PMBUS master group command transmit, direction is implicitly write.
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the configuration information for the specified SMBUS.
  * @param  pCommand : description of the command to be transmitted, NULL for quick command
  * @param  address : device address
  * @param  last : last command in the group - STOP condition is transmitted if this flag is != 0
  * @retval SMBus stack return code
  */
HAL_StatusTypeDef STACK_PMBUS_HostCommandGroup(SMBUS_StackHandleTypeDef *pStackContext, st_command_t *pCommand,
    uint16_t address, uint8_t last)
{
  HAL_StatusTypeDef     result = STACK_ERROR;
  uint16_t              size;
  uint32_t              xFerOptions = SMBUS_FIRST_FRAME;

  /*
    First check status of the SMBUS - no transaction ongoing
  */
  if (( ((pStackContext->StateMachine) & SMBUS_SMS_ACTIVE_MASK) == 0U ) && ( ( pCommand->cmnd_query & WRITE ) == WRITE ) )
  {
    /*
    becoming master, not listening any more
    */
    HAL_SMBUS_DisableListen_IT( pStackContext->Device );

    if ( pCommand == NULL )
    {
      /*
        quick command case
        */
      size = 0U;
    }
    else
    {
      /*
      the command must support write mode, otherwise is unusable for grouping
      */

      pStackContext->OpMode = pCommand->cmnd_query & BLOCK_WRITE;

      /*
        Remembering the address and command code for case of further processing of non-trivial command
      */
      pStackContext->SlaveAddress = address;
      pStackContext->CurrentCommand = pCommand;

      /*
      First byte, the command code is transmitted
      */
      pStackContext->Buffer[0] = pCommand->cmnd_code;

      if ( pCommand->cmnd_query & BLOCK )
      {
        /*
            Block write with data size prepared in the buffer.
          */
        size = 2U + (uint16_t)(pStackContext->Buffer[1]);            /* 1 cmd code + 1 count + data size */
      }
      else
      {
        /*
        fixed size write
        */
        size = pCommand->cmnd_master_Tx_size;
      }

      xFerOptions |= ( pStackContext->StateMachine & SMBUS_SMS_PEC_ACTIVE );
      if ((pStackContext->StateMachine & SMBUS_SMS_PEC_ACTIVE ) == SMBUS_SMS_PEC_ACTIVE )
      {
        size += 1U;
      }
    }

    /*
      finishing transmission
     */
    if ( last != 0U )
    {
      xFerOptions |= SMBUS_LAST_FRAME_NO_PEC;
    }

    /*
      Initiating a transmission
      */
    pStackContext->StateMachine |= SMBUS_SMS_TRANSMIT;
    pStackContext->StateMachine &= ~SMBUS_SMS_READY;

    /*
      Sending the data and logging the result
      */
    result = HAL_SMBUS_Master_Transmit_IT( pStackContext->Device, address, pStackContext->Buffer, size, xFerOptions );
    if (result != HAL_OK )
    {
      pStackContext->StateMachine |= SMBUS_SMS_ERROR;
    }
  }
  return result;
}


/**
  * @brief  a version of the default SMBUS implementation with support for
  *       PMBus extended command
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the configuration information for the specified SMBUS.
  * @retval None
  */
void STACK_SMBUS_LocateCommand( SMBUS_StackHandleTypeDef *pStackContext )
{
  uint8_t       commandCode = pStackContext->Buffer[0];
#ifdef DENSE_CMD_TBL
  uint32_t      current, low, top;
#endif

#ifdef ARP
  if ( pStackContext->StateMachine & SMBUS_SMS_ARP_AM )
  {
    STACK_SMBUS_LocateCommandARP( pStackContext, commandCode );
  }
  else
#endif /* ARP treatment */

    if (commandCode == PMBC_PMBUS_COMMAND_EXT)
    {
      /*
        May not be exactly read byte, but the stack cannot know for sure
       */
      pStackContext->CurrentCommand = (st_command_t *)&EXTENDED_READ_BYTE;
    }
    else
    {
      /*
        Code searching for command based on command code
        */
#ifdef DENSE_CMD_TBL

      /*
        initializing the command code search - the table must have all commands sorted, but there may be gaps
       */
      low = 0U;
      top = pStackContext->CMD_tableSize - 1U;
      pStackContext->CurrentCommand = NULL;

      while ( top >= low )
      {
        /*
          Pick interval half
         */
        current = ( low + top ) >> 1U;
        if (pStackContext->CMD_table[current].cmnd_code == commandCode)
        {
          /*
            we have found our command
           */
          pStackContext->CurrentCommand = &(pStackContext->CMD_table[current]);
          return;
        }
        else if (pStackContext->CMD_table[current].cmnd_code < commandCode)
        {
          /*
            Look at upper half
          */
          low = current + 1U;
        }
        else
        {
          top = current - 1U;
        }
      }
#else
      /*
      Simple command table - command code equals the table index
      */
      pStackContext->CurrentCommand = &(pStackContext->CMD_table[commandCode]);

      /* a sanity check */
      if ( pStackContext->CurrentCommand->cmnd_code != commandCode )
      {
        pStackContext->CurrentCommand = NULL;
      }
#endif /* DENSE_CMD_TBL */
    }
}


#ifdef  PMBUS13 /* Zone commands were introduced in v1.3 */

/**
  * @brief  PMBUS zone write command transmit, direction is implicitly write.
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the configuration information for the specified SMBUS.
  * @param  pCommand : description of the command to be transmitted, NULL for quick command
  * @param  zone : the zone context in which the command executes
  * @retval SMBus stack return code
  */
HAL_StatusTypeDef STACK_PMBUS_MasterZoneWrite(SMBUS_StackHandleTypeDef *pStackContext, st_command_t *pCommand)
{
  HAL_StatusTypeDef     result = STACK_ERROR;
  uint16_t              size;
  uint32_t              xFerOptions = SMBUS_FIRST_FRAME;

  /*
    First check status of the SMBUS - no transaction ongoing, and that the command is write direction
  */
  if (( ((pStackContext->StateMachine) & SMBUS_SMS_ACTIVE_MASK) == 0U ) && ( ( pCommand->cmnd_query & WRITE ) == WRITE ) )
  {
    /*
    becoming master, not listening any more
    */
    HAL_SMBUS_DisableListen_IT( pStackContext->Device );

    if ( pCommand == NULL )
    {
      /*
        quick command case
        */
      size = 0U;
    }
    else
    {
      /*
      the command must support write mode, otherwise is unusable for zone
      */
      pStackContext->OpMode = pCommand->cmnd_query & BLOCK_WRITE;

      /*
        Remembering the address and command code for case of further processing of non-trivial command
      */
      pStackContext->SlaveAddress = SMBUS_ADDR_ZONE_WRITE;
      pStackContext->CurrentCommand = pCommand;

      /*
      First byte, the command code is transmitted
      */
      pStackContext->Buffer[0] = pCommand->cmnd_code;

      if ( pCommand->cmnd_query & BLOCK )
      {
        /*
            Block write with data size prepared in the buffer.
          */
        size = 2U + (uint16_t)(pStackContext->Buffer[1]);            /* 1 cmd code + 1 count + data size */
      }
      else
      {
        /*
        fixed size write
        */
        size = pCommand->cmnd_master_Tx_size;
      }

      xFerOptions |= ( pStackContext->StateMachine & SMBUS_SMS_PEC_ACTIVE );
      if ((pStackContext->StateMachine & SMBUS_SMS_PEC_ACTIVE ) == SMBUS_SMS_PEC_ACTIVE )
      {
        size += 1U;
      }
    }

    /*
      finishing transmission
     */
    xFerOptions |= SMBUS_LAST_FRAME_NO_PEC;

    /*
      Initiating a transmission
      */
    pStackContext->StateMachine |= SMBUS_SMS_TRANSMIT;
    pStackContext->StateMachine &= ~SMBUS_SMS_READY;

    /*
      Sending the data and logging the result
      */
    result = HAL_SMBUS_Master_Transmit_IT( pStackContext->Device, SMBUS_ADDR_ZONE_WRITE, pStackContext->Buffer, size,
                                           xFerOptions );
    if (result != HAL_OK )
    {
      pStackContext->StateMachine |= SMBUS_SMS_ERROR;
    }
  }
  return result;
}

/**
  * @brief  PMBUS zone config command transmit, direction is implicitly write.
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the configuration information for the specified SMBUS.
  * @param  address : address of the device to be configured
  * @param  zone : the zone context to be configured
  * @retval SMBus stack return code
  */
HAL_StatusTypeDef STACK_PMBUS_MasterZoneConfig(SMBUS_StackHandleTypeDef *pStackContext, uint16_t address,
    SMBUS_ZoneStateTypeDef *zone)
{
  pStackContext->Buffer[1] = zone->writeZone;
  pStackContext->Buffer[2] = zone->readZone;
  return STACK_SMBUS_HostCommand( pStackContext, (st_command_t *)&PMBUS_COMMANDS_TAB[PMBC_ZONE_CONFIG], address, WRITE );
}

/**
  * @brief  PMBUS zone active command transmit, direction is implicitly write.
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the configuration information for the specified SMBUS.
  * @param  zone : the zones to be activated
  * @retval SMBus stack return code
  */
HAL_StatusTypeDef STACK_PMBUS_MasterZoneActive(SMBUS_StackHandleTypeDef *pStackContext, SMBUS_ZoneStateTypeDef *zone)
{
  pStackContext->Buffer[1] = zone->activeWriteZone;
  pStackContext->Buffer[2] = zone->activeReadZone;
  return STACK_SMBUS_HostCommand( pStackContext, (st_command_t *)&PMBUS_COMMANDS_TAB[PMBC_ZONE_ACTIVE],
                                  SMBUS_ADDR_ZONE_WRITE, WRITE );
}

/**
  * @brief  PMBUS zone read command initiation, simple implementation limited to status retrieve from single page devices.
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the configuration information for the specified SMBUS.
  * @param  ccode : command control code
  * @param  mask : status mask
  * @retval SMBus stack return code
  */
HAL_StatusTypeDef STACK_PMBUS_MasterReadZoneStatus(SMBUS_StackHandleTypeDef *pStackContext, uint8_t ccode, uint8_t mask)
{
  HAL_StatusTypeDef     result = STACK_ERROR;

  /*
    First check status of the SMBUS - no transaction ongoing
   */
  if (((pStackContext->StateMachine) & SMBUS_SMS_ACTIVE_MASK) == 0U )
  {
    /*
      Becoming master, not listening any more
     */
    HAL_SMBUS_DisableListen_IT( pStackContext->Device );

    /*
      Remembering the address and command code for case of further processing of non-trivial command
    */
    pStackContext->SlaveAddress = SMBUS_ADDR_ZONE_READ;
    pStackContext->CurrentCommand = NULL;

    /*
      First byte, the command code is transmitted
    */
    pStackContext->Buffer[0] = ccode;
    pStackContext->Buffer[1] = mask;

    /*
      Initiating a transmission
     */
    pStackContext->StateMachine |= SMBUS_SMS_TRANSMIT;
    pStackContext->StateMachine &= ~SMBUS_SMS_READY;

    /*
      Sending the data and logging the result
     */
    result = HAL_SMBUS_Master_Transmit_IT( pStackContext->Device, SMBUS_ADDR_ZONE_READ, pStackContext->Buffer, 2U,
                                           SMBUS_FIRST_FRAME );
    if (result != HAL_OK )
    {
      pStackContext->StateMachine |= SMBUS_SMS_ERROR;
    }
  }
  return result;
}

/**
  * @brief  Implementation of Zone read continuation - Master side.
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the context information for the specified SMBUS stack.
  * @retval HAL_StatusTypeDef response code. STACK_OK if success, any other value means problem
  */
HAL_StatusTypeDef STACK_PMBUS_MasterZoneReadStatusCont(SMBUS_StackHandleTypeDef *pStackContext)
{
  HAL_StatusTypeDef     result = STACK_ERROR;

  result = HAL_SMBUS_Master_Receive_IT( pStackContext->Device, SMBUS_ADDR_ZONE_READ, pStackContext->Buffer, 2U,
                                        SMBUS_OTHER_FRAME );
  if (result != HAL_OK )
  {
    pStackContext->StateMachine |= SMBUS_SMS_ERROR;
  }
  return result;
}

/**
  * @brief  Callback function notifying slave about Zone read.
  * @param  pStackContext : Pointer to a SMBUS_StackHandleTypeDef structure that contains
  *                the context information for the specified SMBUS stack.
  * @param  number : Indicates if this command header, or read request
  * @retval HAL_StatusTypeDef response code. STACK_OK if success, any other value means problem
  */
__weak HAL_StatusTypeDef STACK_PMBUS_ZoneReadCallback( SMBUS_StackHandleTypeDef *pStackContext, uint8_t number )
{
  uint8_t ccc, mask;

  if ( number == 1U )
  {
    /* Command just received, here the device should read COMMAND CONTROL CODE and Mask*/
    ccc = pStackContext->Buffer[0];
    mask =  pStackContext->Buffer[1];
    NOT_USED(ccc);
    NOT_USED(mask);
  }
  else
  {
    /* Read phase of the Zone read - arbitarry number returned by example*/
    pStackContext->Buffer[1] = 0xA5U;
    pStackContext->Buffer[2] = pStackContext->OwnAddress;
  }

  /*
    Returning zero means no problem with execution, if reply is expected, then it must be placed to the IO buffer
   */
  return STACK_OK;
}
#endif  /* PMBUS13 */

/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
