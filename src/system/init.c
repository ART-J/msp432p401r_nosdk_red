/*
 * init.c
 *
 *  Created on: 2018-02-10 16:37
 *     Author: Jack Chen <redchenjs@live.com>
*   Fixed on :  2020-02-04 22:14
*      Author: art-j <jjw903427521@gmail.com>
 */

#include <inc/driverlib/driverlib.h>
#include <inc/devicelib/devicelib.h>


void driver_init(void)
{
    CSInit();
	wdt_init();
	usci_b3_spi_init();
	//usci_b0_i2c_init();
	//soft_i2c_init();
	usci_a0_uart_init();
	ADC14init();

}

void device_init(void)
{
	// led_init();
	// key_init();

	ssd1351_init();
	//    dac8571_init();
	//    ads1118_init();
}


