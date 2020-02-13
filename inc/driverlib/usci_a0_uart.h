/*
 * usci_a0_uart.h
 *
 *  Created on: 2020年2月10日
 *      Author: 90342
 *  Fixed on :  2020-02-13 22:14
 *      Author: art-j <jjw903427521@gmail.com>
 */

#ifndef INC_DRIVERLIB_USCI_A0_UART_H_
#define INC_DRIVERLIB_USCI_A0_UART_H_

#include <stdio.h>
#include <string.h>
//外部函数声明

extern void usci_a0_uart_init(void);
extern unsigned char usci_a0_uart_transmit_frame( unsigned char *p_buff, unsigned char num);
extern unsigned char usci_a0_uart_receive_frame( unsigned char *p_buff, unsigned char num);
extern void usci_a0_uart_tx_isr_handle(void);
extern void usci_a0_uart_rx_isr_handle(void);

extern int fputc(int _c, register FILE *_fp);
extern int fputs(const char *_ptr, register FILE *_fp);

#endif /* INC_DRIVERLIB_USCI_A0_UART_H_ */
