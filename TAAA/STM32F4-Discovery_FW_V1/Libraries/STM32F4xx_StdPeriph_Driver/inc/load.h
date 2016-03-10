#ifndef __LOAD_H__
#define __LOAD_H__
typedef struct {
			float vd_load;
			float vq_load;
			float id_load;
			float iq_load;
			float l_sin;
			float l_cos;
			float v;
			float qv;
			float i;
			float qi;
			void (*cal)();
			} LOAD ;
typedef LOAD *LOAD_handle;
#define LOAD_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 (void (*)(unsigned int))load_cal, \
							 }
void load_cal(LOAD_handle);
#endif

