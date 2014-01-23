/*
 * File:   timer_setup.c
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 5
 */

#include <timer.h>
#include "../include/chip_setup.h"

void Timer1_Setup(void)
{
    OpenTimer1(
            T1_OFF &
            T1_IDLE_CON &       
            T1_GATE_OFF &
            T1_PS_1_64 &
            T1_SYNC_EXT_OFF &
            T1_SOURCE_INT,
            0xF424);

    ConfigIntTimer1(
            T1_INT_PRIOR_2 &
            T1_INT_ON
            );

    return;
}
