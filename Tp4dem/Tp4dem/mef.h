/*
 * mef.h
 *
 * Created: 11/7/2024 17:25:22
 *  Author: Alexis
 */ 
#include "stdio.h"

volatile uint8_t flagRED;
volatile uint8_t flagGREEN;
volatile uint8_t flagBLUE;

#ifndef MEF_H_
#define MEF_H_


typedef enum{RED,GREEN,BLUE} estados;

void mef_init();
void mef_update();

#endif /* MEF_H_ */