#ifndef _SOFTSTART_H_
#define _SOFTSTART_H_

#include "stm32f4xx.h"

typedef struct 
	{ float pwm1;
		float pwm2;
		float sineA;
		float sineB;
		float Fin;
		float Fout;
		float t;
		void (*val)();
  }SOFTSTART;

typedef SOFTSTART *SOFTSTART_handle ;

/* Default Initializer for the SOFTSTART object */	
#define SOFTSTART_DEFAULTS {0, \
														0, \
														0, \
														0, \
														0, \
														0, \
														0, \
									 		 		(void (*)(unsigned int))SOFTSTART_val}
//0.000023143

/* Prototypes fo the functions in SOFTSTART.h */
void SOFTSTART_val(SOFTSTART_handle);
	  
#endif // __SOFTSTART_H__
