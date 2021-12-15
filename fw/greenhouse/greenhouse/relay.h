/*
 * relay.h
 *
 * Created: 07.12.2021 23:13:21
 *  Author: Martin
 */ 

#ifndef RELAY_H_
#define RELAY_H_

/**
 * @name  Definitions for relay shield
 */
#define RELAY_1 PB2		// window
#define RELAY_2 PB3		// heater
#define RELAY_3 PB4		// light
#define RELAY_4 PB5		// sprinkler
#define RELAY_DDR_PORT DDRB
#define RELAY_PORT PORTB

/** @brief Initialize relay pins (set output and to off state) */
void relay_init();

/** 
 * @brief Set relay ON 
 * @param relay Number of controlled relay
 * @return none
*/ 
void relay_on(uint8_t relay);

/** 
 * @brief Set relay OFF 
 * @param relay Number of controlled relay
 * @return none
 */
void relay_off(uint8_t relay);

#endif /* RELAY_H_ */