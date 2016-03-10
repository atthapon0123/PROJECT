#ifndef _TRAPE_H_
#define _TRAPE_H_

typedef struct 
	{ 
		float output;
		float input;
		float input_1;
		float step;
		void (*calc)();
  }TRAPE;

typedef TRAPE *TRAPE_handle ;

/* Default Initializer for the VDQs object */	
#define TRAPE_DEFAULTS {	0, \
													0, \
													0, \
													0.0002, \
									 				(void (*)(unsigned int))TRAPE_calc}

/* Prototypes fo the functions in vdqs.h */
void TRAPE_calc(TRAPE_handle);
	  
#endif // _TRAPE_H_
