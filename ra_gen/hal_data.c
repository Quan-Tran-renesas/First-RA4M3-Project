/* generated HAL source file - do not edit */
#include "hal_data.h"
#ifndef CAN1_BAUD_SETTINGS_OVERRIDE
#define CAN1_BAUD_SETTINGS_OVERRIDE  (0)
#endif
#if CAN1_BAUD_SETTINGS_OVERRIDE
can_bit_timing_cfg_t g_can_bit_timing_cfg =
{
    .baud_rate_prescaler = 1,
    .time_segment_1 = 4,
    .time_segment_2 = 2,
    .synchronization_jump_width = 1
};
#else
can_bit_timing_cfg_t g_can_bit_timing_cfg =
		{
				/* Actual bitrate: 500000 Hz. Actual Bit Time Ratio: 73 %. */.baud_rate_prescaler =
						1 + 5 /* Division value of baud rate prescaler */,
				.time_segment_1 = 10, .time_segment_2 = 4,
				.synchronization_jump_width = 4, };
#endif

uint32_t g_can_mailbox_mask[CAN_NO_OF_MAILBOXES_g_can / 4] = { 0x1FFFFFFF,
#if CAN_NO_OF_MAILBOXES_g_can > 4
0x1FFFFFFF,
#endif
#if CAN_NO_OF_MAILBOXES_g_can > 8
0x1FFFFFFF,
0x1FFFFFFF,
#endif
#if CAN_NO_OF_MAILBOXES_g_can > 16
0x1FFFFFFF,
0x1FFFFFFF,
#endif
#if CAN_NO_OF_MAILBOXES_g_can > 24
0x1FFFFFFF,
0x1FFFFFFF,
#endif
		};

can_mailbox_t g_can_mailbox[CAN_NO_OF_MAILBOXES_g_can] = { { .mailbox_id = 0,
		.id_mode = CAN_ID_MODE_STANDARD, .mailbox_type = CAN_MAILBOX_TRANSMIT,
		.frame_type = CAN_FRAME_TYPE_REMOTE }, { .mailbox_id = 1, .id_mode =
		CAN_ID_MODE_STANDARD, .mailbox_type = CAN_MAILBOX_TRANSMIT,
		.frame_type = CAN_FRAME_TYPE_DATA }, { .mailbox_id = 2, .id_mode =
		CAN_ID_MODE_STANDARD, .mailbox_type = CAN_MAILBOX_RECEIVE, .frame_type =
		CAN_FRAME_TYPE_DATA, }, { .mailbox_id = 3, .id_mode =
		CAN_ID_MODE_STANDARD, .mailbox_type = CAN_MAILBOX_RECEIVE, .frame_type =
		CAN_FRAME_TYPE_DATA },
#if CAN_NO_OF_MAILBOXES_g_can > 4
    {
        .mailbox_id              =  4,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  5,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  6,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  7,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
#endif
#if CAN_NO_OF_MAILBOXES_g_can > 8
    {
        .mailbox_id              =  8,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  9,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  10,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  11,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  12,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA,
    },
    {
        .mailbox_id              =  13,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  14,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  15,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
#endif
#if CAN_NO_OF_MAILBOXES_g_can > 16
    {
        .mailbox_id              =  16,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },

    {
        .mailbox_id              =  17,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  18,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  19,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  20,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  21,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  22,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA,
    },
    {
        .mailbox_id              =  23,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
#endif
#if CAN_NO_OF_MAILBOXES_g_can > 24
    {
        .mailbox_id              =  24,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  25,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  26,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  27,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  28,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  29,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  30,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  31,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    }
#endif
		};

#if CAN_CFG_FIFO_SUPPORT
const can_fifo_interrupt_cfg_t g_can_fifo_int_cfg =
{
    .fifo_int_mode          = CAN_FIFO_INTERRUPT_MODE_RX_EVERY_FRAME | CAN_FIFO_INTERRUPT_MODE_TX_EVERY_FRAME,
    .rx_fifo_irq             = VECTOR_NUMBER_CAN1_FIFO_RX,
    .tx_fifo_irq             = VECTOR_NUMBER_CAN1_FIFO_TX,
};

can_rx_fifo_cfg_t g_can_rx_fifo_cfg =
{
    .rx_fifo_mask1 = 0x1FFFFFFF,
    .rx_fifo_mask2 = 0x1FFFFFFF,

    .rx_fifo_id1 =
    {
        .mailbox_id              =  0,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_REMOTE
    },

    .rx_fifo_id2 =
    {
        .mailbox_id              =  0,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_REMOTE
    },
};
#endif

const can_extended_cfg_t g_can_extended_cfg = { .clock_source =
		CAN_CLOCK_SOURCE_PCLKB, .p_mailbox_mask = g_can_mailbox_mask,
		.p_mailbox = g_can_mailbox, .global_id_mode =
				CAN_GLOBAL_ID_MODE_STANDARD, .mailbox_count =
				CAN_NO_OF_MAILBOXES_g_can, .message_mode =
				CAN_MESSAGE_MODE_OVERWRITE,
#if CAN_CFG_FIFO_SUPPORT
    .p_fifo_int_cfg         = &g_can_fifo_int_cfg,
    .p_rx_fifo_cfg          = &g_can_rx_fifo_cfg,
#else
		.p_fifo_int_cfg = NULL, .p_rx_fifo_cfg = NULL,
#endif
		};

can_instance_ctrl_t g_can_ctrl;
const can_cfg_t g_can_cfg = { .channel = 1, .p_bit_timing =
		&g_can_bit_timing_cfg, .p_callback = can_callback, .p_extend =
		&g_can_extended_cfg, .p_context = NULL, .ipl = (2),
#if defined(VECTOR_NUMBER_CAN1_MAILBOX_TX)
    .tx_irq             = VECTOR_NUMBER_CAN1_MAILBOX_TX,
#else
		.tx_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_CAN1_MAILBOX_RX)
    .rx_irq             = VECTOR_NUMBER_CAN1_MAILBOX_RX,
#else
		.rx_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_CAN1_ERROR)
    .error_irq             = VECTOR_NUMBER_CAN1_ERROR,
#else
		.error_irq = FSP_INVALID_VECTOR,
#endif
		};
/* Instance structure to use this module. */
const can_instance_t g_can = { .p_ctrl = &g_can_ctrl, .p_cfg = &g_can_cfg,
		.p_api = &g_can_on_can };
void g_hal_init(void) {
	g_common_init();
}
