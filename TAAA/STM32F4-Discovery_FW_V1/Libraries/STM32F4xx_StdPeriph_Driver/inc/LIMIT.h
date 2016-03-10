#ifndef _LIMIT_H_
#define _LIMIT_H_

#include "stm32f4xx.h"

typedef struct 
	{ float Fcom;
		float Hz;
		void (*init)();
  }LIMIT;

typedef LIMIT *LIMIT_handle ;

/* Default Initializer for the LIMIT object */	
#define LIMIT_DEFAULTS {0, \
												0, \
									 		 	(void (*)(unsigned int))LIMIT_init}

/* Prototypes fo the functions in LIMIT.h */
void LIMIT_init(LIMIT_handle);
	  
#endif // __LIMIT_H__
