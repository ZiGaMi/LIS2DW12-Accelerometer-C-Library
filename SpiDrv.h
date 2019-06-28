/*
 * SpiDrv.h
 *
 *  Created on: 13.05.2019
 *      Author: ziga.miklosic
 */

#ifndef DRIVERS_SPIDRV_H_
#define DRIVERS_SPIDRV_H_

#include "stm32l0xx.h"

/*
 * 	SPI2 - RTC and Accelerometer Interface
 *
 * 	CLK 	- PB13
 * 	MISO	- PB14
 * 	MOSI	- PB15
 *
 * 	ACC_CS	- PB12
 * 	RTC_CS	- PB9
 */

// Accessories SPI
#define ACCESS_SPI				( SPI2 )

// Accessories port
#define ACCESS_port				( GPIOB )

// Clock
#define ACCESS_CLK_bp			( 13ul )
#define ACCESS_CLK_msk			( 0x01u << ACCESS_CLK_bp )
#define ACCESS_CLK_afnum		( 0ul )

// MISO
#define ACCESS_MISO_bp			( 14ul )
#define ACCESS_MISO_msk			( 0x01u << ACCESS_MISO_bp )
#define ACCESS_MISO_afnum		( 0ul )

// MOSI
#define ACCESS_MOSI_bp			( 15ul )
#define ACCESS_MOSI_msk			( 0x01u << ACCESS_MOSI_bp )
#define ACCESS_MOSI_afnum		( 0ul )

// RTC CS
#define RTC_CS_bp				( 12ul )
#define RTC_CS_msk				( 0x01u << RTC_CS_bp )
#define RTC_CS_low()			( ACCESS_port -> ODR &= ~( RTC_CS_msk ))
#define RTC_CS_high()			( ACCESS_port -> ODR |= ( RTC_CS_msk ))

// Accelerometer CS
#define ACC_CS_bp				( 9ul )
#define ACC_CS_msk				( 0x01u << ACC_CS_bp )
#define ACC_CS_low()			( ACCESS_port -> ODR &= ~( ACC_CS_msk ))
#define ACC_CS_high()			( ACCESS_port -> ODR |= ( ACC_CS_msk ))




/*
 * 	Functions
 */

// Initialize Accessories SPI Interface
void SpiAccessInit(void);

#endif /* DRIVERS_SPIDRV_H_ */
