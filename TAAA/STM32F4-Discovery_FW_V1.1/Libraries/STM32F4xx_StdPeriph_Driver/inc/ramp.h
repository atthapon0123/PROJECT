#ifndef __RAMP_H__
#define __RAMP_H__
typedef struct {
			float Vref;
			float k1;
			float k2;
			float Vload;
			float target;
			void (*cal)();
			} RAMP ;
typedef RAMP *RAMP_handle;
#define RAMP_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 (void (*)(unsigned int))ramp_cal, \
							 }
void ramp_cal(RAMP_handle);
#endif
