#ifndef __TEST_H__
#define __TEST_H__
typedef struct {
			unsigned int A;
			unsigned int B;
			void (*init)();
			void (*cal)();
			} TEST ;
typedef TEST *TEST_handle;
#define TEST_DEFAULTS		{0,	\
							 0,	\
							 (void (*)(unsigned int))test_init, \
							 (void (*)(unsigned int))test_cal, \
							 }
void test_init(TEST_handle);
void test_cal(TEST_handle);
#endif
