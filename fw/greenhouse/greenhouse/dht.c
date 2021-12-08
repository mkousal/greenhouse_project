/*
 * dht.c
 *
 * Created: 01.12.2021 12:02:02
 *  Author: Martin
 */ 
#include "dht.h"
#include "gpio.h"
#include "twi.h"

int DHT_getTemperature()
{
	uint8_t res = twi_start((DHT12_ADDR << 1) + TWI_WRITE);	// Start I2C communication
	uint8_t temp_H = 0;										// Init data variables
	uint8_t temp_L = 0;
	if (res == 0)		// If I2C device answer, get data
	{
		twi_write(2);
		twi_start((DHT12_ADDR << 1) + TWI_READ);
		temp_H = twi_read_ack();
		temp_L = twi_read_nack();
		twi_stop();
		uint8_t tmp = temp_L;
		temp_L &= 0x7F;	// Set MSB to '0'
		if (temp_L > 4)	// Round up decimal place to nearest integer
			temp_H++;

		if ((tmp & 0x80) != 0)	// Negative temperature
			temp_H *= -1;
	}
	
	return temp_H;	// Return result
}

uint8_t DHT_getHumidity()
{
	uint8_t res = twi_start((DHT12_ADDR << 1) + TWI_WRITE);	// Start I2C communication
	uint8_t hum_H = 0;
	uint8_t hum_L = 0;									// Initialize data variables
	if (res == 0)										// If I2C device answer, get data
	{
		twi_write(0);
		twi_start((DHT12_ADDR << 1) + TWI_READ);
		hum_H = twi_read_ack();
		hum_L = twi_read_nack();
		twi_stop();
	}
	if (hum_L > 4)	// Round result to the nearest integer
		hum_H++;
	
	return hum_H;	// Return result
}