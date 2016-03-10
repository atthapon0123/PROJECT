#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "spii.h"

  
SPI_InitTypeDef SPI_InitStructure;
void spi_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC->AHB1ENR |= 0x00000001 | 0x00000004; //GPIOA and GPIOC
	RCC->APB1ENR |= 0x00008000;//SPI3
	
  
		/* Pin Configuration for SPI3 */
	GPIOC->MODER |= 0x00200000 | 0x02000000; //PC10 and PC12
	GPIOC->OSPEEDR |= 0x00300000 | 0x03000000; //100MHz for PC10 and PC12
	GPIOC->OTYPER |= 0x00000000 | 0x00000000; //Push Pull
	GPIOC->PUPDR |= 0x00000000 | 0x00000000; //No Pull
  GPIOC->AFR[1] |= 0x00000600 | 0x00060000; //AF6 to PC10 and PC12
	
	
	
//	/* SPI3 FrameSync --> PA15 */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/* Pin Configuration for Framesync */
//	GPIOA->MODER |= 0x40000000; //PA15
//	GPIOA->OSPEEDR|=0xC0000000; 
	GPIOA->AFR[1] |= 0x60000000; //PA15 to framesync

	
	
 	


	SPI3->CR1 |= 0x0104; //Master mode
	SPI3->CR1 |= 0x4000; //1-line unidirectional data selected
	SPI3->CR1 |= 0x0800; //16-bit data
	SPI3->CR1 |= 0x0001; //The second transmit is the first data capture edge
	SPI3->CR1 |= 0x0200; //Software slave management enable
	SPI3->CR1 |= 0x0040; //SPI3 enaable
	SPI3->CRCPR |= 7; //For CRC calculation

}

void delay(__IO uint32_t count) // delay function
	{
   while(count>0)
   {
      count--;
   }
 }

