/***********************************************************************************************************************
 * File Name    : hal_entry.c
 * Description  : Contains data structures and functions used in hal_entry.c.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
#include "common_utils.h"

/*******************************************************************************************************************//**
 * @addtogroup CAN_EP
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define WAIT_TIME                       (5000U)            //wait time value
#define CAN_DESTINATION_MAILBOX_3       (24U)          	   //destination mail box number
#define CAN_MAILBOX_NUMBER_0            (0U)               //mail box number
#define CAN_FRAME_TRANSMIT_DATA_BYTES   (8U)               //data length
#define ZERO                            (0U)
#define NULL_CHAR                       ('\0')
#define RED                             (0x400)
#define BLUE                            (0x40F)
#define GREEN                           (0x404)

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
/* Flags, set from Callback function */
fsp_err_t err = FSP_SUCCESS;
static volatile bool b_can_tx = false;                  //CAN transmission status
static volatile bool b_can_rx = false;                  //CAN receive status
static volatile bool b_can_err = false;                 //CAN error status
static volatile bool printLED = false;                  //printLED option status
/* CAN frames for tx and rx */
static can_frame_t g_can_tx_frame = {RESET_VALUE};      //CAN transmit frame
static can_frame_t g_can_rx_frame = {RESET_VALUE};      //CAN receive frame

uint8_t rtt_led_selection = 0;  //Status of LED selection by user
uint8_t rtt_freq_selection = 0; //Status of Frequency selection by user
static bool sw_board_selection = 0; //Status of Frequency selection by user

uint8_t can_tx_msg[CAN_FRAME_TRANSMIT_DATA_BYTES] = "";        //data to be load in tx_frame while transmitting
uint8_t can_rx_msg[CAN_FRAME_TRANSMIT_DATA_BYTES] = "";       	  //data to be load in rx_frame while acknowledging
char rtt_input_buf[BUFFER_SIZE_DOWN] = {NULL_CHAR,};
char rtt_input_buf1[BUFFER_SIZE_DOWN] = {NULL_CHAR,};

/***********************************************************************************************************************
 * Private local functions
 **********************************************************************************************************************/
static void can_deinit(void);
void R_BSP_WarmStart(bsp_warm_start_event_t event);
void can_transmitter_board();
void can_receiver_board();
void blink_led(bsp_io_port_pin_t pin, uint8_t rec);

/*******************************************************************************************************************//**
 * The RA Configuration tool generates main() and uses it to generate threads if an RTOS is used.  This function is
 * called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    fsp_pack_version_t version = {RESET_VALUE};
    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Example Project information printed on the Console */
    APP_PRINT(BANNER_INFO, EP_VERSION, version.version_id_b.major, version.version_id_b.minor, version.version_id_b.patch );
    APP_PRINT("\r\nThis project demonstrates the basic functionality of CAN module on Renesas RA MCUs using 2 RA boards."
            "\r\nOn pressing any key on the RTTViewer, data is transmitted from Board1 to Board2."
            "\r\nOn reception, Board2 displays the received data on the RTTViewer. Board2, then, transmits the"
            "\r\nframed data back to Board1. On successful transmission, Board1 prints the data on to the RTTViewer.\r\n");

#if defined (BOARD_RA2A1_EK)
    err = R_CGC_Open (&g_cgc0_ctrl, &g_cgc0_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nCGC Open API failed");
        APP_ERR_TRAP(err);
    }
    err = R_CGC_ClockStart (&g_cgc0_ctrl, CGC_CLOCK_MAIN_OSC, NULL);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nCGC ClockStart API failed");
        APP_ERR_TRAP(err);
    }
