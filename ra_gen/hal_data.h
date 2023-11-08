/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_can.h"
#include "r_can_api.h"
FSP_HEADER
/** CAN on CAN Instance. */
extern const can_instance_t g_can;
/** Access the CAN instance using these structures when calling API functions directly (::p_api is not used). */
extern can_instance_ctrl_t g_can_ctrl;
extern const can_cfg_t g_can_cfg;
extern const can_extended_cfg_t g_can_extended_cfg;

#ifndef can_callback
void can_callback(can_callback_args_t *p_args);
#endif
#define CAN_NO_OF_MAILBOXES_g_can (32)
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
