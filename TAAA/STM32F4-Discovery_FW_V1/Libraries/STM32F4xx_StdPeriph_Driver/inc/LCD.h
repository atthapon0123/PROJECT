#ifndef __LCD_H__
#define __LCD_H__

typedef struct 
	{ char lcd1;
		int lcd2;
		int lcd3;
		int lcd4;
		void (*init)();
		void (*update)();
  }LCD; 
typedef LCD *LCD_handle ;

/* Default Initializer for ADC */	
#define LCD_DEFAULTS { 0, \
											 0, \
											 0, \
											 0, \
									 		(void (*)(unsigned int))LCD_init, \
									 		(void (*)(unsigned int))LCD_update}

/* Prototypes fo the functions in LCD.h */
void LCD_init(LCD_handle);
void LCD_update(LCD_handle);
	  
#endif // __LCD_H__
