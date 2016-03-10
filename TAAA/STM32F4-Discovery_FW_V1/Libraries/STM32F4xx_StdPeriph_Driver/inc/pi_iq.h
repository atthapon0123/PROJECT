#ifndef __PI_IQ_H__
#define __PI_IQ_H__
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
			float Saterr;
			float Outpresat;
			float kc;
			void (*cal)();
			} PI_IQ ;
typedef PI_IQ *PI_IQ_handle;
#define PI_IQ_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 1.5,	\
							 -1.5,	\
							 0,	\
							 0,	\
							 0,	\
							 100,	\
							 (void (*)(unsigned int))pi_iq_cal, \
							 }
void pi_iq_cal(PI_IQ_handle);
#endif