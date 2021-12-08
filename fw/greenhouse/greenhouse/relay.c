/*
 * relay.c
 *
 * Created: 07.12.2021 23:13:06
 *  Author: Martin
 */ 

#include "gpio.h"
#include "relay.h"

void relay_init()
{	
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_1);
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_2);
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_3);
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_4);
}

void relay_on(uint8_t relay)
{
	GPIO_write_high(&RELAY_PORT, relay);
}

void relay_off(uint8_t relay)
{
	GPIO_write_low(&RELAY_PORT, relay);	
}