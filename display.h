/* 
 * File:   display.h
 * Author: Raphael
 *
 * Created on 9 de Julho de 2017, 00:27
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

unsigned char display_index = 0;
unsigned char port_array[4] = {0,0,0,0};
unsigned char decimal_point = 0;
unsigned int digit = 0;
unsigned int number = 0;

unsigned char mask(unsigned char num);

void AcenderAlgarismo(unsigned char num);
void bcd();

#endif	/* DISPLAY_H */

