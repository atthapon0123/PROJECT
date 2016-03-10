#ifndef __SPI_H__
#define __SPI_H__

typedef struct 
	{ int  dataout1;
		int  dataout2;
		int  dataout3;
		int  dataout4;
		int  dataout5;
		int  dataout6;
		int  dataout7;
		int  dataout8;
		void (*init)();
		void (*update)();
  }SPIout;
typedef SPIout *SPI_handle ;

/* Default Initializer for SPI */	
#define SPI_DEFAULTS { 0, \
											 0, \
											 0, \
											 0, \
											 0, \
											 0, \
											 0, \
											 0, \
									 		(void (*)(unsigned int))SPI_init, \
									 		(void (*)(unsigned int))SPI_update}

/* Prototypes fo the functions in SPI.h */
void SPI_init(SPI_handle);
void SPI_update(SPI_handle);
											
#endif // __SPI_H__
