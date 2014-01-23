/*
 * File:   blinker.c
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 5
 */
#include <p24hxxxx.h>
#include "../include/blinker_functions.h"

short INT_Counter =  0;         //counter for timer interrupt
_Row_State CUR_ROW = BLANK;
_Blinker_State BLINKER = OFF;
UINT HazFlag = 0;               //flag to note hazards are on

void RightTurn(void)
{
    if(CUR_ROW == ROW1)
    {
        LATBbits.LATB1 = 1;
        CUR_ROW = ROW2;
    }
    else if(CUR_ROW == ROW2)
    {
        LATBbits.LATB2 = 1;
        CUR_ROW = ROW3;
    }
    else if(CUR_ROW == ROW3)
    {
        LATBbits.LATB3 = 1;
        CUR_ROW = BLANK;
    }
    else
    {
        LATBbits.LATB1 = 0;
        LATBbits.LATB2 = 0;
        LATBbits.LATB3 = 0;
        CUR_ROW = ROW1;
    }

    return;
}

void LeftTurn(void)
{
    if(CUR_ROW == ROW1)
    {
        LATAbits.LATA0 = 1;
        CUR_ROW = ROW2;
    }
    else if(CUR_ROW == ROW2)
    {
        LATAbits.LATA1 = 1;
        CUR_ROW = ROW3;
    }
    else if(CUR_ROW == ROW3)
    {
        LATBbits.LATB0 = 1;
        CUR_ROW = BLANK;
    }
    else
    {
        LATAbits.LATA0 = 0;
        LATAbits.LATA1 = 0;
        LATBbits.LATB0 = 0;
        CUR_ROW = ROW1;
    }

    return;
}

void Hazards(void)
{
    if(CUR_ROW == ROW1)
    {
        LATAbits.LATA0 = 1;
        LATBbits.LATB1 = 1;
        CUR_ROW = ROW2;
    }
    else if(CUR_ROW == ROW2)
    {
        LATAbits.LATA1 = 1;
        LATBbits.LATB2 = 1;
        CUR_ROW = ROW3;
    }
    else if(CUR_ROW == ROW3)
    {
        LATBbits.LATB0 = 1;
        LATBbits.LATB3 = 1;
        CUR_ROW = BLANK;
    }
    else
    {
        LATAbits.LATA0 = 0;
        LATAbits.LATA1 = 0;
        LATBbits.LATB0 = 0;

        LATBbits.LATB1 = 0;
        LATBbits.LATB2 = 0;
        LATBbits.LATB3 = 0;
        
        CUR_ROW = ROW1;
    }

    return;
}

void KillStragglers(void)
{
    LATA = 0;
    LATB = 0;

    return;
}

void __attribute__((interrupt,auto_psv)) _ISR _T1Interrupt( void)
{
        if (INT_Counter < 5)
        {
            INT_Counter++;
            _T1IF = 0;

            return;
        }
        else
        {
           INT_Counter = 0;
           if (HazFlag == 0)
           {
                if(BLINKER == LEFT)
                {
                    LeftTurn();
                }
                if(BLINKER == RIGHT)
                {
                    RightTurn();
                }
           }
           else
           {
               Hazards();
           }
           _T1IF = 0;

           return;
        }      
}

void __attribute__((interrupt,auto_psv)) _ISR _CNInterrupt( void)
{
    if((PORTBbits.RB9 == 1) && (PORTBbits.RB10 == 1))
    {
        _CNIF = 0;
        BLINKER = OFF;
        KillStragglers();
        CUR_ROW = BLANK;
        return;
    }
    else if(PORTBbits.RB9 == 0)
    {
        T1CONbits.TON = 1;
        BLINKER = LEFT;
    }
    else
    {
        T1CONbits.TON = 1;
        BLINKER = RIGHT;
    }
    _CNIF = 0;

    return;
}

void __attribute__((interrupt,auto_psv)) _ISR _INT1Interrupt( void)
{
    _INT1EP = !_INT1EP;
    
    if(PORTBbits.RB11 == 0)
    {
        CUR_ROW = BLANK;
        T1CONbits.TON = 1;
        HazFlag = 1;
    }
    else if(PORTBbits.RB11 == 1)
    {
        HazFlag = 0;
        KillStragglers();
    }

    _INT1IF = 0;

    return;
}