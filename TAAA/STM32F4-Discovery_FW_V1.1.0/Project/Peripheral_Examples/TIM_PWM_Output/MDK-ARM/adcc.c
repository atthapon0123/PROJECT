#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "adcc.h"

ADC_InitTypeDef       ADC_InitStructure;
ADC_CommonInitTypeDef ADC_CommonInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

void adcc()
{	
//	/* ADC1 clock enable */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	/* Open Clock for GPIOC and ADC */
	RCC->APB2ENR |= 0x00000100; //ADC
	RCC->AHB1ENR |= 0x00000004; //GPIOC
	
//		/* ADC --> PC4 , PC5*/ 
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* Pin Configuration for ADC */
	GPIOC->MODER |= 0x00000300; //Analog Mode for PC4
	GPIOC->PUPDR |= 0x00000000; //No Pull
	
	
	
	 /* ADC1 regular channel 14 configuration ************************************/
//  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC1->CR1 |= 0x00000000; //Resolutiob 12-bit
	
//  ADC_InitStructure.ADC_ScanConvMode = ENABLE;		//ENABLE
		ADC1->CR1 |= 0x00000080; //Scan mode disable
	
//  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC1->CR2 |= 0x00000002; //Continuous conversion mode enable	
	
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC1->CR2 |= 0x00000000; //None external trigger
	
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC1->CR2 |= 0x00000000; //Data alignment right
	
//  ADC_InitStructure.ADC_NbrOfConversion = 1;
	
  ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_3Cycles);		//3
//		ADC1->SMPR1 |= 0x00000000; //Channel 14 sampling each 3 cycles
		
//  ADC_Cmd(ADC1, ENABLE);
	ADC1->CR2 |= 0x00000001; //ADC1 enable
	
	
}
