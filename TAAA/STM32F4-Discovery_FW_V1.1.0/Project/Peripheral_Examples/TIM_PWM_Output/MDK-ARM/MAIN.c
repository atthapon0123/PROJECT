/*============================================================================*/
/*	                        File Name: MAIN.c                                 */
/*============================================================================*/



//	Include header file used in the main function
#include "TAAA.h"


#define PI 3.14159265359
float freq = 0;
float RPM = 0;

PWM pwm 				= PWM_DEFAULTS;
ADCvalue adc = ADC_DEFAULTS; 
PI_C pi_taaa 		= PI_C_DEFAULTS;
DQs dqs_grid 		= DQs_DEFAULTS;
DQs dqs_gen 		= DQs_DEFAULTS;
DQe dqe_grid		= DQe_DEFAULTS;
DQe dqe_gen			= DQe_DEFAULTS;
PLL pll 				= PLL_DEFAULTS;
DACout dacout = DAC_DEFAULTS;
SPIout spiout = SPI_DEFAULTS;

int main(void)
{
		NVIC_Excitation();
		pwm.init(&pwm);
		spiout.init(&spiout);
		adc.init(&adc);

	for(;;);

}
	
//============================================================================
//	Interrupt zone
//============================================================================
void TIM1_UP_TIM10_IRQHandler(void)
{
		spiout.dataout1 = (pll.Theta/(2*PI))*4095;
		spiout.dataout2 = adc.volt_grid_ab;
		spiout.dataout3 = adc.volt_grid_bc;
		spiout.dataout4 = (dqe_grid.VDe*4095)+0x0800;
		spiout.dataout5 = (dqe_grid.VQe*4095)+0x0800;
	
		spiout.update(&spiout);
		
//----------------------------------------------------------------------------
//	Update the ADC Value			
//----------------------------------------------------------------------------
		adc.update(&adc);

//----------------------------------------------------------------------------
//	DQs Transform			
//----------------------------------------------------------------------------	
	/*DQs Grid*/	
		dqs_grid.Vab = (adc.volt_grid_ab_pu);
		dqs_grid.Vbc = adc.volt_grid_bc_pu;
		dqs_grid.calc(&dqs_grid);
	/*DQs Gen */
		dqs_gen.Vab = adc.volt_gen_ab_pu;
		dqs_gen.Vbc = adc.volt_gen_bc_pu;
		dqs_gen.calc(&dqs_gen);
	
//----------------------------------------------------------------------------
//	DQe Transform			
//----------------------------------------------------------------------------	
	/*DQe Grid*/	
		dqe_grid.angle = pll.Theta;
		dqe_grid.VDs   = dqs_grid.VDs ;
		dqe_grid.VQs   = dqs_grid.VQs ;
		dqe_grid.calc(&dqe_grid);
	/*DQe Gen */
		dqe_gen.angle = pll.Theta;
		dqe_gen.VDs   = dqs_gen.VDs ;
		dqe_gen.VQs   = dqs_gen.VQs ;
		dqe_gen.calc(&dqe_gen);

//----------------------------------------------------------------------------
//	Phase Lock Loop Calculation			
//----------------------------------------------------------------------------
		pll.kp = 1.5;
		pll.ki = 0.002;
		pll.input = dqe_grid.VQe; 
		pll.calc(&pll) ;
		
		freq = pll.w/(2*PI);
		RPM = 30*freq;
		
//----------------------------------------------------------------------------
//	PWM Generator			
//----------------------------------------------------------------------------
	/****** PI Controller ******/
	/* Set gain for PI controller */
		pi_taaa.kp = 1.25 ;
		pi_taaa.ki = 50 ; // 0.01/(200e-6)
		pi_taaa.kc = 1;

		pi_taaa.ref = sqrtf( powf(dqe_grid.VDe,2) + powf(dqe_grid.VQe,2) ) ;
		pi_taaa.input = sqrtf( powf(dqe_gen.VDe,2) + powf(dqe_gen.VQe,2) ) ;
		pi_taaa.cal(&pi_taaa);
		
	/****** PWM Generator ******/
		pwm.Vcontrol = 8400 * pi_taaa.Uo;
		pwm.Wcontrol = 8400 * ((int)RPM/2000); 
		pwm.update(&pwm);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
