/*
 * dht.h
 *
 * Created: 01.12.2021 12:01:49
 *  Author: Martin
 */ 


#ifndef DHT_H_
#define DHT_H_

#include <stdio.h>

#define DHT12_ADDR 92

int DHT_getTemperature();

uint8_t DHT_getHumidity();



#endif /* DHT_H_ */