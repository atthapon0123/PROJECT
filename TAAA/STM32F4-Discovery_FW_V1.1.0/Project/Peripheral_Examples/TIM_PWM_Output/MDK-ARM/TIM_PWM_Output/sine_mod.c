#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "sine_mod.h"
#include "math.h"

#define PI 3.14159265358979

void SINEMOD_calc(SINEMOD *p)
{
				p->sineA=(p->Amplitude*(-cosf(p->Angle)))+p->offset; 
				p->sineB=(p->Amplitude*(-sinf(p->Angle)))+p->offset; 
}
