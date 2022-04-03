//===============================
//Author: Yutong Zhu
//Data: 10/1/2022
//Descibtion: GPIO driver source file
//Student Number: 18047451
//E-mail: w18047451@northumbria.ac.uk
//===============================
#ifndef _PWMLED_H
#define _PWMLED_H

#include "MKL25Z4.h"

//===========================================
//Function name: pwmled_init
//Describtion: initialize PTM module and light the RGB light on board
//Parameters: None
//Function return: None
//===========================================
void pwmled_init(void);

//===========================================
//Function name: pwmled_set
//Describtion: 
//Parameters:		duty_cycle: 0~100 (percentage)
//							colour:			r/R g/G b/B
//Function return: None
//===========================================
void pwmled_set(short duty_cycle,uint8_t colour);

//===========================================
//Function name: pwmled_update
//Describtion: 
//Parameters:		X:Dutycycle of Red LED
//							Y:Dutycycle of Green LED
//							Z:Dutycycle of Blue LED
//Function return: None
//===========================================
void pwmled_update(short X, short Y, short Z);

#endif
