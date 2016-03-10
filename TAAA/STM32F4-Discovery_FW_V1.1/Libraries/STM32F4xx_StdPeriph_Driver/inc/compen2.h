#ifndef __COMPEN2_H__
#define __COMPEN2_H__
typedef struct {
			float input_d;
			float input_q;
			float id_pi;
			float iq_pi;
			float id_in;
			float id_out;
			float wl;
			float iq_in;
			float iq_out;
			float base_l;
			float l;
			void (*cal)();
			} COMPEN2 ;
typedef COMPEN2 *COMPEN2_handle;
#define COMPEN2_DEFAULTS		{0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 0,	\
							 (void (*)(unsigned int))compen2_cal, \
							 }
void compen2_cal(COMPEN2_handle);
#endif





