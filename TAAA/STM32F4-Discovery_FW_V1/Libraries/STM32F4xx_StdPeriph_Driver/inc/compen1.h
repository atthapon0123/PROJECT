#ifndef __COMPEN1_H__
#define __COMPEN1_H__
typedef struct {
			float input_d;
			float input_q;
			float vd_pi;
			float vq_pi;
			float vd_in;
			float vd_out;
			float wc;
			float vq_in;
			float vq_out;
			float base_c;
			float c;
			void (*cal)();
			} COMPEN1 ;
typedef COMPEN1 *COMPEN1_handle;
#define COMPEN1_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 52.9,	\
							 0.0000024,	\
							 (void (*)(unsigned int))compen1_cal, \
							 }
void compen1_cal(COMPEN1_handle);
#endif
