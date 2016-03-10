//============================================================================
//	File Name: TPIM
//============================================================================

//	Include header file used in the main function
#include "TPIM.h"

#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "PWM.h"
#include "ADC.h"
#include "NVIC_DRIVE.h"
#include "pi_c.h"

PWM pwm = PWM_DEFAULTS;
ADCvalue adcdim = ADC_DEFAULTS; 
PI_C pic = PI_C_DEFAULTS;


int main(void)
	{
	NVIC_2ph();
	pwm.init(&pwm);
	adcdim.init(&adcdim);
	for(;;);
	
}
	
void TIM1_UP_TIM10_IRQHandler(void)
{
  pwm.X=8400*adcdim.Rvalue/4095;
	pwm.Y=8400-(8400*adcdim.Rvalue/4095);
  pwm.update(&pwm);
	adcdim.update(&adcdim);
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
