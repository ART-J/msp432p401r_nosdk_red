/*
 * usci_a0_uart.c
 *
 *  Created on: 2020年2月10日
 *      Author: 90342
 *  Fixed on :  2020-02-13 22:14
 *      Author: art-j <jjw903427521@gmail.com>
 */
//   MSP432P401  - eUSCI_A0 UART echo at 9600 baud using SMCLK = 12MHz
//
//                MSP432P401
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//            |     P1.3/UCA0TXD|----> PC (echo)
//            |     P1.2/UCA0RXD|<---- PC
//            |                 |
/*******************************************************************************/
#include <msp.h>
#include <inc/driverlib/usci_a0_uart.h>


#define SIZE 32

static unsigned char *uart_tx_buff = 0;
static unsigned char uart_rx_buff[SIZE] = {0};

static unsigned char uart_tx_num = 0;
static unsigned char uart_rx_num = 0;

//static unsigned char *uart_tx_buff;
//static unsigned char *uart_rx_buff;

//eUSCI_A0 UART echo at 9600 baud using SMCLK = 12MHz
/*******************************************************************************/
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
/*******************************************************************************/
//用于串口/ttl通信的芯片的UART函数
/*******************************************************************************/
//一个字符串
unsigned char usci_a0_uart_transmit_frame(unsigned char *p_buff, unsigned char num) //
{
    if (num == 0) return 1;
    if (UCA0STATW & UCBUSY) return 0;
    __disable_interrupt();
    UCA0IE |= UCTXIE;
    __enable_interrupt();
    uart_tx_buff = p_buff;
    uart_tx_num  = num-1;
    UCA0TXBUF = *uart_tx_buff;
    while (UCA0STATW & UCBUSY);
    return 1;
}
unsigned char uart_a0_uart_receive_frame(unsigned char *p_buff, unsigned char num)
{
    unsigned char cnt=0;
    if (num == 0 || uart_rx_num == 0) return 0;
    p_buff += uart_rx_num;
    __disable_interrupt();
    do {
        *--p_buff = uart_rx_buff[--uart_rx_num];
        cnt++;
    }while (uart_rx_num > 0);
    uart_rx_num = 0;
    __enable_interrupt();
    return cnt;
}
/*******************************************************************************/
//一个字符
inline void usci_a0_uart_tx_isr_handle(void)
{
    if (uart_tx_num != 0) {
        uart_tx_num--;
        uart_tx_buff++;
        UCA0TXBUF = *uart_tx_buff;
    }
    else {
        UCA0IFG &=~UCTXIFG;
        UCA0IE  &=~UCTXIE;
    }
}
inline void usci_a0_uart_rx_isr_handle(void)
{
    if (uart_rx_num == SIZE) {
        uart_rx_num = SIZE-1;
    }
    uart_rx_buff[uart_rx_num++] = UCA0RXBUF;
}
/*******************************************************************************/
/* Standard Includes */
//用于printf函数串口打印，可便于调试程序
/*******************************************************************************/
//一个字符
int fputc(int _c, register FILE *_fp)
{
  while(!(UCA0IFG&UCTXIFG));
  UCA0TXBUF = (unsigned char) _c;

  return((unsigned char)_c);
}
//一个字符串
int fputs(const char *_ptr, register FILE *_fp)
{
  unsigned int i, len;

  len = strlen(_ptr);

  for(i=0 ; i<len ; i++)
  {
    while(!(UCA0IFG&UCTXIFG));
    UCA0TXBUF = (unsigned char) _ptr[i];
  }
  return len;
}


