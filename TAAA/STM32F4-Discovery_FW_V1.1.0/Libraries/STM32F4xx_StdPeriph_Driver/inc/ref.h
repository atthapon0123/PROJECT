#ifndef __REF_H__
#define __REF_H__
typedef struct {
			unsigned int vd_ref;
			unsigned int vq_ref;
			void (*cal)();
			} REF ;
typedef REF *REF_handle;
#define REF_DEFAULTS		{0,	\
							 0,	\
							 (void (*)(unsigned int))ref_cal, \
							 }
void ref_cal(REF_handle);
#endif
