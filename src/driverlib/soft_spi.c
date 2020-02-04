/*
 * soft_spi.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 * 
 * ---------SPI---------
 * PORT		TYPE	PIN
 * MOSI		OUT		P3.3
 * MISO		IN		P3.4
 * SCK		OUT		P2.7
 * ---------------------
 */

#include <msp.h>

#define SPI_SET_PIN()   {\
                            P10DIR |= BIT2;\
                            P10DIR &=~BIT3;\
                            P10DIR |= BIT1;\
                        }

#define SPI_SIMO_SET()  P10OUT |= BIT2
#define SPI_SIMO_CLR()  P10OUT &=~BIT2
#define SPI_SOMI_IN()   P10IN  &  BIT3
#define SPI_CLK_SET()   P10OUT |= BIT1
#define SPI_CLK_CLR()   P10OUT &=~BIT1

#define CPU_FREQ  48000000

static inline void delay_us(void)
{
    __delay_cycles(CPU_FREQ / 48000000);
}

static void transmit_char(unsigned char data)
{
	unsigned char i = 0;
	for (i=8; i>0; i--) {
        delay_us();
        SPI_CLK_CLR();
        if (data & BIT7) {
            SPI_SIMO_SET();
        } else {
            SPI_SIMO_CLR();
        }
        data <<= 1;
        delay_us();
		SPI_CLK_SET();
	}
}

static unsigned char receive_char(void)
{
	unsigned char i = 0;
	unsigned char temp = 0;
	for (i=8; i>0; i--) {
	    delay_us();
		SPI_CLK_SET();
		temp <<= 1;
		if (SPI_SOMI_IN()) {
			temp |= BIT0;
		}
        delay_us();
        SPI_CLK_CLR();
	}
	return temp;
}

unsigned char soft_spi_transmit_frame(unsigned char *p_buff, unsigned int num)
{
	unsigned char i = 0;
	__disable_interrupt();
	for (i=num; i>0; i--) {
		transmit_char(*p_buff);
		p_buff++;
	}
	__enable_interrupt();
	return 1;
}

unsigned char soft_spi_receive_frame(unsigned char *p_buff, unsigned int num)
{
	unsigned char i = 0;
	__disable_interrupt();
	for (i=num; i>0; i--) {
		 *p_buff = receive_char();
		 p_buff++;
	}
	__enable_interrupt();
	return 1;
}

void soft_spi_init(void)
{
    SPI_SET_PIN();
}
