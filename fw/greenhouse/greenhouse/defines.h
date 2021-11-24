/*
 * defines.h
 *
 * Created: 24.11.2021 11:21:16
 *  Author: Martin
 */ 

#ifndef DEFINES_H_
#define DEFINES_H_

#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

#define RELAY_1 PD7
#define RELAY_2 PD6
#define RELAY_3 PD5
#define RELAY_4 PD4

#define RELAY_DDR_PORT DDRD
#define RELAY_PORT PORTD

#define DHT12_ADDR 92

#endif /* DEFINES_H_ */