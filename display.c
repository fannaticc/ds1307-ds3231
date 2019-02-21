/* 
 * File:   display.c
 * Author: Raphael
 *
 * Created on 9 de Julho de 2017, 00:27
 */

#include "display.h"
#include "config.h"
#include "hardware.h"

unsigned char mask(unsigned char num)
{
    unsigned char value = 0;
    switch(num)
    {
        case '0': value = 0x3F;
            break;
        case '1': value = 0x06;
            break;
        case '2': value = 0x5B;
            break;
        case '3': value = 0x4F;
            break;
        case '4': value = 0x66;
            break;
        case '5': value = 0x6D;
            break;
        case '6': value = 0x7D;
            break;
        case '7': value = 0x07;
            break;
        case '8': value = 0x7F;
            break;
        case '9': value = 0x6F;
            break;
    }
    return value;
}

void AcenderAlgarismo(unsigned char num)
{
    PORTA = 0b00000000;
    switch(num)
    {
        case 0: PORTAbits.RA0 = 1;
            break;

        case 1: PORTAbits.RA1 = 1;
            break;

        case 2: PORTAbits.RA2 = 1;
            break;

        case 3: PORTAbits.RA3 = 1;
            break;

        default: PORTA = 0b00000000;
            break;
    }
}

void bcd()
{
    digit = number / 1000u; // extract thousands digit
    port_array[3] = mask(digit); // and store it to PORTD array
    digit = (number / 100u) % 10u; // extract hundreds digit
    port_array[2] = mask(digit); // and store it to PORTD array
    digit = (number / 10u) % 10u; // extract tens digit
    port_array[1] = mask(digit); // and store it to PORTD array
    digit = number % 10u; // extract ones digit
    port_array[0] = mask(digit); // and store it to PORTD array
}