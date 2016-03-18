/*============================================================================*/
/*	                        File Name: PLL.c                                  */
/*============================================================================*/
#include "stm32f4_discovery.h"
#include "stm32f4xx.h" 
#include "PLL.h"

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

/*Calculate Phase Lock Loop Function*/
void pll_calc(PLL *p)
{
		
		//Error
		p->Err = p->input;

	// PI compute
		p->Up_out = p->kp*p->Err;
		p->Ui_out = p->Ui_out+(p->ki*p->Up_out);

		// cal presat output
		p->Outpresat = p->Up_out + p->Ui_out;

		//Anti Windup
		if(p->Outpresat > p->limit_up)
		{
			p->PIout = p->limit_up;
		}
		else if(p->Outpresat < p->limit_down)
		{
			p->PIout = p->limit_down;
		}
		else
		{
			p->PIout = p->Outpresat;
		}
		
		p->w = (p->PIout+1)*100*PI;

		//integral
		p->Theta = p->Theta + (p->step*p->w);
		

		if( p->Theta > (2*PI) || p->Theta < 0)
		{
			if (p->Theta > 2*PI)
			{
				p->Theta = p->Theta - (2*PI);
			}
			else if(p->Theta < (-2*PI))
			{
				p->Theta = p->Theta + (2*PI);
			}
		}

}
