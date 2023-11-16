/*
 * services.h
 *
 *  Created on: Jul 27, 2023
 *      Author: tuan.nguyen-minh
 */

#ifndef SERVICES_H_
#define SERVICES_H_

#include "hal_data.h"

fsp_err_t init_i2C_driver(void);

#define BUF_LEN                 (0x05)

#define RESET_VALUE             (0x00)

extern uint8_t g_slave_rx_buf[BUF_LEN];

extern uint8_t g_slave_tx_buf[BUF_LEN];

extern uint8_t g_dtc_rx_full_log[BUF_LEN];

extern uint8_t g_dtc_tx_complete_log[BUF_LEN];

extern uint8_t g_log_buf[BUF_LEN];

extern uint8_t write_buffer[BUF_LEN];

#endif /* SERVICES_H_ */
