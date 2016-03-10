#ifndef __UNIT_H__
#define __UNIT_H__
typedef struct {
			unsigned int cnt;
			float theta;
			float u_cos;
	    float u_sin;
			void (*cal)();
			} UNIT ;
typedef UNIT *UNIT_handle;
#define UNIT_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 (void (*)(unsigned int))unit_cal, \
}
void unit_cal(UNIT_handle);
#endif

