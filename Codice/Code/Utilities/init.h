/*******************************************************************************
* Title                 :   INIT
* Filename              :   init.h
* Last Revision Date    :   07/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file init.h
 *
 * @brief This is the header file for the initialization functions.
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
#ifndef _INIT_H_
#define _INIT_H_

/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "Code/Utilities/utilities.h"


/******************************************************************************
* [ FUNCTIONS PROTOTYPES ]
*******************************************************************************/
void _adcInit(); // initializes ADC
void _graphicsInit(); // initializes LCD
void _lightSensorInit(); // initializes light sensor
void configurePushButtons(); // configures Joystick buttons
void configureTimer_A2_BASE(); // configures Timer_A
void _hwInit(); // initializes hardware


#endif /* _INIT_H_ */

/*** End of File **************************************************************/
