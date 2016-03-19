#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "vf_profile.h"
#include "math.h"

void VFPROFILE_calc(VFPROFILE *p)
{
	p->Vcom = sqrt(((pow(p->Rs+p->Fcom*p->Xsl+p->Fcom*p->Xrl*2,2))+(pow(p->Fcom*p->Xsl-p->Rs,2)))
					 /(pow(p->Rs+p->Xsl+2*p->Xrl,2))+(pow(p->Xsl-p->Rs,2)));
}
