#ifndef _DHT11_H
#define _DHT11_H

#include "stm32f4xx.h"


void dht_init(void);
int dht_response (void);
uint8_t dht_Read (void);

#endif
