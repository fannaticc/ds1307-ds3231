/* 
 * File:   hardware.h
 * Author: Raphael
 *
 * Created on 5 de Julho de 2017, 23:29
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

//==============================================================================
//Control Buttons.
//==============================================================================
#define BUTTON1 PORTEbits.RE0  //Add horas.
#define BUTTON2 PORTEbits.RE1  //Add minutos.
#define BUTTON3 PORTEbits.RE2  //Add minutos.
//==============================================================================

//==============================================================================
//Display Decimal Decoder & Decimal point pin.
//==============================================================================
#define DEC_A PORTAbits.RA2  //INPUT A FOR DECODER
#define DEC_B PORTCbits.RC1  //INPUT B FOR DECODER
#define DEC_C PORTCbits.RC2  //INPUT C FOR DECODER
#define DEC_D PORTCbits.RC0  //INPUT D FOR DECODER

#define DP PORTBbits.RB7  //DECIMAL POINT PIN
//==============================================================================


//==============================================================================
//Display Display.
//==============================================================================
#define DISP_1 PORTCbits.RC7  //OUTPUT FOR DIGIT 1 ANODE ENABLE.
#define DISP_2 PORTCbits.RC6  //OUTPUT FOR DIGIT 2 ANODE ENABLE.
#define DISP_3 PORTAbits.RA4  //OUTPUT FOR DIGIT 3 ANODE ENABLE.
#define DISP_4 PORTAbits.RA5  //OUTPUT FOR DIGIT 4 ANODE ENABLE.
//#define DISP_5 PORTbits.R  //OUTPUT FOR DIGIT 5 ANODE ENABLE.
//#define DISP_6 PORTbits.R  //OUTPUT FOR DIGIT 6 ANODE ENABLE.
//==============================================================================


//==============================================================================
//Alarm output.
//==============================================================================
#define ALM_OUT PORTCbits.RC3  //ALARM OUTPUT.
//==============================================================================

//==============================================================================
//PWM Output.
//==============================================================================
#define PWM_OUT PORTCbits.RC5  //PWM OUTPUT PIN.
//==============================================================================


//==============================================================================
//Analog inputs.
//==============================================================================
#define OUT_VOLTAGE AN0  //Output high voltage measurment.
#define OUT_CURRENT AN1  //Output currente measurment.
//==============================================================================


//==============================================================================
//I2C Pins.
//==============================================================================
//#define I2C1_SCL	TRISBbits.TRISB6
//#define I2C1_SDA	TRISBbits.TRISB4
//==============================================================================

#endif	/* HARDWARE_H */

