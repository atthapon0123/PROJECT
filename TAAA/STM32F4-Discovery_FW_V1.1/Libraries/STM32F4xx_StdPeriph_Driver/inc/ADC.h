#ifndef __ADC_H__
#define __ADC_H__

typedef struct 
	{ float  volt_grid_ab; 
		float  volt_grid_bc;
		float  volt_gen_ab; 
		float  volt_gen_bc;
		float  reserve1; 
		float  reserve2;
		void (*init)();
		void (*update)();
  }ADCvalue; 
typedef ADCvalue *ADC_handle ;

/* Default Initializer for ADC */	
#define ADC_DEFAULTS { 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
									 		(void (*)(unsigned int))ADC_init, \
									 		(void (*)(unsigned int))ADC_update}

/* Prototypes fo the functions in ADC.h */
void ADC_init(ADC_handle);
void ADC_update(ADC_handle);
	  
#endif // __ADC_H__

