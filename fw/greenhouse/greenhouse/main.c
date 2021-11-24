/*
 * greenhouse.c
 *
 * Created: 24.11.2021 11:19:26
 * Author : Martin
 */ 

#include <avr/io.h>
#include "defines.h"		// Own file with project defines
#include <avr/interrupt.h>
#include "timer.h"
#include <stdlib.h>
#include "uart.h"
#include "twi.h"
#include <util/delay.h>

void initRelay()
{
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_1);
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_2);
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_3);
	GPIO_config_output(&RELAY_DDR_PORT, RELAY_4);
}

int main(void)
{
	initRelay();
	GPIO_write_high(&RELAY_PORT, RELAY_3);
	_delay_ms(500);
	GPIO_write_low(&RELAY_PORT, RELAY_3);
	twi_init();
	uart_init(UART_BAUD_SELECT(9600, F_CPU));
	
	uart_puts_P("\r\nGreenhouse M&C system started\r\n");
	
	TIM1_overflow_4s();
	TIM1_overflow_interrupt_enable();
	
	sei();

    while (1) 
    {
    }
}

ISR(TIMER1_OVF_vect)
{
	uint8_t res = twi_start((DHT12_ADDR << 1) + TWI_WRITE);
	char tmp_str[3] = "   ";
	
	if (res == 0)
	{
		twi_write(0);
		twi_start((DHT12_ADDR << 1)+TWI_READ);
		uint8_t hum_H = twi_read_ack();
		uint8_t hum_L = twi_read_ack();
		uint8_t temp_H = twi_read_ack();
		uint8_t temp_L = twi_read_nack();
		twi_stop();
		itoa(hum_H, tmp_str, 10);
		uart_puts(tmp_str);
		uart_puts(" ");
		itoa(hum_L, tmp_str, 10);
		uart_puts(tmp_str);
		uart_puts(" ");
		itoa(temp_H, tmp_str, 10);
		uart_puts(tmp_str);
		uart_puts(" ");
		itoa(temp_L, tmp_str, 10);
		uart_puts(tmp_str);
		uart_puts("\r\n");
	}
	else
		uart_puts_P("I2C err\r\n");
}