#ifndef __PI_C_H__
#define __PI_C_H__
typedef struct {
			float ref;
			float error;
			float Up_out;
			float Ui_out;
			float input;
			float kp;
			float ki;
			float limit_up;
			float limit_down;
			float Uo;
			float Outpresat;
			float Saterr;
			float kc;
			void (*cal)();
			} PI_C ;
typedef PI_C *PI_C_handle;
#define PI_C_DEFAULTS		{0,	\
							 0,	\
							 0,	\
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
							 (void (*)(unsigned int))pi_c_cal, \
							 }
void pi_c_cal(PI_C_handle);								 
#endif
