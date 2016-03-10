#ifndef _RAMPGEN_H_
#define _RAMPGEN_H_

#include "stm32f4xx.h"

typedef struct 
	{ float Angle;
		float StepAngle;
		void (*calc)();
  }RAMPGEN;

typedef RAMPGEN *RAMPGEN_handle ;

/* Default Initializer for the RAMPGEN object */	
#define RAMPGEN_DEFAULTS {0, \
													0, \
									 		 		(void (*)(unsigned int))RAMPGEN_calc}

/* Prototypes fo the functions in RAMPGEN.h */
void RAMPGEN_calc(RAMPGEN_handle);
	  
#endif // __RAMPGEN_H__
