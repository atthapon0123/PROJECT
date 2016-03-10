/*============================================================================*/
/*	                        File Name: MAIN.c                                 */
/*============================================================================*/



//	Include header file used in the main function
#include "TAAA.h"


#define PI 3.14159265359
float freq = 0;

PWM pwm 				= PWM_DEFAULTS;
ADCvalue adcdim = ADC_DEFAULTS; 
PI_C pi_taaa 		= PI_C_DEFAULTS;
DQs dqs_grid 		= DQs_DEFAULTS;
DQs dqs_gen 		= DQs_DEFAULTS;
DQe dqe_grid		= DQe_DEFAULTS;
DQe dqe_gen			= DQe_DEFAULTS;
//PLL pll 				= PLL_DEFAULTS;
TRAPE trape = TRAPE_DEFAULTS; //Integrate Function
PI_C_NR pi_c_noref = PI_C_NR_DEFAULTS;//PI controller
DACout dacout = DAC_DEFAULTS;
SPIout spiout = SPI_DEFAULTS;

int main(void)
	{
		NVIC_Excitation();
		pwm.init(&pwm);
		adcdim.init(&adcdim);
//		dacout.Output1 = 1000;
//		dacout.init(&dacout);
		spiout.init(&spiout);
			
	for(;;);
	
}
	
//============================================================================
//	Interrupt zone
//============================================================================
void TIM1_UP_TIM10_IRQHandler(void)
{
  
//----------------------------------------------------------------------------
//	Update the ADC Value			
//----------------------------------------------------------------------------
		adcdim.update(&adcdim);
	
//----------------------------------------------------------------------------
//	DQs Transform			
//----------------------------------------------------------------------------	
	
	/*DQs Grid*/	
		dqs_grid.Vab = (adcdim.volt_grid_ab);
		dqs_grid.Vbc = adcdim.volt_grid_bc;
		dqs_grid.calc(&dqs_grid);
	/*DQs Gen */
		dqs_gen.Vab = adcdim.volt_gen_ab;
		dqs_gen.Vbc = adcdim.volt_gen_bc;
		dqs_gen.calc(&dqs_gen);
	
//----------------------------------------------------------------------------
//	DQe Transform			
//----------------------------------------------------------------------------	
	
	/*DQe Grid*/	
		dqe_grid.angle = trape.output;
		dqe_grid.VDs   = dqs_grid.VDs ;
		dqe_grid.VQs   = dqs_grid.VQs ;
		dqe_grid.calc(&dqe_grid);
	/*DQe Gen */
		dqe_gen.angle = trape.output;
		dqe_gen.VDs   = dqs_gen.VDs ;
		dqe_gen.VQs   = dqs_gen.VQs ;
		dqe_gen.calc(&dqe_gen);
	
//----------------------------------------------------------------------------
//	Phase Lock Loop Calculation			
//----------------------------------------------------------------------------

		pi_c_noref.kp = 0.0477/4;
		pi_c_noref.ki = 0.25/4;
		pi_c_noref.input = dqe_grid.VQe; 
		pi_c_noref.cal(&pi_c_noref) ;
		
		/* Integrate */
		trape.input = (pi_c_noref.Uo+1) * 100 * PI ;
		trape.calc(&trape);
		
		freq = trape.input/(2*PI);
		
//----------------------------------------------------------------------------
//	PWM Generator			
//----------------------------------------------------------------------------
	
	/****** PI Controller ******/
	/* Set gain for PI controller */
		pi_taaa.kp = 1.25 ;
		pi_taaa.ki = 50 ; // 0.01/(200e-6)
		pi_taaa.kc = 1 ;
		
	//pi_taaa.ref = sqrtf((dqe_grid.VDe*dqe_grid.VDe)+(dqe_grid.VQe*dqe_grid.VQe));
	//pi_taaa.input = sqrtf((dqe_gen.VDe*dqe_gen.VDe)+(dqe_gen.VQe*dqe_gen.VQe));
		pi_taaa.ref = sqrtf( powf(dqe_grid.VDe,2) + powf(dqe_grid.VQe,2) ) ;
		pi_taaa.input = sqrtf( powf(dqe_gen.VDe,2) + powf(dqe_gen.VQe,2) ) ;
		pi_taaa.cal(&pi_taaa);
		
	/****** PWM Generator ******/
		pwm.duty = 8400 * pi_taaa.Uo ;
		pwm.update(&pwm);
		
//		dacout.Output1 = dqe_grid.VDe;
//		dacout.Output2 = adcdim.volt_grid_ab;
//		dacout.update(&dacout);
		spiout.dataout1 = adcdim.volt_gen_ab;
		spiout.dataout2 = dqs_grid.Vbc;
		spiout.dataout3 = dqs_grid.VDs;
		spiout.dataout4 = dqs_grid.VQs;
		spiout.update(&spiout);
//----------------------------------------------------------------------------
	
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
