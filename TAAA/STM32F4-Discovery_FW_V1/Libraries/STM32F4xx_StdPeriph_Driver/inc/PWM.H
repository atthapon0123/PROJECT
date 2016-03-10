#ifndef __PWM_H__
#define __PWM_H__


typedef struct 
	{ 
		int duty;
		int reserve1;
		int reserve2;
		int reserve3;
		void (*init)() ;
		void (*update)();
    } PWM;

typedef PWM *PWM_handle ;

/* Default Initializer for the PWM object */	
#define PWM_DEFAULTS { 0x0000, \
											 0x0000, \
	                     0x0000, \
	                     0x0000, \
											 (void (*)(unsigned int))PWM_Init, \
											 (void (*)(unsigned int))PWM_Update\
										 }

/* Prototypes fo the functions in PWM.h */
void PWM_Init(PWM_handle);
void PWM_Update(PWM_handle);											 
	  
#endif // __PWM_H__

