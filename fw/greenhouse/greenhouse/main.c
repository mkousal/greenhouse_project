/*
 * greenhouse.c
 *
 * Created: 24.11.2021 11:19:26
 * Author : Martin
 */ 
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

#include <avr/io.h>				// AVR device-specific IO definitions
#include <avr/interrupt.h>		// Interrupts standard C library for AVR-GCC
#include <util/atomic.h>		// Safe interrupt variable operations
#include "timer.h"				// Timer library for AVR-GCC
#include <stdlib.h>				// C library, used for conversion functions
#include <stdio.h>				// C library with basic functions
#include "uart.h"				// UART library for AVR-GCC
#include "twi.h"				// TWI (I2C) library for AVR-GCC
#include <util/delay.h>			// AVR delay library
#include "relay.h"				// Relay library with basic functions with relay shield
#include "dht.h"				// DHT12 specific library with basic functions over I2C
#include "lcd.h"				// Peter Fleury's LCD library

volatile uint8_t minuteFlag = 0;
volatile int temperature = 0;
volatile uint8_t humidity = 0;
volatile int soilMoisture = 0;
volatile int lightIntensity = 0;

int main(void)
{
	relay_init();
	twi_init();
	uart_init(UART_BAUD_SELECT(9600, F_CPU));
	lcd_init(LCD_DISP_ON);
	
	uart_puts_P("\r\nGreenhouse system started\r\n");	// Print start message to UART
	lcd_gotoxy(5,0);									// Print starting message to LCD
	lcd_puts("Greenhouse");
	lcd_gotoxy(4,1);
	lcd_puts("project");
	_delay_ms(1000);
	
	
	TIM1_overflow_4s();
	TIM1_overflow_interrupt_enable();
	
	sei();

    while (1) 
    {
		if (minuteFlag == 1)	// 1 minute interval
		{
			minuteFlag = 0;
			temperature = DHT_getTemperature();
			humidity = DHT_getHumidity();
		}
    }
}

ISR(TIMER1_OVF_vect)
{
	static uint8_t cnt = 0;
	cnt++;
	if (cnt == 16)
	{
		cnt = 1;
		minuteFlag = 1;
	}
}