#include <stdio.h>
#include <stdlib.h>

#include "uart.h"
#include "dht_11.h"
#include "systick.h"


static uint8_t iHum, dHum, iTemp, dTemp;
static uint8_t checkSUM; 
static int dataPresent = 0;

static char tempIntF[5], tempDecF[5];
static char humIntF[5], humDecF[5];
static char test[5];
static char degree = 248;

int main(void){

	usart2_rxtx_init();

	while(1){
	dht_init();
	dataPresent = dht_response();
	iHum = dht_Read(); 	// store the first 8-bit in iHum i.e. integer part of Humidity
	dHum = dht_Read();	// store the next 8-bit in dHum i.e. decimal part of Humidity
	iTemp = dht_Read();
	dTemp = dht_Read();
	checkSUM = dht_Read();
	/////////////////////////////////////////////////////
		sprintf(humIntF, "%d", iHum);
		sprintf(humDecF, "%d", dHum);
		sprintf(tempIntF, "%d", iTemp);
		sprintf(tempDecF, "%d", dTemp);
	//////////////////////////////////////////////////////
	if (checkSUM != (iHum+dHum+iTemp+dTemp))
	{
			uart2_tx_string("Error");
			uart2_tx('\n');
	}
	else{
				uart2_tx_string("Temp: ");
				uart2_tx_string(tempIntF);
				uart2_tx('.');
				uart2_tx_string(tempDecF);
				uart2_tx(degree);
				uart2_tx('C');
				uart2_tx('\n');
				uart2_tx_string("Hum: ");
				uart2_tx_string(humIntF);
				uart2_tx('.');
				uart2_tx_string(humDecF);
				uart2_tx('%');
				uart2_tx('\n');
				uart2_tx('\n');
		
			//	sprintf(test, "%d", dataPresent);
		//uart2_tx_string(test);
		//uart2_tx('\n');
		}
	usDelay(1000000); // micro second delay -> 1sec

	}

} 




