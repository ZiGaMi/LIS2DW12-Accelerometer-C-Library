
/*
 * Accelerometer.h
 *
 *  Created on: 28.06.2019
 *      Author: ziga.miklosic
 */

#ifndef ACCESSORIES_ACCELEROMETER_H_
#define ACCESSORIES_ACCELEROMETER_H_

#include "stm32l0xx.h"
#include "stdbool.h"

#include "Drivers/SpiDrv.h"


/*
 * 	LIS2DW12 Accelerometer Register Addresses
 */

// Who Am I
#define LIS2DW12_WHO_AM_I_addr						( uint8_t )		( 0x0Fu )
#define LIS2DW12_WHO_AM_I_name						( uint8_t )		( 0x44u )

// Control registers
#define LIS2DW12_CTRL1_addr							( uint8_t )		( 0x20u )
#define LIS2DW12_CTRL2_addr							( uint8_t )		( 0x21u )
#define LIS2DW12_CTRL3_addr							( uint8_t )		( 0x22u )
#define LIS2DW12_CTRL4_INT1_PAD_CTRL_addr			( uint8_t )		( 0x23u )
#define LIS2DW12_CTRL5_INT2_PAD_CTRL_addr			( uint8_t )		( 0x24u )
#define LIS2DW12_CTRL6_addr							( uint8_t )		( 0x25u )
#define LIS2DW12_CTRL7_addr							( uint8_t )		( 0x3Fu )

// Temperature output register - 16 bit
#define	LIS2DW12_OUT_T_L_addr						( uint8_t )		( 0x0Du )
#define LIS2DW12_OUT_T_H_adrr						( uint8_t )		( 0x0Eu )

// Temperature output register - 8 bit
#define LIS2DW12_OUT_T_addr							( uint8_t )		( 0x26u )

// Status register
#define LIS2DW12_STATUS_addr						( uint8_t )		( 0x27u )
#define LIS2DW12_STATUS_DUP_addr					( uint8_t )		( 0x37u )

// Acceleration across axis
#define LIS2DW12_OUT_X_L_addr						( uint8_t )		( 0x28u )
#define LIS2DW12_OUT_X_H_addr						( uint8_t )		( 0x29u )
#define LIS2DW12_OUT_Y_L_addr						( uint8_t )		( 0x2Au )
#define LIS2DW12_OUT_Y_H_addr						( uint8_t )		( 0x2Bu )
#define LIS2DW12_OUT_Z_L_addr						( uint8_t )		( 0x2Cu )
#define LIS2DW12_OUT_Z_H_addr						( uint8_t )		( 0x2Du )

// FIFO control registers
#define LIS2DW12_FIFO_CTRL_addr						( uint8_t )		( 0x2Eu )
#define LIS2DW12_FIFO_SAMPLES_addr					( uint8_t )		( 0x2Fu )

// TAP thresholds
#define LIS2DW12_TAP_THS_X_addr						( uint8_t )		( 0x30u )
#define LIS2DW12_TAP_THS_Y_addr						( uint8_t )		( 0x31u )
#define LIS2DW12_TAP_THS_Z_addr						( uint8_t )		( 0x32u )
#define LIS2DW12_TAP_SRC_addr						( uint8_t )		( 0x39u )

// Interrupts registers
#define LIS2DW12_INT_DUR_addr						( uint8_t )		( 0x33u )
#define LIS2DW12_ALL_INT_SRC_addr					( uint8_t )		( 0x3Bu )

// Wake-Up register
#define LIS2DW12_WAKE_UP_THS_addr					( uint8_t )		( 0x34u )
#define LIS2DW12_WAKE_UP_DUR_addr					( uint8_t )		( 0x35u )
#define LIS2DW12_WAKE_UP_SRC_addr					( uint8_t )		( 0x38u )

// Free fall
#define LIS2DW12_FREE_FALL_addr						( uint8_t )		( 0x36u )

// 6D source
#define LIS2DW12_SIXD_SRC_addr						( uint8_t )		( 0x3Au )

// Axis offsets
#define LIS2DW12_X_OFS_USR_addr						( uint8_t )		( 0x3Cu )
#define LIS2DW12_Y_OFS_USR_addr						( uint8_t )		( 0x3Du )
#define LIS2DW12_Z_OFS_USR_addr						( uint8_t )		( 0x3Eu )



// Data structure
typedef struct{
	uint16_t				axisRawVal[3];
}AccelerometerTypeDef;


// Axis names
typedef enum{
	XAxis	= ( uint8_t ) ( 0u ),
	YAxis	= ( uint8_t ) ( 1u ),
	ZAxis	= ( uint8_t ) ( 2u )
}AxisEnum;



/*
 * 	Functions
 */

// Init accelerometer
void AccelerometerInit(void);

// Write to register
void AccelerometerWriteReg(uint8_t, uint8_t);

// Write multiple bytes
void AccelerometerWriteMultipleReg(uint8_t, uint8_t*, uint8_t);

// Read from register
uint8_t AccelerometerReadReg(uint8_t);

// Read multiple bytes
uint8_t* AccelerometerReadMultipleReg(uint8_t, uint8_t);

// Check for new data
bool AccelerometerCheckForNewData(void);

// Get axis value
void AccelerometerGetAxisValues(AccelerometerTypeDef*);



#endif /* ACCESSORIES_ACCELEROMETER_H_ */
