/* 
 * File:   ds3231.c
 * Author: |H|e|c|t|o|r|
 *
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "ds3231.h"
#include "my_i2c.h"
#include "main.h"
#include "display.h"


//==============================================================================
// Inicialize the DS3231
//==============================================================================
void DS3231_Init(void)
{
    DS3231_SetInfo(REG_DS3231_CONTROL, 0x00);
    DS3231_SetInfo(REG_DS3231_STATUS, 0x00);
}

//==============================================================================
//Sets Information in the RTC.
//byte0: Sets "Word Address".
//byte1: Sets the information.
//==============================================================================
void DS3231_SetInfo(unsigned char byte0, unsigned char byte1)
{
    I2C_Start();
    I2C_WriteByte(0xD0 + 0);
    I2C_WriteByte(byte0);
    I2C_WriteByte(byte1);
    I2C_Stop();
}


//==============================================================================
//Gets information of RTC.
//byte 0: Sets the "Word Address"
//byte1: Return the  information.
//==============================================================================
unsigned char DS3231_GetInfo(unsigned char byte0)
{
    unsigned char byte1 = 0;
    I2C_Start();
    I2C_WriteByte(0xD0);
    I2C_WriteByte(byte0);
    I2C_RepeatedStart();
    I2C_WriteByte(0xD1);
    byte1 = I2C_ReadByte(0);
    I2C_Stop();
    
    return (byte1);
}


//==============================================================================
//Adds data in the RTC. minutes, seconds, hours, day, date, month and year.
//byte0: Sets data to increment.
//==============================================================================
void DS3231_AddData(unsigned char byte0)
{
    unsigned char byte1 = 0;
    
    switch(byte0)
    {
        case 0x00:
        case 0x01: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   byte1++;
                   if(byte1 == 60)
                   {
                       byte1 = 0;
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
                    
        case 0x03: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   byte1++;
                   if(byte1 == 8)
                   {
                       byte1 = 1;
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
                    
        case 0x04: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   byte1++;
                   if(byte1 == 32)
                   {
                       byte1 = 1;
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
            
        case 0x05: byte1 = DS3231_GetInfo(byte0);
                   byte1 = BCDToDecimal(byte1 & 127);
                   byte1++;
                   if(byte1 == 13)
                   {
                       byte1 = 1;
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
            
        case 0x06: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   byte1++;
                   if(byte1 == 100)
                   {
                       byte1 = 0;
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
            
        case 0x02: byte1 = DS3231_GetInfo(byte0);
                   switch((byte1 & 96) >> 5)
                   {
                       case 0:
                       case 1: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                               byte1++;
                               if(byte1 == 24)
                               {
                                   byte1 = 0;
                               }
                               DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                               break;
                               
                       case 2: byte1 = BCDToDecimal(byte1 & 31);
                               byte1++;
                               if(byte1 == 13)
                               {
                                   byte1 = 1;
                               }
                               byte1 = DecimalToBCD(byte1);
                               byte1 = byte1 | 64;
                               DS3231_SetInfo(byte0, byte1);
                               break;
                               
                       case 3: byte1 = BCDToDecimal(byte1 & 31);
                               byte1++;
                               if(byte1 == 13)
                               {
                                   byte1 = 1;
                               }
                               byte1 = DecimalToBCD(byte1);
                               byte1 = byte1 | 96;
                               DS3231_SetInfo(byte0, byte1);
                               break;
                               
                       default:    
                               break;
                   }
                   break;
        default: break;
    }
}


//==============================================================================
//Decs data in the RTC. minutes, seconds, hours, day, date, month and year.
//byte0: Sets data to decrement.
//==============================================================================
void DS3231_DecData(unsigned char byte0)
{
    unsigned char byte1 = 0;
    
    switch(byte0)
    {
        case 0x00:
        case 0x01: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   if(byte1 == 0)
                   {
                       byte1 = 59;
                   }
                   else 
                   {
                       byte1--;
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
                    
        case 0x03: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   if(byte1 == 1)
                   {
                       byte1 = 7;
                   }
                   else
                   {
                       byte1--;                       
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
                    
        case 0x04: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   byte1--;
                   if(byte1 == 1)
                   {
                       byte1 = 31;
                   }
                   else
                   {
                       byte1--;                       
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
            
        case 0x05: byte1 = DS3231_GetInfo(byte0);
                   byte1 = BCDToDecimal(byte1 & 127);
                   if(byte1 == 1)
                   {
                       byte1 = 12;
                   }
                   else
                   {
                       byte1--;                       
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
            
        case 0x06: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                   if(byte1 == 0)
                   {
                       byte1 = 100;
                   }
                   else
                   {
                       byte1--;                       
                   }
                   DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                   break;
            
        case 0x02: byte1 = DS3231_GetInfo(byte0);
                   switch((byte1 & 96) >> 5)
                   {
                       case 0:
                       case 1: byte1 = BCDToDecimal(DS3231_GetInfo(byte0));
                               if (byte1 == 0)
                               {
                                   byte1 = 23;
                               } 
                               else
                               {
                                   byte1--;
                               }
                               DS3231_SetInfo(byte0, DecimalToBCD(byte1));
                               break;
                               
                       case 2: byte1 = BCDToDecimal(byte1 & 31);
                               if(byte1 == 1)
                               {
                                   byte1 = 12;
                               }
                               else
                               {
                                   byte1--;
                               }
                               byte1 = DecimalToBCD(byte1);
                               byte1 = byte1 | 64;
                               DS3231_SetInfo(byte0, byte1);
                               break;
                               
                       case 3: byte1 = BCDToDecimal(byte1 & 31);
                               if(byte1 == 1)
                               {
                                   byte1 = 12;
                               }
                               else
                               {
                                   byte1--;
                               }
                               byte1 = DecimalToBCD(byte1);
                               byte1 = byte1 | 96;
                               DS3231_SetInfo(byte0, byte1);
                               break;
                               
                       default:    
                               break;
                   }
                   break;
        default: break;
    }
}


//==============================================================================
//Makes a change from AM to PM, or PM to AM.
//==============================================================================
void DS3231_AMPM(void)
{
    unsigned char byte0;
    
    byte0 = DS3231_GetInfo(HOURS);
    
    if((byte0 & 96) == 96)
    {
        byte0 &= 95;
    }
    else if((byte0 & 64) == 64)
    {
        byte0 |= 96;
    }
    
    DS3231_SetInfo(HOURS, byte0);
}

//==============================================================================
//Makes a change from AM to PM, or PM to AM.
//==============================================================================
void DS3231_AMtoPM(void)
{
    
}

//==============================================================================
//Makes a change from AM to PM, or PM to AM.
//==============================================================================
void DS3231_PMtoAM(void)
{
    
}

//==============================================================================
//Makes a change of 12hr to 24hr, or 24hr to 12hr.
//==============================================================================
void DS3231_HourMode(void)
{
    unsigned char byte0, byte1;
    
    byte0 = DS3231_GetInfo(HOURS);
    
    switch((byte0 & 96) >> 5)
    {
        case 0:
        case 1: byte1 = BCDToDecimal(byte0);
                if(byte1 == 0)
                {
                    byte1 = 12;
                    byte1 = DecimalToBCD(byte1);
                    byte1 = byte1 | MODE_12HOUR_PM;
                    break;
                }
                else if(byte1 > 12)
                {
                    byte1 = byte1 - 12;
                    byte1 = DecimalToBCD(byte1);
                    byte1 = byte1 | MODE_12HOUR_PM;
                    break;
                }
                else if(byte1 < 13)
                {
                    byte1 = DecimalToBCD(byte1);
                    byte1 = byte1 | MODE_12HOUR_AM;
                    break;
                }
                break;
                
        case 2: byte1 = byte0 & 31;
                break;
                
        case 3: byte1 = byte0 & 31;
                byte1 = BCDToDecimal(byte1);
                byte1 = byte1 + 12;
                if(byte1 == 24)
                {
                    byte1 = 0;
                }
                byte1 = DecimalToBCD(byte1);
                break;
                
        default:
                break;
    }
    
    DS3231_SetInfo(HOURS, byte1);
}

//==============================================================================
//Makes a change of 12hr to 24hr
//==============================================================================
void DS3231_HourMode_12to24(void)
{
    unsigned char byte0, byte1;
    
    
    DS3231_SetInfo(HOURS, byte1);
}

//==============================================================================
//Makes a change of 24hr to 12hr.
//==============================================================================
void DS3231_HourMode_24to12(void)
{
    unsigned char byte0, byte1;
    
    
    DS3231_SetInfo(HOURS, byte1);
}


//==============================================================================
//Gets the full time. "Hours:Minutes:Seconds"  <<01:35:12>>
//*p: Save all time in this variable.
//Return 0 if time is in 24 format.
//Return 1 if time is in 24 format.
//Return 2 if time is in AM format.
//Return 3 if time  is in PM format.
//==============================================================================
unsigned char DS3231_GetTime(unsigned char *p)
{
    unsigned char byte0, byte1;
    unsigned char byte2[5];
    
    byte0 = DS3231_GetInfo(HOURS);
    byte1 = (byte0 & 96) >> 5;
    
    switch(byte1)
    {
        case 0:
        case 1:
                byte0 = BCDToDecimal(byte0);
                break;
                
        case 2:
        case 3: byte0 = BCDToDecimal(byte0 & 31);
                break;
                
        default:
                break;
    }
    sprintf(byte2, "%02d", byte0);
    *p++ = byte2[0];
    *p++ = byte2[1];
    *p++ = ':';
    
    // Get minutes
    byte0 = BCDToDecimal(DS3231_GetInfo(MINUTES));
    sprintf(byte2, "%02d", byte0);
    *p++ = byte2[0];
    *p++ = byte2[1];
    *p++ = ':';
    
    // Get seconds
    byte0 = BCDToDecimal(DS3231_GetInfo(SECONDS));
    sprintf(byte2, "%02d", byte0);
    *p++ = byte2[0];
    *p++ = byte2[1];
    *p++ = NULL;

    return (byte1);
}


//==============================================================================
//Gets the full calendar. "Day. Date Month. Year" <<Mon. 12 Jan. 15>>
//*p: Save all calendar in this variable.
//==============================================================================
void DS3231_GetCalendar(unsigned char *p)
{
    unsigned char byte0;
    unsigned char byte1[5];
    byte0 = BCDToDecimal(DS3231_GetInfo(DAY));
    switch(byte0)
    {
        case 1: *p++ = 'S'; *p++= 'e'; *p++= 'g'; 
                break;
                
        case 2: *p++= 'T'; *p++= 'e'; *p++= 'r'; 
                break;
                
        case 3: *p++= 'Q'; *p++= 'u'; *p++= 'a'; 
                break;
                
        case 4: *p++= 'Q'; *p++= 'u'; *p++= 'i'; 
                break;
                
        case 5: *p++= 'S'; *p++= 'e'; *p++= 'x'; 
                break;
                
        case 6: *p++= 'S'; *p++= 'a'; *p++= 'b'; 
                break;
                
        case 7: *p++= 'D'; *p++= 'o'; *p++= 'm'; 
                break;
                
        default:
                break;
    } 
    
    *p++ = '.'; *p++ = ' ';
    byte0 = BCDToDecimal(DS3231_GetInfo(DATE));
    
    sprintf(byte1, "%02d", byte0);
    *p++ = byte1[0]; *p++ = byte1[1]; *p++ = ' ';
    byte0 = BCDToDecimal(DS3231_GetInfo(MONTH));
    
    switch(byte0)
    {
        case 1: *p++ = 'J'; *p++ = 'a'; *p++ = 'n';
                break;
                
        case 2: *p++ = 'F'; *p++ = 'e'; *p++ = 'v';
                break;
                
        case 3: *p++ = 'M'; *p++ = 'a'; *p++ = 'r';
                break;
                
        case 4: *p++ = 'A'; *p++ = 'b'; *p++ = 'r'; 
                break;
                
        case 5: *p++ = 'M'; *p++ = 'a'; *p++ = 'i'; 
                break;
                
        case 6: *p++ = 'J'; *p++ = 'u'; *p++ = 'n';
                break;
                
        case 7: *p++ = 'J'; *p++ = 'u'; *p++ = 'l';
                break;
                
        case 8: *p++ = 'A'; *p++ = 'g'; *p++ = 'o';
                break;
                
        case 9: *p++ = 'S'; *p++ = 'e'; *p++ = 't';
                break;
                
        case 10: *p++ = 'O'; *p++ = 'u'; *p++ = 't';
                 break;
                
        case 11: *p++ = 'N'; *p++ = 'o'; *p++ = 'v';
                 break;
                
        case 12: *p++ = 'D'; *p++ = 'e'; *p++ = 'z';
                 break;
                
        default:
                 break;
    } 
    
    *p++ = '.'; *p++ = ' ';
    
    byte0 = BCDToDecimal(DS3231_GetInfo(YEAR));
    sprintf(byte1, "%02d", byte0);
    *p++ = byte1[0]; *p++ = byte1[1]; *p = NULL;
}


//==============================================================================
//Gets the full calendar. "Day. Date Month. Year" <<Mon. 12 Jan. 15>>
//*p: Save all calendar in this variable.
//==============================================================================
int DS3232_GetTemperature(unsigned char *p)
{
    float rv;
    unsigned char temp_msb, temp_lsb;
    signed int nint;
    
    temp_msb = DS3231_GetInfo(TEMP_MSB);
    temp_lsb = DS3231_GetInfo(TEMP_LSB) >> 6;
    
    if ((temp_msb & 0x80) != 0)
        nint = temp_msb | ~((1 << 8) - 1);      // if negative get two's complement
    else
        nint = temp_msb;

    rv = nint + 0.25 * temp_lsb;
    
    return sprintf(p, "%3.2f", rv); 
}

//==============================================================================
//Converts a variable of BCD to Decimal.
//==============================================================================
unsigned char BCDToDecimal(unsigned char byte0)
{
    return (((byte0 & 0xF0) >> 4) * 10) + (byte0 & 0x0F);
}

//==============================================================================
//Converts a variable of Decimal to BCD.
//==============================================================================
unsigned char DecimalToBCD(unsigned char byte0)
{
    return (((byte0 / 10) << 4) | (byte0 % 10));
}
