#ifndef __PLL_H__
#define __PLL_H__
typedef struct {
			float input;
			float ref;
			float Up_out;
			float Ui_out;
			float kp;
			float ki;
			float limit_up;
			float limit_down;
			float PIout;
			float w;
			float Err;
			float Outpresat;
			float Saterr;
			float Theta;
			float step;
			void (*calc)();
			} PLL ;
typedef PLL *PLL_handle;
#define PLL_DEFAULTS	{0,0,0,0,0,0,	\
							 1,-1,	\
							 0,	\
							 0,	\
							 0,	\
							 0, \
							 0, \
							 0, \
							 0.0002, \
							 (void (*)(unsigned int))pll_calc, \
							 }
void pll_calc(PLL_handle);								 
#endif
