#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "LCD.h"

void LCD_init(LCD *p)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
/*	Open Clock 	*/
	RCC->AHB1ENR |= 0x00000003; //GPIOA and GPIB
	RCC->APB2ENR |= 0x00001000;//SPI1
	
/* 	Pin Configuration for SPI1	*/
	GPIOB->MODER |= 0x00000880; //PB3 and PB5 to AF mode
	GPIOB->OSPEEDR |= 0x00000CC0; //100 MHz to PB3 and PB5

/*	SPI1 FrameSync --> PA4	*/ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/*	Configure AF5	*/
	GPIOA->AFR[0] |= 0x00050000; //AF5 to PA4
	GPIOB->AFR[0] |= 0x00505000; //PB3 and PB5 to AF5
	
//===== Configuration for SPI1 =====//
	SPI1->CR1 |= 0x0104; //Master mode
	SPI1->CR1 |= 0xC000; //1-line unidirectional data selected
	SPI1->CR1 |= 0x0800; //16-bit data
	SPI1->CR1 |= 0x0001; //The second transmit is the first data capture edge
	SPI1->CR1 |= 0x0200; //Software slave management enable
	SPI1->CR1 |= 0x0040; //SPI1 enaable
	SPI1->CRCPR |= 7; //For CRC calculation
}

// 	Delay function
void delay_lcd(__IO uint32_t count) 
	{
   while(count>0)
   {
      count--;
   }
	}

void LCD_update(LCD *p)
{
/*	SPI1 Channel 1	*/
	GPIOA->BSRRH |= 0x0010;
  SPI1->DR = 0x0000 + p->lcd1;
	SPI1->SR |= 0x0002;
 	delay_lcd(1000);
 	GPIOA->BSRRL |= 0x0010;
	
/*	SPI1 Channel 2	*/
	GPIOA->BSRRH |= 0x0010;
  SPI1->DR = 0x1000 + p->lcd2;
	SPI1->SR |= 0x0002;
 	delay_lcd(1000);
 	GPIOA->BSRRL |= 0x0010;
	
	/*	SPI1 Channel 3	*/
	GPIOA->BSRRH |= 0x0010;
  SPI1->DR = 0x2000 + p->lcd3;
	SPI1->SR |= 0x0002;
 	delay_lcd(1000);
 	GPIOA->BSRRL |= 0x0010;
	
	/*	SPI1 Channel 4	*/
	GPIOA->BSRRH |= 0x0010;
  SPI1->DR = 0x3000 + p->lcd4;
	SPI1->SR |= 0x0002;
 	delay_lcd(1000);
 	GPIOA->BSRRL |= 0x0010;
}
	
