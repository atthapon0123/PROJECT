#ifndef _DQs_Transform_H_
#define _DQs_Transform_H_

#include "stm32f4xx.h"

typedef struct 
	{ float Vab;
		float Vbc;
		float VDs;
		float VQs;
		void (*calc)();
  }DQs;

typedef DQs *DQs_handle ;

/* Default Initializer for the VDQs object */	
#define DQs_DEFAULTS {		0, \
													0, \
													0, \
													0, \
									 				(void (*)(unsigned int))DQs_calc}

/* Prototypes fo the functions in vdqs.h */
void DQs_calc(DQs_handle);
	  
#endif // _DQs_Transform_H_
