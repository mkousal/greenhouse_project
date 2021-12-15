/*
 * dht.h
 *
 * Created: 01.12.2021 12:01:49
 *  Author: Martin
 */ 


#ifndef DHT_H_
#define DHT_H_

#include <stdio.h>
/**
 * @name  Definitions DHT12 sensor
 */
#define DHT12_ADDR 92

/** 
 * @brief Returns measured temperature from DHT12 sensor 
 * @return int with temperature
 */

int DHT_getTemperature();

/** 
 * @brief Returns measured humidity from DHT12 sensor 
 * @return uint8_t with humidity
 */
uint8_t DHT_getHumidity();

#endif /* DHT_H_ */