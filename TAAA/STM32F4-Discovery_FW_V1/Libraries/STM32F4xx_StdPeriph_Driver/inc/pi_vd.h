#ifndef __PI_VD_H__
#define __PI_VD_H__
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
			} PI_VD ;
typedef PI_VD *PI_VD_handle;
#define PI_VD_DEFAULTS		{0,	\
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
							 (void (*)(unsigned int))pi_vd_cal, \
							 }
void pi_vd_cal(PI_VD_handle);
#endif
