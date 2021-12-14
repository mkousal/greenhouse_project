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
#include "adc.h"				// ADC library with basic functions and settings

// Defines for setting your own greenhouse constants, eg. temperature, humidity, soil moisture etc.
#define SET_TEMPERATURE_HEAT 25			// Temperature at which heater is turned on
#define SET_TEMPERATURE_WINDOW 25		// Temperature at which window is opened
#define SET_HUMIDITY 30					// Humidity at which is window opened
#define SET_SOIL 50						// Soil moisture at which sprinkler is turned on
#define CALIBRATE_SOIL_MIN 730			// Value measured on soil moisture sensor at air 
#define CALIBRATE_SOIL_MAX 940			// Value measured on soil moisture sensor in the water
#define SET_LIGHT 600					// Light intensity value at which light is turned on

volatile uint8_t minuteFlag = 0;
volatile int temperature = 0;
volatile uint8_t humidity = 0;
volatile uint16_t soilMoisture = 0;
volatile uint16_t lightIntensity = 0;

// Function map for getting results from one range to the another
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Function to update LCD with new values
void lcdUpdate(int temperature, uint16_t soil, uint16_t light, uint16_t hum)
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
	lcd_gotoxy(8, 0);
	lcd_puts_P("S: ");
	itoa(soil, tmp_str, 10);
	lcd_puts(tmp_str);
	lcd_gotoxy(8, 1);
	lcd_puts_P("L: ");
	itoa(light, tmp_str, 10);
	lcd_puts(tmp_str);
}

// Function to print all measured values to UART
void printUART(int temperature, uint16_t soil, uint16_t light, uint16_t hum)
{
	char tmp_str[5] = "     ";
	uart_puts_P("Temperature: ");
	itoa(temperature, tmp_str, 10);
	uart_puts(tmp_str);
	uart_putc(248);		// Degree sign
	uart_puts_P("C  Air humidity: ");
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
}

int main(void)
{
	relay_init();		// Set ports for relay controlling
	twi_init();			// Initialize TWI
	uart_init(UART_BAUD_SELECT(9600, F_CPU));	// Initialize UART with 9600 baud
	lcd_init(LCD_DISP_ON);		// Initialize LCD
	
	uart_puts_P("\r\nGreenhouse system started\r\n");	// Print start message to UART
	lcd_gotoxy(5,0);									// Print starting message to LCD
	lcd_puts("Greenhouse");
	lcd_gotoxy(4,1);
	lcd_puts("project");
	_delay_ms(1000);
	lcd_clrscr();
	
	ADC_set_reference_AVCC();						// Set ADC reference
	ADC_enable();									// Enable ADC
	ADC_enable_conversion_complete_interrupt();		// Enable interrupt after AD conversion complete
	ADC_set_prescaler_128();						// Set ADC prescaler to 128
	
	TIM1_overflow_4s();								// Set Timer 1 overflow to 4 s
	TIM1_overflow_interrupt_enable();				// Enable Timer 1 overflow interrupt
	TIM0_overflow_16ms();							// Set Timer 0 overflow to 16 ms
	TIM0_overflow_interrupt_enable();				// Enable Timer 0 overflow interrupt
	sei();											// Globally enable interrupt flag

    while (1) 
    {
		if (minuteFlag == 1)	// 1 minute interval
		{
			minuteFlag = 0;		// Reset 1 minute flag
			temperature = DHT_getTemperature();	// Get temperature from DHT12
			humidity = DHT_getHumidity();		// Get humidity from DHT12
			soilMoisture = map(1023 - soilMoisture, 1023 - CALIBRATE_SOIL_MAX, 1023 - CALIBRATE_SOIL_MIN, 0, 100);	// Get measured soil moisture values into 0-100%
		
			if (lightIntensity > SET_LIGHT)	// Light intensity -> dark
				relay_on(RELAY_3);		// Turn on light (relay 3)
			else						// Light intensity -> bright
				relay_off(RELAY_3);		// turn off light		
				
			if (soilMoisture < SET_SOIL)		// Soil moisture below 50%
				relay_on(RELAY_4);		// Turn on sprinkler (relay 4)
			else						// Soil moisture > 50%	
				relay_off(RELAY_4);		// Turn off sprinkler
				
			if (temperature > SET_TEMPERATURE_WINDOW || humidity > SET_HUMIDITY)	// If temperature > 25°C or humidity of air > 30%
				relay_on(RELAY_1);					// Open window (relay 1)
			else									// Temperature < 25°C or humidity of air < 30%	
				relay_off(RELAY_1);					// Close window (relay 1)
				
			if(temperature < SET_TEMPERATURE_HEAT)					// If temperature > 25°C
				relay_on(RELAY_2);					// Turn on heater (relay 2)
			else									// Temperature < 25°C
				relay_off(RELAY_2);					// Turn off heater
				
				
			lcdUpdate(temperature, soilMoisture, lightIntensity, humidity);	// Update LCD with new measured values
			printUART(temperature, soilMoisture, lightIntensity, humidity);	// Update UART with new measured values
		}
    }
}

ISR(TIMER1_OVF_vect)	// ISR for setting every one minute flag
{
	static uint8_t cnt = 0;
	cnt++;
	if (cnt == 2)	// '16' for 1 minute interval, '2' for testing => 8s
	{
		cnt = 1;
		minuteFlag = 1;
	}
}

ISR(TIMER0_OVF_vect) // Start AD convert of soil moisture or light intensity, every thing is measured once in 320 ms
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
				ADC_start();			// Start AD convert
				i = 1;
				break;
			case 1:
				ADC_select_channel_2();	// Light intensity sensor
				ADC_start();			// Start AD convert
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