#ifndef __BACK_H__
#define __BACK_H__
typedef struct {
			float vd;
			float vq;
			float l_sin;
			float l_cos;
			float v;
			float qv;
			float id;
			float iq;
			void (*cal)();
			} BACK ;
typedef BACK *BACK_handle;
#define BACK_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 (void (*)(unsigned int))back_cal, \
							 }
void back_cal(BACK_handle);
#endif
