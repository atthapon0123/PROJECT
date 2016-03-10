/*============================================================================*/
/*	                        File Name: PWM.c                                  */
/*============================================================================*/
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "PWM.h"

void PWM_Init(PWM *p)
{
	
/*****************************     GPIO SETUP FOR PWM     *******************************/		
/* Configure RCC for GPIO */
	RCC->AHB1ENR |=  0x00000001 |0x00000002 | 0x00000010 ; // GPIOA | GPIOB | GPIOE
	
/* Configure GPIOx Pin for PWM */
	GPIOA->MODER |= 0x00200000; //PA10 to AF mode
	GPIOB->MODER |= 0x80000000; //PB15 to AF mode
	GPIOE->MODER |= 0x00020000| 0x00080000| 0x00200000| 0x00800000 | 0x02000000 
							 | 0x08000000 | 0x20000000 ; //PE8-14 to AF mode
	
/* Configure GPIOx Speed for PWM */
	GPIOA->OSPEEDR |= 0x00300000; //PA10 to High Speed
	GPIOB->OSPEEDR |= 0xC0000000; //PB15 to High Speed
	GPIOE->OSPEEDR |= 0x00030000| 0x000C0000| 0x00300000 | 0x00C00000 | 0x03000000 
								 | 0x0C000000 | 0x30000000 ; //PE8-14 to High Speed
	
/* Configure GPIOx Output Type for PWM */
	GPIOA->OTYPER |= 0x00000000; //PushPull  
  GPIOB->OTYPER |= 0x00000000; //PushPull  
	GPIOE->OTYPER |= 0x00000000; //PushPull
	
/* Configure GPIOx PullUp PullDown for PWM */
	GPIOA->PUPDR |= 0x00000000; //No Pull
	GPIOB->PUPDR |= 0x00000000; //No Pull
	GPIOE->PUPDR |= 0x00000000; //No Pull
	
/* Configure GPIOx to Alternate Function 1 */
  GPIOA->AFR[1] |= 0x00000100 ; //PA10 to AF1
  GPIOB->AFR[1] |= 0x10000000 ; //PB15 to AF1
  GPIOE->AFR[1] |= 0x00000001 | 0x00000010 | 0x00000100| 0x00001000 | 0x00010000 
								| 0x00100000 | 0x01000000; //PE8-14 to AF1
	 
/* Configure PB5 for switch soft start */
	GPIOB->PUPDR |= 0x00000800; //Configure GPIOB PullDown

/***************************     TIMER 1 BASE FOR PWM    ************************************/	
/* Configure RCC for TIM1 */
	RCC->APB2ENR |= 0x00000001; //TIM1 Enable
		
/* Configure CouterMode for TIM1 */
  TIM1->CR1 |= 0x0020; //CenterAligned1
	 
	TIM1->CNT = 8400;
	 
/* Configure Period for TIM1 */
	TIM1->ARR = 8400;

/* Configure ClockDivision for TIM1 */
	TIM1->CR1 |= 0x0000;
	
/* Configure Prescaler for TIM1 */
	TIM1->PSC = 1;		
	
/* Configure RepetitionCouter for TIM1 */
	TIM1->RCR = 1;				

/*************************     TIMER OUTPUT COMPARE FOR PWM    **************************/	
/* Configure OC mode for PWM */
  TIM1->CCMR1 |= 0x0070; //Output Compare1 mode PWM2
	TIM1->CCMR1 |= 0x7000; //Output Compare2 mode PWM2
	TIM1->CCMR2 |= 0x0070; //Output Compare3 mode PWM2
	TIM1->CCMR2 |= 0x7000; //Output Compare4 mode PWM2
	 
///* Configure Output1-4 State and NState  */
  TIM1->CCER |= 0x0001; //Output1 State Enable
  TIM1->CCER |= 0x0004; //Output1 NState Enable
  TIM1->CCER |= 0x0010; //Output2 State Enable
  TIM1->CCER |= 0x0040; //Output2 NState Enable
	TIM1->CCER |= 0x0100; //Output3 State Enable
  TIM1->CCER |= 0x0400; //Output3 NState Enable
	TIM1->CCER |= 0x1000; //Output4 State Enable	 

/* Configure Output Compare1-4 IdleState and NIdleState */
  TIM1->CR2 |= 0x0100; //OC1 Set for IdleState,Reset for NIdleState  
  TIM1->CR2 |= 0x0400; //OC2 Set for IdleState,Reset for NIdleState 
  TIM1->CR2 |= 0x1000; //OC3 Set for IdleState,Reset for NIdleState 	 
  TIM1->CR2 |= 0x4000; //OC4 Set for IdleState,Reset for NIdleState 	 
	 
/* Configure Output Compare1-4 Preload */
  TIM1->CCMR1 |= 0x0008; //OC1 Preload Enable
  TIM1->CCMR1 |= 0x0800; //OC2 Preload Enable
	TIM1->CCMR2 |= 0x0008; //OC3 Preload Enable
	TIM1->CCMR2 |= 0x0800; //OC4 Preload Enable
	 
/*************************     TIMER DEADTIME FOR PWM    **************************/	
/* Configure OSSR and OSSI  */
  TIM1->BDTR |= 0x0800; //Enable Off-State Selection for Run mode
  TIM1->BDTR |= 0x0400; //Enable Off-State Selection for Idle mode
	 
/* Configure Lock level */
	TIM1->BDTR |= 0x0100; //Lock Configuration Level 1
	 
/* Configure Dead Time Value */
	TIM1->BDTR = 0x001F;//PWM_mod->DeadTime; //Value between 0x0001-0x00FF
	
/* Configure Break Polarity */
	TIM1->BDTR |= 0x2000; //Break Polarity High
	 
/* Confiagure Automatic Output */
	TIM1->BDTR |= 0x4000; //Automatic Output Enable 
	
/************************************************************************************************/	 	 
/* Set the ARR Preload Bit */
	TIM1->CR1 |= 0x0080; //Auto-reload preload enable
		
/* Enable the TIM Counter */
	TIM1->CR1 |= 0x0001; //Counter enable
		
/* Enable the TIM Main Output */
	TIM1->BDTR |= 0x8000; //PWM Output enable
		
/* Enable the Interrupt sources */
	TIM1->SR |= 0x0001; // Update interrupt Flag
	TIM1->DIER |= 0x0001; //Interrupt Update Enable
}

void PWM_Update(PWM *p)
{
/* Modulation with TIM1 CH1-4 */
		TIM1->CCR1 = p->duty;					    //Pulse Value for CH1
//	TIM1->CCR2 = p->reserve1;					//Pulse Value for CH2
//	TIM1->CCR3 = p->reserve2;					//Pulse Value for CH3
//  TIM1->CCR4 = p->reserve3;					//Pulse Value for CH4 
}
