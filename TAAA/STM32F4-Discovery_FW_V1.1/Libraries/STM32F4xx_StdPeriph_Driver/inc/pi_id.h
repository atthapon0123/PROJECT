#ifndef __PI_ID_H__
#define __PI_ID_H__
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
			} PI_ID ;
typedef PI_ID *PI_ID_handle;
#define PI_ID_DEFAULTS		{0,	\
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
							 (void (*)(unsigned int))pi_id_cal, \
							 }
void pi_id_cal(PI_ID_handle);
#endif