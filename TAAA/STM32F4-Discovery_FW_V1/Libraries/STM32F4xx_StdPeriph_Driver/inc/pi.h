#ifndef __PI_H__
#define __PI_H__
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
			void (*cal)();
			} PI ;
typedef PI *PI_handle;
#define PI_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 1.5,	\
							 -1.5,	\
							 0,	\
							 (void (*)(unsigned int))pi_cal, \
							 }
void pi_cal(PI_handle);
#endif
