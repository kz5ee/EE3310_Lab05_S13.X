/*
 * File:   pin_setup.c
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 5
 */
#include <pps.h>
#include"../include/chip_setup.h"

inline void Pin_Setup(void)
{
    /*Set RB9...11 as inputs*/
    TRISBbits.TRISB9 = 1;
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB11 = 1;

    /*Set RB11 as external interrupt INT1*/
    PPSInput(PPS_INT1, PPS_RP11);

    /*Enable weak pull-ups on RB9,10, & 11*/
    CNPU1bits.CN15PUE = 1;
    CNPU2bits.CN16PUE = 1;
    CNPU2bits.CN21PUE = 1;
    
    /*Enable CN interrupts on RB9&10*/
    CNEN2bits.CN16IE = 1;
    CNEN2bits.CN21IE = 1;

    /*Set RA0-1 & RB0-3 as Digital I/O*/
    AD1PCFGL = 0xffff;//0x0e3f;

    /*Set RA0-1 & RB0-3 as outputs*/
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;

    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;

    return;
}

inline void Interrupt_Setup(void)
{
    _CNIE = 1;      //Enable Change Notification Interrupt
    _INT1IE = 1;    //Enable External Interrupt INT1

    _CNIP = 2;      //Set CN interrupt priority to 2
    _INT1IP = 4;    //Set INT1 interrupt priority to 4

    _CNIF = 0;      //Clear CN interrupt flag
    _INT1IF = 0;    //Clear INT1 interrupt flag
    
    _INT1EP = 1;    //Set INT1 interrupt on positive edge

    return;
}