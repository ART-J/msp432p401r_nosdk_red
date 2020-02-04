/*
 * usci_a0_spi.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 * 
 * ---------SPI---------
 * PORT		TYPE	PIN
 * MOSI		OUT		P3.3
 * MISO		IN		P3.4
 * SCK      OUT     P2.7
 * ---------------------
 */

#include <msp.h>


//#define SPI_SET_PIN()   {\
//                            P3SEL |= BIT3 + BIT4;\
//                            P2SEL |= BIT7;\
//                        }

#define SPI_SET_PIN()  P10SEL0 |= BIT1 +BIT2 + BIT3;
//						{\
//                            /*P3SEL |= BIT3 + BIT4;\
//                            P2SEL |= BIT7;\*/
//                            \           // set 3-SPI pin as second function
//                        }

static unsigned char *spi_tx_buff;
static unsigned char *spi_rx_buff;

static unsigned char spi_tx_num = 0;
static unsigned char spi_rx_num = 0;

unsigned char usci_b3_spi_transmit_frame(unsigned char *p_buff, unsigned char num)
{
	if (UCB3STAT & UCBUSY) return 0;
	__disable_interrupt();
    UCB3IE |= UCTXIE;
	UCB3IE &=~UCRXIE;
	__enable_interrupt();
    spi_tx_buff = p_buff;
    spi_tx_num  = num;
	UCB3TXBUF = *spi_tx_buff++;
    while (UCB3STAT & UCBUSY);
	return 1;
}

unsigned char usci_b3_spi_receive_frame(unsigned char *p_buff, unsigned char num)
{
    if (UCB3STAT & UCBUSY) return 0;
	__disable_interrupt();
    UCB3IE &=~UCTXIE;
    UCB3IE |= UCRXIE;
    __enable_interrupt();
    spi_rx_buff = p_buff;
    spi_rx_num  = num;
    UCB3TXBUF = 0xff;
    while (UCB3STAT & UCBUSY);
	return 1;
}

void usci_b3_spi_init(void)
{
    SPI_SET_PIN();
    __enable_interrupt();
    NVIC->ISER[0] = 1 << ((EUSCIB0_IRQn) & 31); // Enable eUSCIA3 interrupt in NVIC module

    UCB3CTLW0 |= UCSWRST;                     // **Put state machine in reset**
	UCB3CTLW0 |= UCMST|UCSYNC|UCCKPL|UCMSB;   // 3-pin, 8-bit SPI master
											  // Clock polarity high, MSB
	UCB3CTLW0 |= UCSSEL__SMCLK;                // ACLK
	UCB3BR0 = 7;                           // /2,fBitClock = fBRCLK/(UCBRx+1).
	UCB3BR1 = 0;                              //
	//UCA3MCTLW = 0;                            // No modulation
	UCB3CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**
    UCB3IFG  &=~(UCTXIFG + UCRXIFG);
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;   // Wake up on exit from ISR
}
inline void usci_b3_spi_rx_isr_handle(void)
{
    *spi_rx_buff++ = UCB3RXBUF;
    spi_rx_num--;
    if (spi_rx_num) {
        UCB3TXBUF = 0xff;
    } else {
        UCB3IFG &=~UCRXIFG;
        UCB3IE  &=~UCRXIE;
    }
}

inline void usci_b3_spi_tx_isr_handle(void)
{
    UCB3RXBUF;
    spi_tx_num--;
    if (spi_tx_num) {
        UCB3TXBUF = *spi_tx_buff++;
    } else {
        UCB3IFG &=~UCTXIFG;
        UCB3IE  &=~UCTXIE;
    }
}
