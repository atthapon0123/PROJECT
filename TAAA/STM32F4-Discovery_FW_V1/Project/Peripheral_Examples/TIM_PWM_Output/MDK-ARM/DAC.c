#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "DAC.h"


	/* -----------------------*/
	/*     DAC Pin Table      */
	/* -----------------------*/
	/*| Channel    |   PIN   |*/
	/* -----------------------*/
	/*| Channel 0  |   PA4   |*/
	/*| Channel 1  |   PA5   |*/
	/* -----------------------*/
	/*      Table End         */
	/* -----------------------*/
	
	
void DAC_init(DACout *p)
{
/* Open Clock GPIOA and DAC */
	RCC->AHB1ENR |= 0x00000001 ; //GPIOA
	RCC->APB1ENR |= 0x20000000 ; //DAC
	
/* Pin Configuration for GPIOA */
	GPIOA->MODER |= 0x00000300 | 0x00000C00 ; //set PA4 and PA5 to Analog mode 
	GPIOA->PUPDR |= 0x00000000 | 0x00000000 ; //set PA4 and PA5 No Pull
	
//===== DAC Channel 1&2 (Ch1 = Pin4 , Ch2 = Pin5)=====//
/* Trigger Configuration for DAC */
	DAC->CR |= 0x00000000 ; // Trigger_None   
	
/* WaveGeneration Configuration for DAC */
  DAC->CR |= 0x00000000 ; // WaveGeneration_None  
	
/* OutputBuffer Configuration for DAC */
  DAC->CR |= 0x00000000 ; // OutputBuffer_Enable

/* Enable the selected DAC channel 1&2 */
  DAC->CR |= 0x00000001 ; //DAC channel1 enable
	DAC->CR |= 0x00010000 ; //DAC channel2 enable
}

void DAC_update(DACout *p)
{
	DAC->DHR12R1 = p->Output1;
	DAC->DHR12R2 = p->Output2;
}
