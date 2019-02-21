/*
 * File:   main.c
 * Author: Raphael Pereira
 */
#include <xc.h>
#include <pic18f4520.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "my_delays.h"
#include "hd44780.h"
#include "my_i2c.h"
#include "ds3231.h"
#include "display.h"
#include "hardware.h"
#include "main.h"
#include "isr.h"

void main(void)
{
    float temp;
    unsigned char time[10];
    unsigned char tempera[10];
    unsigned char hour_mode;
    unsigned char old_seg;
    static bit flag_button = 1;
    static bit flag_button2 = 1;
    static bit flag_button3 = 1;
    
    System_Init();
    
    // Disarm alarms and clear alarms for this example, because alarms is battery backed.
    // Under normal conditions, the settings should be reset after power and restart microcontroller.
    clock.armAlarm1(false);
    clock.armAlarm2(false);
    clock.clearAlarm1();
    clock.clearAlarm2();
    
    while(1)
    {        
        if(BUTTON2 == 0)
        {
            if (flag_button2)
            {
                flag_button2 = 0;
                DS3231_AddData(MINUTES);
                Delay_ms(10);
            }
        }
        else
        {
            flag_button2 = 1;
        }
        
        if(BUTTON1 == 0)
        {
            if (flag_button)
            {
                flag_button = 0;
                DS3231_AddData(HOURS);
                Delay_ms(10);
            }
        }
        else
        {
            flag_button = 1;
        }
        
        if(BUTTON3 == 0)
        {
            if (flag_button3)
            {
                flag_button3 = 0;
                DS3231_HourMode();//DS3231_Set_24h_or_12h_Mode(!_12h24hmode_status);
                Delay_ms(10);
            }
        }
        else
        {
            flag_button3 = 1;
        }
        
        hour_mode = DS3231_GetTime(time);
        
        port_array[0] = mask(time[4]);
        port_array[1] = mask(time[3]);
        port_array[2] = mask(time[1]);
        port_array[3] = mask(time[0]);
    }
}

void System_Init()
{
    OSCCON = 0b01110010;

    ADCON1 = 0b00001111; // Set all pins in digital mode.
    CMCON = 0b00000111; // Disable all comparators.

    TRISA = 0b00000000;                     // Configure PORTA as output
    TRISB = 0b11111111;
    TRISC = 0b00000000;
    TRISD = 0b00000000;                     // Configure PORTD as output
    TRISE = 0b00000111;
    
    CMCON = 0b00000111;
    
    I2C_Close(); // Close the  I2C Bus.
    
    //I2C_Init(49); // I2C 100kHz, 20MHz-CRYSTAL.
    I2C_Init(19); // I2C 100kHz, 8MHz-CRYSTAL.
    //I2C_Init(9); // I2C 100kHz, 4MHz-CRYSTAL.
    
    DS3231_Init();

    // Timer 1 running 200Hz for the display LED refresh.
    T1CON = 0x01;
    PIR1bits.TMR1IF = 0;
    TMR1H = 0xD8;
    TMR1L = 0xF0;
    PIE1bits.TMR1IE = 1;
    
    INTCON = 0xC0; // Enable global interrupt.
}