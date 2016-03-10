#ifndef __VFPROFILE_H__
#define __VFPROFILE_H__


typedef struct 
	{ float Rs;
		float Xsl;
		float Xrl;
		float Vcom;
		float Fcom;
		void (*calc)();
  }VFPROFILE;

typedef VFPROFILE *VFPROFILE_handle ;

/* Default Initializer for the V/F Profile object */	
#define VFPROFILE_DEFAULTS {0, \
													0, \
													0, \
													0, \
													0, \
									 		 		(void (*)(unsigned int))VFPROFILE_calc}

/* Prototypes fo the functions in VF_PROFILE.h */
void VFPROFILE_calc(VFPROFILE_handle);



#endif //__VFPROFILE_H__
