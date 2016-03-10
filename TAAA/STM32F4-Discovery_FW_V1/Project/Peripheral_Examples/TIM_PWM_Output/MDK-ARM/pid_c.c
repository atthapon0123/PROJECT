/*PID controller*/
//File name : pid_c.c 

#include "pid_c.h"
#include "stm32f4_discovery.h"

void pid_c_cal(PID_C *p)
{
	p->error = p->ref-p->input;
	p->Up_out1 = p->Up_out;
	p->Up_out = p->kp*p->error;
	p->Ui_out = p->Ui_out+(p->ki*p->Up_out)+(p->kc*p->Saterr);
	p->Ud_out = p->kd * (p->Up_out - p->Up_out1);
	
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
	
	if(p->Ud_out >= p->limit_up)
	{
		p->Ud_out = p->limit_up;
	}
	else if(p->Ud_out <= p->limit_down)
	{
		p->Ud_out = p->limit_down;
	}
	else
	{
		p->Ud_out = p->Ud_out;
	}
	
	// cal presat output
	p->Outpresat = p->Up_out + p->Ui_out + p->Ud_out ;
	
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
