/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (5)
#endif
/* ISR prototypes */
void can_error_isr(void);
void can_rx_isr(void);
void can_tx_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_CAN1_ERROR ((IRQn_Type) 0) /* CAN1 ERROR (Error interrupt) */
#define CAN1_ERROR_IRQn          ((IRQn_Type) 0) /* CAN1 ERROR (Error interrupt) */
#define VECTOR_NUMBER_CAN1_MAILBOX_RX ((IRQn_Type) 1) /* CAN1 MAILBOX RX (Reception complete interrupt) */
#define CAN1_MAILBOX_RX_IRQn          ((IRQn_Type) 1) /* CAN1 MAILBOX RX (Reception complete interrupt) */
#define VECTOR_NUMBER_CAN1_MAILBOX_TX ((IRQn_Type) 2) /* CAN1 MAILBOX TX (Transmission complete interrupt) */
#define CAN1_MAILBOX_TX_IRQn          ((IRQn_Type) 2) /* CAN1 MAILBOX TX (Transmission complete interrupt) */
#define VECTOR_NUMBER_CAN1_FIFO_RX ((IRQn_Type) 3) /* CAN1 FIFO RX (Receive FIFO interrupt) */
#define CAN1_FIFO_RX_IRQn          ((IRQn_Type) 3) /* CAN1 FIFO RX (Receive FIFO interrupt) */
#define VECTOR_NUMBER_CAN1_FIFO_TX ((IRQn_Type) 4) /* CAN1 FIFO TX (Transmit FIFO interrupt) */
#define CAN1_FIFO_TX_IRQn          ((IRQn_Type) 4) /* CAN1 FIFO TX (Transmit FIFO interrupt) */
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
