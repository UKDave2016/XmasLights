/*
 * File:   main.c
 * Author: Dave
 *
 * Created on 15 May 2016, 16:14
 * 
 * PIC16F676 flashing some leds, also a button to change modes.
 */

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


#include "main.h"

void main(void)
{
    TRISC = 0 ; // C PORTS outputs
    ANSEL = 0 ; // ANALOG interfaces off
    TRISA |= 0x02 ; // RA2 = input
    OSCCAL = 0x3448; // lie about the oscillator calibration
    
    int delay = 750 ;
    int direction = -10 ;
    int mode = 2 ;
    
    while(1)
    {
        if (RA2)
        {
            __delay_ms(15) ;
            if (RA2)
            {
                mode++ ;
                if (mode == 3)
                    mode = 0 ;
                
                while(RA2)
                    ;
            }
        }
        
        if (mode == 0)
        { // flashing
        delay += direction ;
        if (delay < 50 || delay > 950)
            direction = 0 - direction ;
        cdelay(delay) ;
        PORTC = 0x03 ;
        cdelay(delay) ;
        PORTC = 0x0c ;
        cdelay(delay) ;
        PORTC = 0x05 ;
        cdelay(delay) ;
        PORTC = 0x0a ;
        }
        else if (mode == 1)
        { // steady 
            PORTC = 0x0f ;
        }
        else if (mode == 2)
        { // dimmer
            PORTC = 0x0f ;
            __delay_ms(5);
            PORTC = 0 ;
            __delay_ms(10);
        }
    }
}
void cdelay(int count)
{
    while(count--)
        __delay_ms(1) ;
}
