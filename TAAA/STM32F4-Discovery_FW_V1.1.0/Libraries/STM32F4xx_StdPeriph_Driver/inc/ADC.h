#ifndef __ADC_H__
#define __ADC_H__
typedef struct	
	{ int  err0;
		int  err1;
		int  err2;
		int  err3;
		int  error0;
		int  error1;
		int  error2;
		int  error3;
		int  volt_grid_ab; 
		int  volt_grid_bc;
		int  volt_gen_ab; 
		int  volt_gen_bc;
		float  volt_grid_ab_set0;
		float  volt_grid_bc_set0;
		float  volt_grid_ab_pu;
		float  volt_grid_bc_pu;
		int  volt_gen_ab_set0;
		int  volt_gen_bc_set0;
		float  volt_gen_ab_pu;
		float  volt_gen_bc_pu;
		int  reserve1; 
		int  reserve2;
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
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
											 0x00000000, \
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

