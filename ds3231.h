/* 
 * File:   ds3231.h
 * Author: |H|e|c|t|o|r|
 *
 */

#ifndef DS3231_H
#define	DS3231_H

#define MODE_12HOUR_AM     0x40
#define MODE_12HOUR_PM     0X60
#define SECONDS            0x00
#define MINUTES            0x01
#define HOURS              0x02
#define DAY                0x03
#define DATE               0x04
#define MONTH              0x05
#define YEAR               0x06
#define TEMP_MSB           0x11
#define TEMP_LSB           0x12
#define REG_DS3231_CONTROL 0x0E
#define REG_DS3231_STATUS  0x0F

//==============================================================================
// Function Prototypes.
//==============================================================================
unsigned char DS3231_GetTime(unsigned char *byte0);
unsigned char DS3231_GetInfo(unsigned char byte0);
unsigned char BCDToDecimal (unsigned char byte0);
unsigned char DecimalToBCD (unsigned char byte0);
int DS3232_GetTemperature(unsigned char *p);

void DS3231_Init(void);
void DS3231_AMPM(void);
void DS3231_AMtoPM(void);
void DS3231_PMtoAM(void);
void DS3231_HourMode(void);
void DS3231_HourMode_24to12(void);
void DS3231_HourMode_12to24(void);
void DS3231_AddData(unsigned char byte0);
void DS3231_DecData(unsigned char byte0);
void DS3231_GetCalendar(unsigned char *p1);
void DS3231_SetInfo(unsigned char byte0, unsigned char byte1);
void write_Ds3231_Byte(unsigned char data, unsigned char reg);

#endif	/* DS3231_H */