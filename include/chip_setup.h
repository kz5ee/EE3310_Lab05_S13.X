/* 
 * File:   chip_setup.h
 * Author: Mike Peters
 * 1000750876
 *
 * Created on March 14, 2013, 5:28 AM
 */

#ifndef CHIP_SETUP_H
#define	CHIP_SETUP_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <p24Hxxxx.h>


    void Timer1_Setup(void);
    void Pin_Setup(void);
    void Interrupt_Setup(void);


#ifdef	__cplusplus
}
#endif

#endif	/* CHIP_SETUP_H */