#endif
    /* Initialize CAN module */
    err = R_CAN_Open(&g_can_ctrl, &g_can_cfg);
    /* Error trap */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nCAN Open API failed");
        APP_ERR_TRAP(err);
    }

    APP_PRINT("\r\nTo start CAN transmission, please enter any key on RTTViewer\r\n");

    /* Define the ID, Data type, Data length in which the board will send the data to */
    g_can_tx_frame.id = CAN_DESTINATION_MAILBOX_3;
    g_can_tx_frame.type = CAN_FRAME_TYPE_DATA;
    g_can_tx_frame.data_length_code = CAN_FRAME_TRANSMIT_DATA_BYTES;

    /* copy the tx data frame with TX_MSG */
    memcpy((uint8_t*)&g_can_tx_frame.data[ZERO], (uint8_t*)&can_tx_msg[ZERO], CAN_FRAME_TRANSMIT_DATA_BYTES);

   /* Define type of board*/
	APP_PRINT("\r\n Define your board: (Press S2 to switch board)");
	APP_PRINT("\r\n Transmitter board.");
	APP_PRINT("\r\n Receiver board. ( Default )\n");

	/* Loop */
    while (true)
    {
    	if (sw_board_selection == 1)
    	{
    		can_transmitter_board();
    		if (!R_BSP_PinRead((bsp_io_port_pin_t) BSP_IO_PORT_00_PIN_06))
    		{
    	        /* Preventing button hold too long */
    			while(!R_BSP_PinRead(((bsp_io_port_pin_t) BSP_IO_PORT_00_PIN_06)));

    			sw_board_selection = false;
    	        APP_PRINT("\r\n Change to Receiver Board \n");
    	        /* Turn off all LED */
    	        R_BSP_PinAccessEnable();
    			R_BSP_PinWrite((bsp_io_port_pin_t) RED  , BSP_IO_LEVEL_LOW);
    			R_BSP_PinWrite((bsp_io_port_pin_t) BLUE , BSP_IO_LEVEL_LOW);
    			R_BSP_PinWrite((bsp_io_port_pin_t) GREEN, BSP_IO_LEVEL_LOW);
    			R_BSP_PinAccessDisable();

    		}
    	}
    	else
    	{
    		can_receiver_board();
    		if (!R_BSP_PinRead((bsp_io_port_pin_t) BSP_IO_PORT_00_PIN_06))
    		{
    	        /* Preventing button hold too long */
    			while(!R_BSP_PinRead(((bsp_io_port_pin_t) BSP_IO_PORT_00_PIN_06)));

    			sw_board_selection = true;
    	        APP_PRINT("\r\n Change to Transmitter Board");
    	        /* Turn off all LED */
    	        R_BSP_PinAccessEnable();
    			R_BSP_PinWrite((bsp_io_port_pin_t) RED  , BSP_IO_LEVEL_LOW);
    			R_BSP_PinWrite((bsp_io_port_pin_t) BLUE , BSP_IO_LEVEL_LOW);
    			R_BSP_PinWrite((bsp_io_port_pin_t) GREEN, BSP_IO_LEVEL_LOW);
    			R_BSP_PinAccessDisable();

    			/* Reset bit printLED */
    			printLED = false;

    		}
    	}
    }
}

