#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PCout(13)	// PA8
#define LED1 PCout(14)	// PD2	

#define READ_HW_1 PBin(4)
#define READ_HW_2 PBin(3)
#define READ_HW_3 PDin(2)	
#define READ_HW_4 PCin(10)
#define READ_HW_5 PAin(15)	
	
void LED_Init(void);//≥ı ºªØ
void HW_Init(void);

		 				    
#endif
