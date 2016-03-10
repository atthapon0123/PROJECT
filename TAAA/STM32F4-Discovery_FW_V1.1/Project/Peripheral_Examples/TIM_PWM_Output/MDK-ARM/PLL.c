/*============================================================================*/
/*	                        File Name: PLL.c                                  */
/*============================================================================*/
#include "stm32f4_discovery.h"
#include "stm32f4xx.h" 
#include "PLL.h"
#include "math.h"
#include "trape.h"
#include "pi_c_nr.h"


/*****************************************************************************************/
/*                   _______________             ______         _________         _____  */
/*                  |               |           |      |       |         |       |  1  | */
/*  VQe Grid ======>| PI CONTROLLER |=== Uo ===>|  +1  |======>| *100*PI |======>|  -  | */
/*                  |_______________|           |______|       |_________|       |  S  | */
/*                                                                               |_____| */
/*                                                                                  V    */
/*         |<========================================================================    */
/*         V                   _____                                                     */
/*         ====== output ====>|     |                                                    */
/*                  2*PI ====>| MOD |=====> angle                                        */
/*                            |_____|                                                    */
/*                                                                                       */
/*****************************************************************************************/

#define PI 3.14159265359
TRAPE trape = TRAPE_DEFAULTS; //Integrate Function
PI_C_NR pi_c_noref = PI_C_NR_DEFAULTS; //PI controller

/*Calculate Phase Lock Loop Function*/
void PLL_cal(PLL *p)
{


	/* PI controller */
	pi_c_noref.kp = 0.0125;
	pi_c_noref.ki = 0.25;
	pi_c_noref.input = p->V_Qe ; 
	pi_c_noref.cal(&pi_c_noref) ;
		
	/* Integrate */
	trape.input = (pi_c_noref.Uo+1) * 100 * PI ;
	trape.calc(&trape);
	
//	/* Angle Modulation with 2*PI */
//	p->angle = fmodf(trape.output,2*PI);
	
//	p->angle = trape.output ;
//		if(p->angle>(2*PI))
//			p->angle -= (2*PI);
//		else if (p->angle <(-2*PI))
//			p->angle += (2*PI);
//		else 
//			p->angle = p->angle ;
}
