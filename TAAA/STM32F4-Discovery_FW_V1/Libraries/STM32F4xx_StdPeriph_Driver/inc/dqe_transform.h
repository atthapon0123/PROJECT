#ifndef _DQe_Transform_H_
#define _DQe_Transform_H_

#include "stm32f4xx.h"

typedef struct 
	{ 
		float VDs;
		float VQs;
		float VDe;
		float VQe;
		float angle;
		void (*calc)();
  }DQe;

typedef DQe *DQe_handle ;

/* Default Initializer for the VDQs object */	
#define DQe_DEFAULTS {		0, \
													0, \
													0, \
													0, \
													0, \
									 				(void (*)(unsigned int))DQe_calc}

/* Prototypes fo the functions in vdqs.h */
void DQe_calc(DQe_handle);
	  
#endif // _VDQe_Transform_H_
