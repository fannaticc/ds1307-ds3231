/* 
 * File:   isr.c
 * Author: Raphael
 *
 * Created on 5 de Novembro de 2017, 18:13
 */

#include "isr.h"
#include "config.h"
#include "main.h"
#include "adc.h"
#include "display.h"
#include "my_delays.h"

void interrupt isr_timer_display()
{
    if(PIR1bits.TMR1IF)
    {
        //PORTD = 0b00000000;
        
        INTCONbits.GIE = 0;
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xD8;
        TMR1L = 0xF0;
        
        AcenderAlgarismo(display_index);
        //PORTD ^= ((PORTD ^ port_array[display_index]) & 0x7F); // bring appropriate value to PORTD
        PORTD = port_array[display_index];

        if(display_index >= 3)
            display_index = 0;
        else
            display_index ++;
        
        INTCONbits.GIE = 1;
    }
}

