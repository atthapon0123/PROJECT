#ifndef __PLL_H__
#define __PLL_H__

typedef struct 
	{ float  V_Qe; 
		float  angle;
		void (*cal)();
  }PLL; 
typedef PLL *PLL_handle ;

/* Default Initializer for ADC */	
#define PLL_DEFAULTS { 0x00000000, \
											 6.28318530718, \
									 		(void (*)(unsigned int))PLL_cal}


void PLL_cal(PLL_handle);
	  
#endif // __PLL_H__
