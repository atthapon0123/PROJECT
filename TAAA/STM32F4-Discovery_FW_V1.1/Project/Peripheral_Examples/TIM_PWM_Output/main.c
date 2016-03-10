#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "PWM.h"
#include "DAC.h"
#include "sine_mod.h"
#include "rampgen.h"
#include "NVIC_DRIVE.h"
#include "math.h"
#define PI 3.14159265358979

float Mod1,Mod2;
unsigned int j; 
int x;

PWM PWM_PP = PWM_DEFAULTS;
DACout DAC_Out = DAC_DEFAULTS;
RAMPGEN rampgen = RAMPGEN_DEFAULTS;
SINEMOD modulate = SINEMOD_DEFAULTS;

int main(void)
{
	/* Configure PD13 for Check Interrupt */
  RCC->AHB1ENR |= 0x00000008; //GPIOD
	GPIOD->MODER |= 0x04000000; //PD13 to OUT mode
	GPIOD->BSRRL = 0x00001000;
	NVIC_2ph();
//---------------------------------------------------------------------
// Initialize PWM function
//---------------------------------------------------------------------
  PWM_PP.init(&PWM_PP);
	
//---------------------------------------------------------------------
//Initialize DAC function	
//----------------------------------------------------------------------
	DAC_Out.init(&DAC_Out);
	
	for(;;);
}


/************************** Interupt *********************************/
void TIM1_UP_TIM10_IRQHandler(void) 
{
GPIO_SetBits(GPIOD,GPIO_Pin_13);
TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	
//----------------------------------------------------------------------------
// Calculate the angle from RAMPGEN function		
//----------------------------------------------------------------------------		
	rampgen.StepAngle = 2*PI/100;
	rampgen.calc(&rampgen);

//----------------------------------------------------------------------------
// Calculate the modulating signal from SINEMOD function			
//----------------------------------------------------------------------------	
	modulate.Amplitude = 0.8*4200;
	modulate.offset = 4200;
	modulate.Angle = rampgen.Angle;
	modulate.calc(&modulate);

//----------------------------------------------------------------------------
// Update the DAC function		
//----------------------------------------------------------------------------				
	DAC_Out.Output1 = modulate.sineA;  
	DAC_Out.Output2 = modulate.sineB; 
	DAC_Out.update(&DAC_Out);
	
//----------------------------------------------------------------------------
// Update the PWM function		
//----------------------------------------------------------------------------
	PWM_PP.cmpr1 = modulate.sineA;
	PWM_PP.cmpr2 = modulate.sineA;
	PWM_PP.cmpr3 = modulate.sineB;
	PWM_PP.cmpr4 = modulate.sineB;
	PWM_PP.update(&PWM_PP);

GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	}



