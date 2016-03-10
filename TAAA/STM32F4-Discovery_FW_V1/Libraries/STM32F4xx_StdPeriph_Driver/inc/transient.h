#ifndef __TRANSIENT_H__
#define __TRANSIENT_H__

typedef struct 
	{ float Fout;
		float Fin;
		void (*calc)();
  }TRANSIENT; 
typedef TRANSIENT *TRANSIENT_handle ;

/* Default Initializer for transient */	
#define TRANSIENT_DEFAULTS { 0x00000000, \
														 0x00000000, \
									 		(void (*)(unsigned int))transient_calc}

/* Prototypes fo the functions in transient.h */
void transient_calc(TRANSIENT_handle);
	  
#endif // __TRANSIENT_H__
