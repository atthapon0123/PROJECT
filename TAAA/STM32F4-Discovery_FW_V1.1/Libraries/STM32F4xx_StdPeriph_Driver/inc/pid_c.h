#ifndef __PID_C_H__
#define __PID_C_H__
typedef struct {
			float ref;
			float error;
			float Up_out;
			float Ui_out;
	    float Ud_out;
	    float Up_out1;
			float input;
			float kp;
			float ki;
    	float kd;
			float limit_up;
			float limit_down;
			float Uo;
			float Outpresat;
			float Saterr;
			float kc;
			void (*cal)();
			} PID_C ;
typedef PID_C *PID_C_handle;
#define PID_C_DEFAULTS		{0,	\
							 0,	\
							 0, \
							 0, \
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
							 (void (*)(unsigned int))pid_c_cal, \
							 }
void pid_c_cal(PID_C_handle);												 
#endif
