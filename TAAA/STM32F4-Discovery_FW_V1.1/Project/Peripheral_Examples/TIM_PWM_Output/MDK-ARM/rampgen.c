#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "rampgen.h"

#define PI 3.14159265358979

void RAMPGEN_calc(RAMPGEN *p)
{
//Angle Calculation
			p->Angle += p->StepAngle;
		if(p->Angle>(2*PI))
			p->Angle -= (2*PI);
		else if (p->Angle <(-2*PI))
			p->Angle += (2*PI);
}
