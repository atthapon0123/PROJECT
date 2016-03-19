#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "sine_mod.h"
#include "math.h"

#define PI 3.14159265358979

void SINEMOD_calc(SINEMOD *p)
{
//Angle Calculation
				p->sineA=(p->Amplitude*(-sinf(p->Angle)))+4200; 
				p->sineB=(p->Amplitude*(-sinf(p->Angle+120)))+4200;
}
