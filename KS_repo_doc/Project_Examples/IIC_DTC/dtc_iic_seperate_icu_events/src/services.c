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

uint8_t g_log_buf[BUF_LEN] = {0xa0, 0x20, 0x30, 0x80, 0x50};

uint8_t write_buffer[BUF_LEN] = {0x0a, 0x02, 0x03, 0x08, 0x05};

fsp_err_t init_i2C_driver(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Open mater I2C channel */
    err = R_IIC_MASTER_Open(&g_i2c_master_ctrl, &g_i2c_master_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

//    R_ICU->IELSR_b[g_transfer1_ctrl.irq].IELS = 0x73U;


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

        g_transfer0_cfg.p_info->p_src = &g_log_buf;
        g_transfer0_cfg.p_info->p_dest = &g_dtc_rx_full_log;
        g_transfer0_cfg.p_info->length = 1;

        g_transfer0_ctrl.irq = 9;
        R_ICU->IELSR_b[g_transfer0_ctrl.irq].DTCE = 1U;
        R_ICU->IELSR_b[g_transfer0_ctrl.irq].IELS = 0x068U;
        R_DTC_Enable(&g_transfer0_ctrl);
        err = R_DTC_Open(&g_transfer0_ctrl, &g_transfer0_cfg);

    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        /* Slave Open unsuccessful closing master module */

        if (FSP_SUCCESS !=  R_DTC_Close(&g_transfer0_ctrl))
        {
            /* Display failure message in RTT */
        }
    }

    g_transfer1_cfg.p_info->p_src = &g_log_buf;
    g_transfer1_cfg.p_info->p_dest = &g_dtc_tx_complete_log;
    g_transfer1_cfg.p_info->length = 1;

    g_transfer1_ctrl.irq = 11;
    R_ICU->IELSR_b[g_transfer1_ctrl.irq].DTCE = 1U;
    R_ICU->IELSR_b[g_transfer1_ctrl.irq].IELS = 0x064U;

    R_DTC_Enable(&g_transfer1_ctrl);
    err = R_DTC_Open(&g_transfer1_ctrl, &g_transfer1_cfg);

    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        /* Slave Open unsuccessful closing master module */

        if (FSP_SUCCESS !=  R_DTC_Close(&g_transfer1_ctrl))
        {
            /* Display failure message in RTT */
        }
    }

    return err;
}
