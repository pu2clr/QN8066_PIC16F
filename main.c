/*
 * Controller for the QN8066 device (FM transmitter). 
 * Microcontroller: PIC16F876A. XC8 Compiler (MPLAB).
 *
 * Author: Ricardo Lima Caratti
 * Created on August, 2024
 * Copyright - This code can be freely obtained and distributed under 
 * the MIT license (https://github.com/pu2clr/QN8066_PIC16F/blob/main/LICENSE).
 */


#include <xc.h>
#include "QN8066.h"


#include <xc.h>

// Check the _XTAL_FREQ value defined in QN8066.h and change it for your desired value
// #define _XTAL_FREQ 4000000  // defines the oscillator (defined in QN8066.h)

// PIC16F876A Configuration Bit Settings 
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void main(void) {
    
    i2c_begin();
    
    qn8066_begin();
    __delay_ms(100);
    qn8066_set_tx(1069);
    
    while (1) {
        __delay_ms(5);
    }
    
    return;
}
