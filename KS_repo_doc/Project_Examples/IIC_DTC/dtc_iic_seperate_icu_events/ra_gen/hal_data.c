/* generated HAL source file - do not edit */
#include "hal_data.h"
dtc_instance_ctrl_t g_transfer1_ctrl;

#if (1 == 1)
transfer_info_t g_transfer1_info =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_DESTINATION,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_REPEAT,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0,
  .length = 0, };

#elif (1 > 1)
/* User is responsible to initialize the array. */
transfer_info_t g_transfer1_info[1];
#else
/* User must call api::reconfigure before enable DTC transfer. */
#endif

const dtc_extended_cfg_t g_transfer1_cfg_extend =
{ .activation_source = 9, };

const transfer_cfg_t g_transfer1_cfg =
{
#if (1 == 1)
  .p_info = &g_transfer1_info,
#elif (1 > 1)
    .p_info              = g_transfer1_info,
#else
    .p_info = NULL,
#endif
  .p_extend = &g_transfer1_cfg_extend, };

/* Instance structure to use this module. */
const transfer_instance_t g_transfer1 =
{ .p_ctrl = &g_transfer1_ctrl, .p_cfg = &g_transfer1_cfg, .p_api = &g_transfer_on_dtc };
dtc_instance_ctrl_t g_transfer0_ctrl;

#if (1 == 1)
transfer_info_t g_transfer0_info =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_DESTINATION,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_REPEAT,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0,
  .length = 5, };

#elif (1 > 1)
/* User is responsible to initialize the array. */
transfer_info_t g_transfer0_info[1];
#else
/* User must call api::reconfigure before enable DTC transfer. */
#endif

const dtc_extended_cfg_t g_transfer0_cfg_extend =
{ .activation_source = 11, };

const transfer_cfg_t g_transfer0_cfg =
{
#if (1 == 1)
  .p_info = &g_transfer0_info,
#elif (1 > 1)
    .p_info              = g_transfer0_info,
#else
    .p_info = NULL,
#endif
  .p_extend = &g_transfer0_cfg_extend, };

/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{ .p_ctrl = &g_transfer0_ctrl, .p_cfg = &g_transfer0_cfg, .p_api = &g_transfer_on_dtc };
iic_slave_instance_ctrl_t g_i2c_slave_ctrl;
const iic_slave_extended_cfg_t g_i2c_slave_extend =
{
/* Actual delay: 250 ns. */.clock_settings.brl_value = 15,
  .clock_settings.digital_filter_stages = 0, .clock_settings.cks_value = 0, };
const i2c_slave_cfg_t g_i2c_slave_cfg =
{ .channel = 1, .rate = I2C_SLAVE_RATE_STANDARD, .slave = 8, .general_call_enable = false, .addr_mode =
          I2C_SLAVE_ADDR_MODE_7BIT,
  .p_callback = i2c_slave_callback, .p_context = NULL,
#if defined(VECTOR_NUMBER_IIC1_RXI)
    .rxi_irq                 = VECTOR_NUMBER_IIC1_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_IIC1_TXI)
    .txi_irq                 = VECTOR_NUMBER_IIC1_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_IIC1_TEI)
    .tei_irq                 = VECTOR_NUMBER_IIC1_TEI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_IIC1_ERI)
    .eri_irq                 = VECTOR_NUMBER_IIC1_ERI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif
  .ipl = (11),
  .eri_ipl = (11), .clock_stretching_enable = true, .p_extend = &g_i2c_slave_extend, };
/* Instance structure to use this module. */
const i2c_slave_instance_t g_i2c_slave =
{ .p_ctrl = &g_i2c_slave_ctrl, .p_cfg = &g_i2c_slave_cfg, .p_api = &g_i2c_slave_on_iic };
iic_master_instance_ctrl_t g_i2c_master_ctrl;
const iic_master_extended_cfg_t g_i2c_master_extend =
{ .timeout_mode = IIC_MASTER_TIMEOUT_MODE_LONG, .timeout_scl_low = IIC_MASTER_TIMEOUT_SCL_LOW_DISABLED,
/* Actual calculated bitrate: 98945. Actual calculated duty cycle: 51%. */.clock_settings.brl_value = 15,
  .clock_settings.brh_value = 16, .clock_settings.cks_value = 4, };
const i2c_master_cfg_t g_i2c_master_cfg =
{ .channel = 0, .rate = I2C_MASTER_RATE_STANDARD, .slave = 8, .addr_mode = I2C_MASTER_ADDR_MODE_7BIT,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_tx = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_rx = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
  .p_callback = i2c_master_callback,
  .p_context = NULL,
#if defined(VECTOR_NUMBER_IIC0_RXI)
    .rxi_irq             = VECTOR_NUMBER_IIC0_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_IIC0_TXI)
    .txi_irq             = VECTOR_NUMBER_IIC0_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_IIC0_TEI)
    .tei_irq             = VECTOR_NUMBER_IIC0_TEI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_IIC0_ERI)
    .eri_irq             = VECTOR_NUMBER_IIC0_ERI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif
  .ipl = (12),
  .p_extend = &g_i2c_master_extend, };
/* Instance structure to use this module. */
const i2c_master_instance_t g_i2c_master =
{ .p_ctrl = &g_i2c_master_ctrl, .p_cfg = &g_i2c_master_cfg, .p_api = &g_i2c_master_on_iic };
void g_hal_init(void)
{
    g_common_init ();
}
