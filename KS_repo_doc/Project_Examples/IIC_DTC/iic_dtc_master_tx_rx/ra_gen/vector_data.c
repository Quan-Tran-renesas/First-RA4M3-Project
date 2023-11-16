/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = iic_master_rxi_isr, /* IIC0 RXI (Receive data full) */
            [1] = iic_master_txi_isr, /* IIC0 TXI (Transmit data empty) */
            [2] = iic_master_tei_isr, /* IIC0 TEI (Transmit end) */
            [3] = iic_master_eri_isr, /* IIC0 ERI (Transfer error) */
            [4] = iic_slave_rxi_isr, /* IIC1 RXI (Receive data full) */
            [5] = iic_slave_txi_isr, /* IIC1 TXI (Transmit data empty) */
            [6] = iic_slave_tei_isr, /* IIC1 TEI (Transmit end) */
            [7] = iic_slave_eri_isr, /* IIC1 ERI (Transfer error) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_IIC0_RXI), /* IIC0 RXI (Receive data full) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_IIC0_TXI), /* IIC0 TXI (Transmit data empty) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_IIC0_TEI), /* IIC0 TEI (Transmit end) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_IIC0_ERI), /* IIC0 ERI (Transfer error) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_IIC1_RXI), /* IIC1 RXI (Receive data full) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_IIC1_TXI), /* IIC1 TXI (Transmit data empty) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_IIC1_TEI), /* IIC1 TEI (Transmit end) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_IIC1_ERI), /* IIC1 ERI (Transfer error) */
        };
        #endif
