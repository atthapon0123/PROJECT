#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "transient.h"
#include "math.h"
int t;

void transient_calc(TRANSIENT *p)
{
	t=t+1;
	p->Fout = p->Fin*(1-exp(-(t/1*pow(10,-4))));
}
