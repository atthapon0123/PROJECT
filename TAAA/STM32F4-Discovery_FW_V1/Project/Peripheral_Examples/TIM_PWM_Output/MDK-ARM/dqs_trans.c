#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "dqs_transform.h"
#include "math.h"

void DQs_calc(DQs *a)
{
	a->VDs = (2*a->Vab/3)+(a->Vbc/3);
	a->VQs = (1/sqrt(3))*(a->Vbc);
}
