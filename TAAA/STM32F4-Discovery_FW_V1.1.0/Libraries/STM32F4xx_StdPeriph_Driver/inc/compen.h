#ifndef __COMPEN_H__
#define __COMPEN_H__
typedef struct {
			unsigned int xl;
			unsigned int zb;
			unsigned int vc_d;
			unsigned int vc_q;
			unsigned int id;
			unsigned int iq;
			void (*cal)();
			} COMPEN ;
typedef COMPEN *COMPEN_handle;
#define COMPEN_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 (void (*)(unsigned int))compen_cal, \
}
void compen_cal(COMPEN_handle);
#endif

