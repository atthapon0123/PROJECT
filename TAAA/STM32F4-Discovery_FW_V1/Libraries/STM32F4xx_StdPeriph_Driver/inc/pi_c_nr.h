#ifndef __PI_C_NR_H__
#define __PI_C_NR_H__
typedef struct {
			float input;
			float Up_out;
			float Ui_out;
			float kp;
			float ki;
			float limit_up;
			float limit_down;
			float Uo;
			float Outpresat;
			float Saterr;
			float kc;
			void (*cal)();
			} PI_C_NR ;
typedef PI_C_NR *PI_C_NR_handle;
#define PI_C_NR_DEFAULTS	{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 1,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 100,	\
							 (void (*)(unsigned int))pi_c_nr_cal, \
							 }
void pi_c_nr_cal(PI_C_NR_handle);								 
#endif
