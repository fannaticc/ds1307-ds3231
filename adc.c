/* 
 * File:   adc.c
 * Author: Raphael
 *
 * Created on 7 de Julho de 2016, 12:00
 */
#include "adc.h"
#include "config.h"

unsigned int readAD()
{
    
    
    ADCON0bits.GO = 1; //Setting GO bit to 1 starts AD read
    //When AD read is ready, GO bit turns 0
    while(ADCON0bits.GO);

    return (((unsigned int)ADRESH) << 8) | (ADRESL);
}

unsigned int readadraw()
{
    return (((unsigned int)ADRESH) << 8) | (ADRESL);
}

/*unsigned int readAD(unsigned int selectAD)

    //Declaration of variables
    unsigned int result = 0;
    
    ADCON0 = selectAD;
    ADCON0bits.ADON = 1; // Turn on the ad Module.
    
    ADCON0bits.GO = 1; // Setting GO bit to 1 starts AD read.
    while(ADCON0bits.GO); // When AD read is ready, GO bit turns 0

    result = (((unsigned int)ADRESH)<<8)|(ADRESL); // Read 
    
    //Return the mean of reads
    return (unsigned int) (result);
}*/


