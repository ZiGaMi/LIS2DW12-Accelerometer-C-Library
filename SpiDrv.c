/*
 * SpiDrv.c
 *
 *  Created on: 13.05.2019
 *      Author: ziga.miklosic
 */


#include "Drivers/SpiDrv.h"


// Initialize Accessories SPI Interface
void SpiAccessInit(){

	/*
	 * 	Configure SPI pins
	 */

	// Enable clock for GPIOB
	RCC -> IOPENR |= ( RCC_IOPENR_GPIOBEN );

	// Alternative function mode
	ACCESS_port -> MODER &= ~(	( 0x03u << ( 2ul *  ACCESS_CLK_bp )) 	|
								( 0x03u << ( 2ul *  ACCESS_MISO_bp )) 	|
								( 0x03u << ( 2ul *  ACCESS_MOSI_bp )) 	|
								( 0x03u << ( 2ul *  RTC_CS_bp )) 	|
								( 0x03u << ( 2ul *  ACC_CS_bp )));

	ACCESS_port -> MODER |=  (	( 0x02u << ( 2ul * ACCESS_CLK_bp ))		|
								( 0x02u << ( 2ul * ACCESS_MISO_bp ))	|
						   		( 0x02u << ( 2ul * ACCESS_MOSI_bp )));


	// Output for chip select
	ACCESS_port -> MODER |= ( 0x01u << ( 2ul * RTC_CS_bp ) |
							( 0x01u << ( 2ul * ACC_CS_bp )));


	// High speed mode
	ACCESS_port -> OSPEEDR |= (	( 0x03u << ( 2ul * ACCESS_CLK_bp ))		|
								( 0x03u << ( 2ul * ACCESS_MISO_bp ))	|
								( 0x03u << ( 2ul * ACCESS_MOSI_bp ))	|
								( 0x03u << ( 2ul * RTC_CS_bp ))			|
								( 0x03u << ( 2ul * ACC_CS_bp )));


	// Set alternative functions
	ACCESS_port -> AFR[1] |= (	( ACCESS_CLK_afnum 		<< ( 4ul * ( ACCESS_CLK_bp - 8u ))) 	|
								( ACCESS_MISO_afnum 	<< ( 4ul * ( ACCESS_MISO_bp - 8u ))) 	|
								( ACCESS_MOSI_afnum 	<< ( 4ul * ( ACCESS_MOSI_bp -8u ))));

	// Set slave select high
	RTC_CS_high();
	ACC_CS_high();


	/*
	 * 	Configure SPI
	 */

	// Enable clock for SPI2
	RCC -> APB1ENR |= ( RCC_APB1ENR_SPI2EN );

	// Master configuration
	// fPCLK/8 = 1 MHz
	// CPHA=0, CPOL=0
	// Software driven SS
	ACCESS_SPI -> CR1 = 0u;
	ACCESS_SPI -> CR1 |= ( SPI_CR1_BR_1 | SPI_CR1_MSTR );

	// NOTE: This configuration is suitable for RTC device.
	// TODO: Check if interface with accelerometer can be implemented with this configs
	// SD Card SPI Mode 0
	// Data size -> 8 bit
	// SS output enable
	ACCESS_SPI -> CR2 = 0;
	ACCESS_SPI -> CR2 |= ( SPI_CR2_SSOE );

	// Enable SPI
	ACCESS_SPI -> CR1 |= SPI_CR1_SPE;
}
