#include "uart.h"

                                                    																							
#define GPIOAEN						(1U<<0)
#define UART2EN						(1U<<17)

#define CR1_TE						(1U<<3)
#define CR1_RE						(1U<<2)

#define CR1_UE						(1U<<13)
#define SR_TXE						(1U<<7)
#define SR_RXNE						(1U<<5)

#define SYS_FREQ					16000000
#define APB1_CLK					SYS_FREQ

#define UART_BAUDRATE			9600


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate);

void usart2_rxtx_init(void){
	
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	
	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<4);
	
	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	
	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER |= (1U<<7);
	GPIOA->MODER &= ~(1U<<6);
	
	/*Set PA3 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);
	
	
	/********Configure uart module********/
	/*Enable clock access to uart2*/
	RCC->APB1ENR |= UART2EN;
	
	/*Configure baudrate*/
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	
	/*Configure the transfer direction*/
	USART2->CR1 = (CR1_TE | CR1_RE);
	/*Enable uart module */
		USART2->CR1 |= CR1_UE;
	
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate){

	USARTx->BRR = ((periphClk + (baudRate/2U))/baudRate); //compute_uart_div(periphClk, baudRate);
}

 void uart2_tx(char ch){
	 /* Make sure transmit data register is empty */
	 while(!(USART2->SR & SR_TXE));
	 /*Write to transfer resgister*/
	 USART2->DR = (ch & 0xFF);
 }
 
 char uart2_rx(void){
	 /* Make sure recieve data register is empty */
	 while(!(USART2->SR & SR_RXNE));
	 /*Read data*/
	 return USART2->DR;
	 
 }
 
 void uart2_tx_string(char *ch){
	 /* Make sure transmit data register is empty */
	 unsigned char j = 0;
	 while(ch[j]!=0){
	 uart2_tx(ch[j]);
		 ++ch;
	 }
 } 
 
 
 
