#ifndef __DAC_H__
#define __DAC_H__

typedef struct 
	{ int  Output1;
		int  Output2;
		void (*init)();
		void (*update)();
  }DACout;
typedef DACout *DAC_handle ;

/* Default Initializer for the PWM object */	
#define DAC_DEFAULTS { 0x00000000, \
	                     0x00000000, \
									 		(void (*)(unsigned int))DAC_init, \
									 		(void (*)(unsigned int))DAC_update}

/* Prototypes fo the functions in DAC.h */
void DAC_init(DAC_handle);
void DAC_update(DAC_handle);
	  
#endif // __DAC_H__

