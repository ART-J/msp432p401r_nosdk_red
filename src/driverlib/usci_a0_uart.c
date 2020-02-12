/*
 * usci_a0_uart.c
 *
 *  Created on: 2020年2月10日
 *      Author: 90342
 */
#include <msp.h>



void usci_a0_uart_init(void)
{
    //   Configure UART pins
      P1SEL0 |= BIT2 | BIT3;                  // set 2-UART pin as second function

      __enable_interrupt();
      NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31); // Enable eUSCIA0 interrupt in NVIC module

      // Configure UART
      UCA0CTLW0 |= UCSWRST;
      UCA0CTLW0 |= UCSSEL__SMCLK;             // Put eUSCI in reset
      // Baud Rate calculation
      // 12000000/(16*9600) = 78.125
      // Fractional portion = 0.125
      // User's Guide Table 21-4: UCBRSx = 0x10
      // UCBRFx = int ( (78.125-78)*16) = 2
      UCA0BR0 = 78;                           // 12000000/16/9600
      UCA0BR1 = 0x00;
      UCA0MCTLW = 0x1000 | UCOS16 | 0x0020;

      UCA0CTLW0 &= ~UCSWRST;                  // Initialize eUSCI
      UCA0IE |= UCRXIE;

    //SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;   // Wake up on exit from ISR
}
static unsigned char *uart_tx_buff;
static unsigned char *uart_rx_buff;

static unsigned char uart_tx_num = 0;
static unsigned char uart_rx_num = 0;

unsigned char usci_a0_uart_transmit_frame(unsigned char *p_buff, unsigned char num)
{
    //if (UCA0IFG&UCTXIFG) return 0;
    __disable_interrupt();

    __enable_interrupt();
    uart_tx_buff = p_buff;
    uart_tx_num  = num;
    UCA0TXBUF = *uart_tx_buff++;
    while(!(UCA0IFG&UCTXIFG));
    return 1;
}

unsigned char usci_a0_uart_receive_frame(unsigned char *p_buff, unsigned char num)
{
   // if (UCA0STAT & UCBUSY) return 0;
    __disable_interrupt();

    __enable_interrupt();
    uart_rx_buff = p_buff;
    uart_rx_num  = num;
    UCA0TXBUF = 0xff;
   // while (UCA0STAT & UCBUSY);
    return 1;
}
inline void usci_a0_uart_rx_isr_handle(void)
{
    *uart_rx_buff++ = UCA0RXBUF;
    uart_rx_num--;
    if (uart_rx_num) {
        UCA0TXBUF = 0xff;
    } else {
        UCA0IFG &=~UCRXIFG;

    }
}

inline void usci_a0_uart_tx_isr_handle(void)
{
    UCA0RXBUF;
    uart_tx_num--;
    if (uart_tx_num) {
        UCA0TXBUF = *uart_tx_buff++;
    } else {
        UCA0IFG &=~UCTXIFG;

    }
}





