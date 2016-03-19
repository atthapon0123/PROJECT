#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "SPI.h"

uint16_t pos = 0;
uint16_t output[8]= {0,0,0,0,0,0,0,0};

void SPI_init(SPIout *p)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
/*	Open Clock 	*/
	RCC->AHB1ENR |= 0x00000001 | 0x00000004; //GPIOA and GPIOC
	RCC->APB1ENR |= 0x00008000;//SPI3
	
/* 	Pin Configuration for SPI3	*/
	GPIOC->MODER |= 0x00200000 | 0x02000000; //PC10 and PC12
	GPIOC->OSPEEDR |= 0x00300000 | 0x03000000; //100MHz for PC10 and PC12
	GPIOC->OTYPER |= 0x00000000 | 0x00000000; //Push Pull
	GPIOC->PUPDR |= 0x00000000 | 0x00000000; //No Pull

	
/*	SPI3 FrameSync --> PA15	*/ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/*	Configure AF6	*/
	GPIOC->AFR[1] |= 0x00000600 | 0x00060000; //AF6 to PC10 and PC12
	GPIOA->AFR[1] |= 0x60000000; //PA15 to framesync
	
//===== Configuration for SPI3 =====//
	SPI3->CR1 |= 0x0104; //Master mode
	SPI3->CR1 |= 0xC000; //1-line unidirectional data selected
	SPI3->CR1 |= 0x0800; //16-bit data
	SPI3->CR1 |= 0x0001; //The second transmit is the first data capture edge
	SPI3->CR1 |= 0x0200; //Software slave management enable
	SPI3->CR1 |= 0x0040; //SPI3 enaable
	SPI3->CRCPR |= 7; //For CRC calculation
}


// 	Delay function
void delay_ms(__IO uint32_t count) 
	{
   while(count>0)
   {
      count--;
   }
	}


void SPI_update(SPIout *p)
{	
	output[0] =  (0x0000+ p->dataout1);
	output[1] =  (0x1000+ p->dataout2);
	output[2] =  (0x2000+ p->dataout3);
	output[3] =  (0x3000+ p->dataout4);
	output[4] =  (0x4000+ p->dataout5);
	output[5] =  (0x5000+ p->dataout6);
	output[6] =  (0x6000+ p->dataout7);
	output[7] =  (0x7000+ p->dataout8);
	
	while(pos <=7)
	{
		GPIOA->BSRRH |= 0x8000;
		SPI3->DR = output[pos];
		SPI3->SR = 0x0002;
		pos++;
		delay_ms(50);
		GPIOA->BSRRL |= 0x8000;
		delay_ms(50);
	}
		pos=0;
	 
}
	
