#include "dht_11.h"
#include "systick.h"

#define DHTPIN	(1U<<9) /* DHTPIN Pin i.e PA9 */

void dht_init(void){
	/* Enable GPIOA */
	RCC->AHB1ENR |= (1<< 0);
	/* Set PA9 direction (MODE) - OUTPUT */
	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &= ~(1U<<19);

	GPIOA->ODR &= ~DHTPIN; //Make sensor pin LOW
	usDelay(18000); //Wait for 18ms
	GPIOA->ODR &= ~DHTPIN; //Make sensor pin high
	//usDelay(40); //Wait for 40us
	/* Set PA9 direction (MODE) - Input */
	GPIOA->MODER &= ~(1U<<18);
	GPIOA->MODER &= ~(1U<<19);
}

int dht_response(void){
	int response = 0;
	usDelay(40);
	if (!(GPIOA->IDR & DHTPIN))
	{
		usDelay(80);
		if ((GPIOA->IDR & DHTPIN)) response = 1;
		else response = -1;
	}
	while ((GPIOA->IDR & DHTPIN));   // wait for the pin to go low

	return response;
}

uint8_t dht_Read (void){
	uint8_t d,i;
	d = 0;
	for (i=0;i<8;i++)
	{
		while (!((GPIOA->IDR & DHTPIN)));   // wait till pin goes high
		usDelay(40);   // wait for 40 us
		if (((GPIOA->IDR & DHTPIN)))   // if the pin is low
		{
			d |= (1U<<(7-i));  /* write 1 */
		}
		else d &= ~(1U<<(7-i));   // write 0
		while (((GPIOA->IDR & DHTPIN)));  // wait for the pin to go low
	}
	return d;
}
