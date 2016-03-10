/*PI controller "No Reference" */
//File name : pi_c_nr.c

#include "pi_c_nr.h"
#include "stm32f4_discovery.h"

void pi_c_nr_cal(PI_C_NR *p)
{
	p->Up_out = p->kp*p->input;
	p->Ui_out = p->Ui_out+(p->ki*p->Up_out)+(p->kc*p->Saterr);
	
	if(p->Ui_out >= p->limit_up)
	{
		p->Ui_out = p->limit_up;
	}
	else if(p->Ui_out <= p->limit_down)
	{
		p->Ui_out = p->limit_down;
	}
	else
	{
		p->Ui_out = p->Ui_out;
	}
	
	// cal presat output
	p->Outpresat = p->Up_out + p->Ui_out;
	
	//Anti Windup
	if(p->Outpresat >= p->limit_up)
	{
		p->Uo = p->limit_up;
	}
	else if(p->Outpresat <= p->limit_down)
	{
		p->Uo = p->limit_down;
	}
	else
	{
		p->Uo = p->Outpresat;
	}
	//cal saterr
	p->Saterr = p->Uo - p->Outpresat;
}

