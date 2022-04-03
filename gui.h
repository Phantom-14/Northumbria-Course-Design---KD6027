//===============================
//Author: Yutong Zhu
//Data: 10/1/2022
//Descibtion: GPIO driver source file
//Student Number: 18047451
//E-mail: w18047451@northumbria.ac.uk
//===============================
#ifndef _GUI_H
#define _GUI_H
#include "uart.h"
#include <stdio.h>

//===========================================
//Function name: GUI_init()
//Describtion: To output the user interface in the terminal, it must be initialized before the UART module.
//===========================================
void GUI_init(void);

//===========================================
//Function name: GUI_update()
//Describtion: To output the user interface in the terminal, it must be initialized before the UART module.
//===========================================
void GUI_update(short X,short Y, short Z,char Xout_g_S,short Xout_g_int,short Xout_g_dec1,short Xout_g_dec2,\
								char Yout_g_S,short Yout_g_int,short Yout_g_dec1,short Yout_g_dec2,\
								char Zout_g_S,short Zout_g_int,short Zout_g_dec1,short Zout_g_dec2);

#endif
