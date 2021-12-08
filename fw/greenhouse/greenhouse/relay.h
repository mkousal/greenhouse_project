/*
 * relay.h
 *
 * Created: 07.12.2021 23:13:21
 *  Author: Martin
 */ 


#ifndef RELAY_H_
#define RELAY_H_

#define RELAY_1 PD7		// window
#define RELAY_2 PD6		// heater
#define RELAY_3 PD5		// 
#define RELAY_4 PD4		// 

#define RELAY_DDR_PORT DDRD
#define RELAY_PORT PORTD

void relay_init();

void relay_on(uint8_t relay);

void relay_off(uint8_t relay);



#endif /* RELAY_H_ */