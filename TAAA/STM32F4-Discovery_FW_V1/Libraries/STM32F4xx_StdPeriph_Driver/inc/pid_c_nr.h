#ifndef __PID_C_NR_H__
#define __PID_C_NR_H__
typedef struct {
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
			} PID_C_NR ;
typedef PID_C_NR *PID_C_NR_handle;
#define PID_C_NR_DEFAULTS	{0,	\
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
							 (void (*)(unsigned int))pid_c_nr_cal, \
							 }
void pid_c_nr_cal(PID_C_NR_handle);												 
#endif
