/*
 * usci_a0_uart.h
 *
 *  Created on: 2020年2月10日
 *      Author: 90342
 */

#ifndef INC_DRIVERLIB_USCI_A0_UART_H_
#define INC_DRIVERLIB_USCI_A0_UART_H_

extern unsigned char usci_a0_uart_transmit_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num);
extern unsigned char usci_a0_uart_receive_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num);

extern void usci_a0_uart_tx_isr_handle(void);
extern void usci_a0_uart_rx_isr_handle(void);

extern void usci_a0_uart_init(void);




#endif /* INC_DRIVERLIB_USCI_A0_UART_H_ */
