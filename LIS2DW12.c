
/*
 * Accelerometer.c
 *
 *  Created on: 28.06.2019
 *      Author: ziga.miklosic
 */

#include "Accessories/Accelerometer.h"

// Write to register
void AccelerometerWriteReg(uint8_t addr, uint8_t data){

	ACC_CS_low();

	// Address
	*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) ( addr & 0x3Fu );
	while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
	( ACCESS_SPI -> DR );

	// Value
	*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) ( data & 0xFFu );
	while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
	( ACCESS_SPI -> DR );

	ACC_CS_high();
}


// Write multiple bytes
// Memory address increment
// NOTE: Do not use this function before initialization of accelerometer
void AccelerometerWriteMultipleReg(uint8_t addr, uint8_t *buf, uint8_t size){

	// Limit size
	size = ( size > 8 ) ? ( 8u ) : ( size );

	ACC_CS_low();

	// Address
	*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) ( addr & 0x3Fu );
	while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
	( ACCESS_SPI -> DR );

	// Value
	for( uint8_t i = 0; i < size; i++){
		*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) ( *buf++ & 0xFFu );
		while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
		( ACCESS_SPI -> DR );
	}

	ACC_CS_high();
}


// Read from register
uint8_t AccelerometerReadReg(uint8_t addr){

	uint8_t data = 0x00u;

	ACC_CS_low();

	// Address
	*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) (( 0x01u << 7u ) | ( addr & 0x3Fu ));
	while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
	( ACCESS_SPI -> DR );

	// Value
	*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) ( data & 0xFFu );
	while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
	data = ( uint8_t ) ( ACCESS_SPI -> DR );

	ACC_CS_high();

	return ( uint8_t ) ( data );
}


// Read multiple bytes
// Memory address increment
// NOTE: Do not use this function before initialization of accelerometer
// Read multiple bytes
uint8_t* AccelerometerReadMultipleReg(uint8_t addr, uint8_t size){

	// Limit size
	size = ( size > 8 ) ? ( 8u ) : ( size );

	// Data buffer
	static uint8_t buf[10];

	ACC_CS_low();

	// Address
	*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) (( 0x01u << 7u ) | ( addr & 0x3Fu ));
	while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
	( ACCESS_SPI -> DR );

	for( uint8_t i = 0; i < size; i++){
		*(uint8_t*) &( ACCESS_SPI -> DR ) = ( uint8_t ) ( 0x00u );
		while(( ACCESS_SPI -> SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
		buf[i] = ( uint8_t ) ( ACCESS_SPI -> DR );
	}

	ACC_CS_high();

	return ( uint8_t* ) ( &buf );
}


// Init accelerometer
void AccelerometerInit(){

	// 1600Hz ODR
	// High performance
	// 14-bit
	AccelerometerWriteReg(LIS2DW12_CTRL1_addr, (( 0x09u << 4u ) | ( 0x01u << 2u ) | ( 0x03u << 0u )));

	// SPI
	// 4-wire
	// Block Data Update
	// No pull-up on CS
	// Multiple byte access automatically increment addresses
	AccelerometerWriteReg(LIS2DW12_CTRL2_addr, ( 0x01 << 2u ) | ( 0x01 << 4u ));

	// Self-test disabled
	// Push-pull
	// No interrupt
	AccelerometerWriteReg(LIS2DW12_CTRL3_addr, 0x00u);

	// Interrupts
	AccelerometerWriteReg(LIS2DW12_CTRL4_INT1_PAD_CTRL_addr, 0x00u);
	AccelerometerWriteReg(LIS2DW12_CTRL5_INT2_PAD_CTRL_addr, 0x00u);

	// Bandwith ODR/20 -> 1600Hz/20 = 80Hz BW
	// Full scale +-2g
	// High pass filer disabled
	// Low noise enabled
	AccelerometerWriteReg(LIS2DW12_CTRL6_addr, (( 0x03u << 6u ) | ( 0x01u << 2u )));

	// FIFO Bypass
	AccelerometerWriteReg(LIS2DW12_FIFO_CTRL_addr, 0x00u);
}


// Check for new data
bool AccelerometerCheckForNewData(){
	return ( bool ) ((( AccelerometerReadReg(LIS2DW12_STATUS_addr) & 0x01 ) == 0x01 ) ? ( true ) : ( false ) );
}


// Get axis values
void AccelerometerGetAxisValues(AccelerometerTypeDef *ACC){

	// Get data
	uint8_t *data;
	data = AccelerometerReadMultipleReg(LIS2DW12_OUT_X_L_addr, 6u);

	// Parse data
	for ( uint8_t i = 0; i < 6; i = i + 2 ){
		ACC -> axisRawVal[ ( i >> 1u ) ] = ( uint16_t ) (((( *(data + i + 1u ) << 8u ) & 0xFF00u ) | ( *( data + i ) & 0xFF )));
	}
}
