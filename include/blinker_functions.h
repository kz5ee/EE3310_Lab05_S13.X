/* 
 * File:   blinker_functions.h
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 5
 */

#ifndef BLINKER_FUNCTIONS_H
#define	BLINKER_FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <Generic.h>

    typedef enum{
        BLANK,
        ROW1,
        ROW2,
        ROW3
}_Row_State;
extern _Row_State CUR_ROW;

typedef enum {
    OFF,
            LEFT,
            RIGHT,
            HAZARD
}_Blinker_State;
extern _Blinker_State BLINKER;

    void LeftTurn(void);
    void RightTurn(void);
    void Hazards(void);


#ifdef	__cplusplus
}
#endif

#endif	/* BLINKER_FUNCTIONS_H */

