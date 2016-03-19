#include "stm32f4xx.h"
typedef struct
	{	
		uint16_t i;
		uint16_t w=0;
		uint16_t x1=0;
		uint16_t x2=0;
		uint16_t x12=0;
		uint16_t ma;
		uint16_t ma1;
		uint16_t z1;
		uint16_t z2;
		uint16_t z12;
		uint16_t vd;
		uint16_t vq;
		uint16_t adc_val=0;
		uint16_t adc_val1=0;
		
	}Sine_TypeDef;
#define ptr1  ((uint16_t)0x0000)
void sine_config();
					