void can_transmitter_board()
{
	/* Print text once */
	if (printLED == false)
	{
		APP_PRINT("\r\n\n Please enter the LED's board you want to set:");
		APP_PRINT("\r\n 1. Enter 1 to select RED");
		APP_PRINT("\r\n 2. Enter 2 to select GREEN");
		APP_PRINT("\r\n 3. Enter 3 to select BLUE");
		APP_PRINT("\r\n Your selection is: \n ");
		printLED = true;
	}

    uint32_t time_out = WAIT_TIME;
    /* Check for user input */
	if (APP_CHECK_DATA && rtt_led_selection == 0)
	{
		APP_READ(rtt_input_buf);
		rtt_led_selection = (uint8_t) atoi(rtt_input_buf);
        switch (rtt_led_selection)
        {
          	case(1):
				{
            		memcpy(&can_tx_msg[0],"RED  ",5);
            		APP_PRINT("\r\n LED1 is selected.");
            		break;
				}
           	case(2):
				{
            		memcpy(&can_tx_msg[0],"GREEN",5);
            		APP_PRINT("\r\n LED2 is selected.");
            		break;
				}
           	case(3):
				{
            		memcpy(&can_tx_msg[0],"BLUE ",5);
            		APP_PRINT("\r\n LED3 is selected.");
            		break;
				}
           	default:
				{
           			APP_ERR_PRINT("\r\n Wrong data input");
           			rtt_led_selection = 0;
           			break;
				}
         }
        APP_PRINT("\r\n Please enter frequency for blinking LED on your board:");

	}
	/* After selecting the LED continue to choose the frequency */
	else if (APP_CHECK_DATA && rtt_led_selection != 0)
    {
        /* read data from RTT */
        APP_READ(rtt_input_buf);

        APP_PRINT("\r\n Transmitting the data");
        /* Input data from RTT to can_tx_msg */
        memcpy((uint8_t*)&can_tx_msg[5],(uint8_t*)&rtt_input_buf[0],1);

        /* transmit the data from mail box #0 with tx_frame */
        memcpy((uint8_t*)&g_can_tx_frame.data[ZERO], (uint8_t*)&can_tx_msg, 8);


        err = R_CAN_Write(&g_can_ctrl, CAN_MAILBOX_NUMBER_0, &g_can_tx_frame);
        /* Error trap */
        if (FSP_SUCCESS != err)
        {
            APP_ERR_PRINT("\r\n CAN Write API FAILED");
            can_deinit();
            APP_ERR_TRAP(err);
        }

        /* Wait for transmit flag bit to set */
        while ((true != b_can_tx) && (--time_out));
        if (RESET_VALUE == time_out)
        {
            APP_ERR_PRINT("CAN transmission failed due to timeout");
            APP_ERR_TRAP(true);
        }

        /* Reset flag bit */
        b_can_tx = false;
        printLED = false;
        APP_PRINT("\r\n CAN transmission is successful!!");
        memset(rtt_input_buf,NULL_CHAR,BUFFER_SIZE_DOWN);

        /* Reset LED selection */
        rtt_led_selection = 0;
    }
	else if (!R_BSP_PinRead((bsp_io_port_pin_t) BSP_IO_PORT_00_PIN_05))
	{
        while(!R_BSP_PinRead(((bsp_io_port_pin_t) BSP_IO_PORT_00_PIN_05)));
    	memcpy((uint8_t*)&g_can_tx_frame.data[ZERO], (uint8_t*)"RED  5   ", 8);
        err = R_CAN_Write(&g_can_ctrl, CAN_MAILBOX_NUMBER_0, &g_can_tx_frame);
        APP_PRINT("\r\n Button Pressed");

	}
}

