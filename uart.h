#ifndef _UART_H
#define _UART_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>


void uart2_tx(char ch);
char uart2_rx(void);
void usart2_rxtx_init(void);
void uart2_tx_string(char *ch);

#endif
