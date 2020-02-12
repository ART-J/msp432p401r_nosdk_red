/*
 * vector.c
 *
 *  Created on: 2016-10-26
 *      Author: Jack Chen <redchenjs@live.com>
 *  Fixed on :  2018-05-25 11:14
 *      Author: art-j <jjw903427521@gmail.com>
 */

#include <inc/driverlib/usci_b3_spi.h>
#include <inc/driverlib/usci_b0_i2c.h>
#include <inc/driverlib/usci_a0_uart.h>
#include <msp.h>
//#include <inc/device/wdt.h>
uint8_t RXData = 0;
uint8_t TXData = 1;

void EUSCIA0_IRQHandler(void)
{
    if (UCA0IFG & UCRXIFG)
    {
        UCA0IFG &=~ UCRXIFG;            // Clear interrupt
        RXData = UCA0RXBUF;             // Clear buffer
    }
}
/***********************************************************************************************/
void EUSCIB3_IRQHandler(void)
{

	if (UCB3IFG & UCRXIFG)
	{
		usci_b3_spi_rx_isr_handle();
	}
	if (UCB3IFG & UCTXIFG)
	{
		usci_b3_spi_tx_isr_handle();
	}
}
/***********************************************************************************************/
void EUSCIB0_IRQHandler(void)
{

	if (UCB0IFG & UCRXIFG)
	{

		usci_b0_i2c_rx_isr_handle();
	}
	if (UCB0IFG & UCTXIFG)
	{
		usci_b0_i2c_tx_isr_handle();
	}
}
/**********************************************************************************/
//#pragma vector=WDT_VECTOR
//__interrupt void WDT_ISR(void)
//{
//    static unsigned long cnt = 0;
//
//    if (cnt++ > 20) {
//        cnt = 0;
//        __bic_SR_register_on_exit(LPM0_bits);
//    }
//}
//
//#pragma vector=USCI_A0_VECTOR
//__interrupt void USCI_A0_ISR(void)
//{
//    switch (__even_in_range(UCA0IV, 4)) {
//    case  0: break;                           // Vector  0: No interrupts
//    case  2:                                  // Vector  2: RXIFG
//        usci_a0_spi_rx_isr_handle();
//        break;
//    case  4:                                  // Vector  4: TXIFG
//        usci_a0_spi_tx_isr_handle();
//        break;
//    default: break;
//    }
//}
// UART interrupt service routine
