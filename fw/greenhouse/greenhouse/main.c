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
#include "adc.h"

volatile uint8_t minuteFlag = 0;
volatile int temperature = 0;
volatile uint8_t humidity = 0;
volatile uint16_t soilMoisture = 0;
volatile uint16_t lightIntensity = 0;

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void lcdUpdate(uint16_t temperature, uint16_t soil, uint16_t light, uint16_t hum)
{
	char tmp_str[4] = "    ";
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts_P("T: ");
	itoa(temperature, tmp_str, 10);
	lcd_puts(tmp_str);
	lcd_gotoxy(0,1);
	lcd_puts_P("H: ");
	itoa(hum, tmp_str, 10);
	lcd_puts(tmp_str);
}

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
	lcd_clrscr();
	
	ADC_set_reference_AVCC();
	ADC_enable();
	ADC_enable_conversion_complete_interrupt();
	ADC_set_prescaler_128();
	
	TIM1_overflow_4s();
	TIM1_overflow_interrupt_enable();
	TIM0_overflow_16ms();
	TIM0_overflow_interrupt_enable();
	sei();

    while (1) 
    {
		if (minuteFlag == 1)	// 1 minute interval
		{
			minuteFlag = 0;
			temperature = DHT_getTemperature();
			humidity = DHT_getHumidity();
			soilMoisture = map(1023 - soilMoisture, 1023 - 940, 1023 - 730, 0, 100);
			uart_puts_P("Temperature: ");
		
			char tmp_str[5] = "     ";
			itoa(temperature, tmp_str, 10);
			uart_puts(tmp_str);
			uart_puts_P("°C  Air humidity: ");
			itoa(humidity, tmp_str, 10);
			uart_puts(tmp_str);
			uart_puts_P("%  Soil humidity: ");
			itoa(soilMoisture, tmp_str, 10);
			uart_puts(tmp_str);
			uart_puts_P("%  Light: ");
			if (lightIntensity > 600)
				uart_puts_P("dark");
			else
				uart_puts_P("light");
			itoa(lightIntensity, tmp_str, 10);
			uart_puts(tmp_str);
			uart_puts_P("\r\n");
			
			if (lightIntensity > 600)	// Light intensity -> dark
				relay_on(RELAY_3);		// Turn on light (relay 3)
			else						// Light intensity -> bright
				relay_off(RELAY_3);		// turn off light
				
			
			itoa(soilMoisture, tmp_str, 10);
			uart_puts(tmp_str);
			uart_puts_P("\r\n");
			
			if (soilMoisture < 50)
				relay_on(RELAY_4);
			else
				relay_off(RELAY_4);
				
			if (temperature > 25 || humidity > 30)
				relay_on(RELAY_1);
			else
				relay_off(RELAY_1);
				
			if(temperature < 25)
				relay_on(RELAY_2);
			else
				relay_off(RELAY_2);
				
				
			lcdUpdate(temperature, soilMoisture, lightIntensity, humidity);
		}
    }
}

ISR(TIMER1_OVF_vect)
{
	static uint8_t cnt = 0;
	cnt++;
	if (cnt == 2)	// 16 for 1 minute interval
	{
		cnt = 1;
		minuteFlag = 1;
	}
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t cnt = 0;
	static uint8_t i = 0;
	cnt++;
	if(cnt == 10)	// ~160 ms
	{
		cnt = 0;
		switch (i)
		{
			case 0:
				ADC_select_channel_3();	// Soil moisture sensor
				ADC_start();
				i = 1;
				break;
			case 1:
				ADC_select_channel_2();	// Light intensity sensor
				ADC_start();
				i = 0;
				break;
		}
	}
	
}

ISR(ADC_vect)
{
	uint16_t adc = ADC;
	if ((ADMUX & 0x03) == 3)	// Soil moisture sensor
		soilMoisture = adc;
	else	// Light intensity sensor
		lightIntensity = adc;
}