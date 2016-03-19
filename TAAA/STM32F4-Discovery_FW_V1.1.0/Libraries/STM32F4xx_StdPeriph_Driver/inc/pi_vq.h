#ifndef __PI_VQ_H__
#define __PI_VQ_H__
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
			} PI_VQ ;
typedef PI_VQ *PI_VQ_handle;
#define PI_VQ_DEFAULTS		{0,	\
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
							 (void (*)(unsigned int))pi_vq_cal, \
							 }
void pi_vq_cal(PI_VQ_handle);
#endif