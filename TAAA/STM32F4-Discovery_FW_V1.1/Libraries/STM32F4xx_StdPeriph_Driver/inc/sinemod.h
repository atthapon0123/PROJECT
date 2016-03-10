#ifndef _SINEMOD_H_
#define _SINEMOD_H_


typedef struct 
	{ float Amplitude;
		float Angle;
		float	sineA;
		float sineB;
		int Hz;
		void (*calc)();
  }SINEMOD;

typedef SINEMOD *SINEMOD_handle ;

/* Default Initializer for the SINEMOD object */	
#define SINEMOD_DEFAULTS {0, \
													0, \
													0, \
													0, \
													0, \
									 				(void (*)(unsigned int))SINEMOD_calc}

/* Prototypes fo the functions in sinemod.h */
void SINEMOD_calc(SINEMOD_handle);
	  
#endif // _SINEMOD_H_