void can_receiver_board()
{
    static uint32_t pin = 0;
    static uint8_t rec = 0;
    /* check if receive flag is set */
    if (true == b_can_rx)
    {
        /* Reset flag bit */
        b_can_rx = false;
        APP_PRINT("\r\n CAN received the data : %s\r\n", &g_can_rx_frame.data);

        /* if received data is same as transmitted data then acknowledge with RX_MSG as received successful*/
        if (RESET_VALUE == strncmp((char*)&g_can_rx_frame.data[ZERO], "RED", 3))
        {
            APP_PRINT("\r\n Received 'RED', blinking RED LED with freq of %d Hz'\r\n",(uint8_t)g_can_rx_frame.data[5] - 0x30);
            /* Define which LED to blink and what frequency */
            pin = RED;
            rec = (uint8_t) (g_can_rx_frame.data[5] - 0x30);

            /* Turn off the remaining LED */
	        R_BSP_PinAccessEnable();
			R_BSP_PinWrite((bsp_io_port_pin_t) BLUE , BSP_IO_LEVEL_LOW);
			R_BSP_PinWrite((bsp_io_port_pin_t) GREEN, BSP_IO_LEVEL_LOW);
			R_BSP_PinAccessDisable();
        }
        /* check if received data is same as rx_msg then received an acknowledge for the transfer of data successful */
        else if (RESET_VALUE == strncmp((char*)&g_can_rx_frame.data[ZERO],"BLUE", 4))
        {
            APP_PRINT("\r\n Received 'BLUE', blinking BLUE LED with freq of %d Hz'\r\n",(uint8_t)g_can_rx_frame.data[5] - 0x30);
            /* Define which LED to blink and what frequency */
            pin = BLUE;
            rec = (uint8_t) (g_can_rx_frame.data[5] - 0x30);

            /* Turn off the remaining LED */
	        R_BSP_PinAccessEnable();
			R_BSP_PinWrite((bsp_io_port_pin_t) RED  , BSP_IO_LEVEL_LOW);
			R_BSP_PinWrite((bsp_io_port_pin_t) GREEN, BSP_IO_LEVEL_LOW);
			R_BSP_PinAccessDisable();
        }
        else if (RESET_VALUE == strncmp((char*)&g_can_rx_frame.data[ZERO],"GREEN", 5))
        {
            APP_PRINT("\r\n Received 'GREEN', blinking GREEN LED with freq of %d Hz'\r\n",(uint8_t)g_can_rx_frame.data[5] - 0x30);
            /* Define which LED to blink and what frequency */
            pin = GREEN;
            rec = (uint8_t) (g_can_rx_frame.data[5] - 0x30);

            /* Turn off the remainning LED */
	        R_BSP_PinAccessEnable();
			R_BSP_PinWrite((bsp_io_port_pin_t) RED  , BSP_IO_LEVEL_LOW);
			R_BSP_PinWrite((bsp_io_port_pin_t) BLUE , BSP_IO_LEVEL_LOW);
			R_BSP_PinAccessDisable();
        }
        /* if no data match then data transfer failed */
        else
        {
            APP_ERR_PRINT("\r\nCAN data mismatch\r\n CAN operation failed\r\n");
            APP_ERR_TRAP(true);
        }
        /* Reset the rx frame data */
        memset((uint8_t*)&g_can_rx_frame.data[ZERO],RESET_VALUE,CAN_FRAME_TRANSMIT_DATA_BYTES);
    }
    /* re initializing time out value */
    blink_led(pin,rec);
}
/* Function to blink LED */
void blink_led(bsp_io_port_pin_t pin, uint8_t rec)
{
	R_BSP_PinAccessEnable();
	/* Set the blink frequency (must be <= bsp_delay_units */
	uint32_t freq_in_hz = rec;

	/* Calculate the delay in terms of bsp_delay_units */
	uint32_t delay = BSP_DELAY_UNITS_MILLISECONDS / freq_in_hz;

	if (rec == 0) R_BSP_PinWrite((bsp_io_port_pin_t) pin, BSP_IO_LEVEL_LOW);
	else
	{
		R_BSP_PinWrite((bsp_io_port_pin_t) pin , BSP_IO_LEVEL_LOW);
		R_BSP_SoftwareDelay(delay, BSP_DELAY_UNITS_MILLISECONDS);
		R_BSP_PinWrite((bsp_io_port_pin_t) pin , BSP_IO_LEVEL_HIGH);
		R_BSP_SoftwareDelay(delay, BSP_DELAY_UNITS_MILLISECONDS);
	}
	R_BSP_PinAccessDisable();
}

/*******************************************************************************************************************//**
 * This function is called when an CAN event is occurred and SET the respective flags.
 **********************************************************************************************************************/
void can_callback(can_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case CAN_EVENT_TX_COMPLETE:
        {
            b_can_tx = true;        //set flag bit
            break;
        }

        case CAN_EVENT_RX_COMPLETE:
        {
            b_can_rx = true;
            memcpy(&g_can_rx_frame, &p_args->frame, sizeof(can_frame_t));  //copy the received data to rx_frame
            break;
        }

        case CAN_EVENT_MAILBOX_MESSAGE_LOST:    //overwrite/overrun error event
        case CAN_EVENT_BUS_RECOVERY:            //Bus recovery error event
        case CAN_EVENT_ERR_BUS_OFF:             //error Bus Off event
        case CAN_EVENT_ERR_PASSIVE:             //error passive event
        case CAN_EVENT_ERR_WARNING:             //error warning event
        case CAN_EVENT_ERR_BUS_LOCK:            //error bus lock
        case CAN_EVENT_ERR_CHANNEL:             //error channel
        case CAN_EVENT_ERR_GLOBAL:              //error global
        case CAN_EVENT_TX_ABORTED:              //error transmit abort
        case CAN_EVENT_TX_FIFO_EMPTY:           //error transmit FIFO is empty
        case CAN_EVENT_FIFO_MESSAGE_LOST:       //error FIFO message lost
        {
            b_can_err = true;                   //set flag bit
            break;
        }

    }
}

/*******************************************************************************************************************//**
 * @brief       This function is to de-initializes the CAN module
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
static void can_deinit(void)
{
    err = FSP_SUCCESS;
    err = R_CAN_Close(&g_can_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n **CAN Close API failed**");
    }
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event) {
    if (BSP_WARM_START_POST_C == event) {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    }
}

/*******************************************************************************************************************//**
 * @} (end defgroup CAN_EP)
 **********************************************************************************************************************/
