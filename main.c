/*
 * main.c
 *
 *  Created on: 2019-04-11 15:57
 *      Author: art-j <jjw903427521@gmail.com>
 *  Fixed on :  2019-04-26 11:14
 *      Author: art-j <jjw903427521@gmail.com>
 *  updated  : 2019-05-29 11:14
 *      Author: art-j <jjw903427521@gmail.com>
 ** --------key------------
 *  P1.1 P1.4
* -----------------------
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    ---------SOFT_I2C-----   *  ---------SOFT_SPI-----   * --------SSD1351--------  * --------DAC8571--------   * ------clock out-----
 * PORT     TYPE    PIN      * PORT     TYPE    PIN      * PORT     TYPE    PIN     * PORT     TYPE    PIN      * ACLK:  P4.2
 * SDA      INOUT   P1.6     * MOSI     OUT     P10.2    * RES      OUT     P10.3   * SDA      INOUT   P1.6     * HSMCLK:P4.4
 * SCL      OUT     P1.7     * MISO     IN      P10.3    * DC       OUT     P10.4   * SCL      OUT     P1.7     * MCLK:  P4.3
 * -----------------------   * SCK      OUT     P10.1    * CS       OUT     P10.5
                                                         * SCK      OUT     P10.1(SPI)
                                                         * MOSI     OUT     P10.2(SPI)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 * -----USCI_A2_SPI-------  * -----USCI_B0_SPI-------    * -----USCI_B3_SPI---------  * -----USCI_B1_SPI---------
 * PORT     TYPE    PIN     * PORT     TYPE    PIN       * PORT     TYPE    PIN       * PORT     TYPE    PIN
 * MOSI     OUT     P3.3    * MOSI     OUT     P1.6      * MOSI     OUT     P10.2      * MOSI     OUT     P4.1
 * MISO     IN      P3.2    * MISO     IN      P1.7      * MISO     IN      P10.3      * MISO     IN      P4.2
 * SCK      OUT     P3.1    * SCK      OUT     P1.5      * SCK      OUT     P10.1      * SCK      OUT     P4.3
 * ----------------------   * ----------------------     * ---------------------      * ---------------------

 * -----USCI_A1_UART------  * -----USCI_A0_UART------
 * PORT     TYPE    PIN     * PORT     TYPE    PIN
 * RXD      INOUT   P3.2    * RXD      INOUT   P1.2
 * TXD      OUT     P3.3    * TXD      OUT     P1.3
 * -----------------------  * -----------------------
 */
//******************************************************************************

#include "msp.h"
#include <mylib.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    driver_init();
    device_init();
    //user_init();
    LMP3;
    while (1) {
    if(systik_flag==1)
    {
        user_loop();
        systik_flag=0;
    }
    LMP3;
    }
}

