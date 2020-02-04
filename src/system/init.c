/*
 * init.c
 *
 *  Created on: 2018-02-10 16:37
 *     Author: Jack Chen <redchenjs@live.com>
*   Fixed on :  2020-02-04 22:14
*      Author: art-j <jjw903427521@gmail.com>
 */

//#include <inc/device/wdt.h>
//#include <inc/device/ucs.h>
//#include <inc/device/soft_i2c.h>
//#include <inc/device/usci_a0_spi.h>
//#include <inc/device/usci_b0_i2c.h>
#include <inc/devicelib/ssd1351.h>
#include <inc/driverlib/ADC14.h>
#include <inc/driverlib/usci_b3_spi.h>
#include <inc/driverlib/wdt.h>
//#include <inc/driver/ads1118.h>
//#include <inc/driver/dac8571.h>

void driver_init(void)
{
	wdt_init();
	usci_b3_spi_init();
	ADC14init();
	//usci_b0_i2c_init();
	//soft_i2c_init();
	//usci_b1_spi_init();
}

void device_init(void)
{
	// led_init();
	// key_init();

	ssd1351_init();
	//    dac8571_init();
	//    ads1118_init();
}


