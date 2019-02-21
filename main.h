/* 
 * File:   main.h
 * Author: Raphael
 *
 * Created on 9 de Julho de 2017, 00:26
 */

#ifndef MAIN_H
#define	MAIN_H

#define ADC_VREF 5
#define DESIRED_VOUT 134.0
#define DIVIDER_RATIO 40.0
#define DESIRED_ADC_IN_V (DESIRED_VOUT / DIVIDER_RATIO)
#define MAX_PWM_LEVEL 300
#define MIN_PWM_LEVEL 1
#define OFFSET 10
#define ADC_RESOLUTION10 1023
#define ADC_RESOLUTION12 2047

unsigned int adc_result = 0;
unsigned int pwm_value = 8;
const unsigned int DESIRED_ADC_RESULT = (ADC_RESOLUTION10 * (DESIRED_ADC_IN_V / ADC_VREF));

void interrupt isr_timer_display();
void interrupt isr_step_up();
void bcd();

void System_Init();

#endif	/* MAIN_H */

