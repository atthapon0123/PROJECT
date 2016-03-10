#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "softstart.h"
#include "math.h"

void SOFTSTART_val(SOFTSTART *p)
{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
{
		p->pwm1 = 8400;
		p->pwm2 = 8400;	
		
/* Configure Output1-4 State and NState  */
	TIM1->CCER = 0x0001; 						//Output1 State Enable
	TIM1->CCER = 0x0010; 						//Output2 State Enable
	TIM1->CCER = 0x0100; 						//Output3 State Enable
	TIM1->CCER = 0x1000; 						//Output4 State Enable	 
	
	p->t = 0;
}
		else if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1)
{
	p->pwm1 = p->sineA;
	p->pwm2 = p->sineB;

/* Configure Output1-4 State and NState  */
	TIM1->CCER |= 0x0001; 					//Output1 State Enable
	TIM1->CCER |= 0x0004; 					//Output1 NState Enable
	TIM1->CCER |= 0x0010; 					//Output2 State Enable
	TIM1->CCER |= 0x0040; 					//Output2 NState Enable
	TIM1->CCER |= 0x0100; 					//Output3 State Enable
	TIM1->CCER |= 0x0400;				 		//Output3 NState Enable
	TIM1->CCER |= 0x1000; 					//Output4 State Enable	 
	
/* First order function for softstart */
	p->t = p->t+0.032;
	p->Fout = p->Fin*(1-exp(-(p->t/2*pow(10,-1))));
	
}
}
