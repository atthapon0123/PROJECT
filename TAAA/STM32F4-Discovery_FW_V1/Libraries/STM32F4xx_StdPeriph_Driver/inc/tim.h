#ifndef __TIM_H__
#define __TIM_H__
typedef struct {
			float A;
			float B;
	    void (*set)();
			} TIM ;
typedef TIM *TIM_handle;
#define TIM_DEFAULTS		{0,	\
							 0,	\
							 (void (*)(unsigned int))tim_set, \
}
void tim_set(TIM_handle);
#endif
