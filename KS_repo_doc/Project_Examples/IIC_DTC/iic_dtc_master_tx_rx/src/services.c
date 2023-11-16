/*
 * services.c
 *
 *  Created on: Jul 27, 2023
 *      Author: tuan.nguyen-minh
 */
#include <services.h>

uint8_t g_slave_rx_buf[BUF_LEN];

uint8_t g_slave_tx_buf[BUF_LEN];

uint8_t g_dtc_rx_full_log[BUF_LEN];

uint8_t g_dtc_tx_complete_log[BUF_LEN];

uint8_t g_log_buf[BUF_LEN] = {0xa0, 0x20, 0x30, 0x80, 0x50 };

uint8_t write_buffer[BUF_LEN] = {0x0a, 0x02, 0x03, 0x08, 0x05};

fsp_err_t init_i2C_driver(void)
{
    fsp_err_t err = FSP_SUCCESS;

    err = R_IIC_MASTER_Open(&g_i2c_master_ctrl, &g_i2c_master_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Open slave I2C channel */
    err = R_IIC_SLAVE_Open(&g_i2c_slave_ctrl, g_i2c_slave.p_cfg);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        /* Slave Open unsuccessful closing master module */

        if (FSP_SUCCESS !=  R_IIC_MASTER_Close(&g_i2c_slave_ctrl))
        {
            /* Display failure message in RTT */
        }
    }

    return err;
}
