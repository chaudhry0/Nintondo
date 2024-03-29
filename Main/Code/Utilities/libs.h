/*******************************************************************************
* Title                 :   LIBS
* Filename              :   libs.h
* Last Revision Date    :   07/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file libs.h
 *
 * @brief This is the header file that includes all the libraries.
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
#ifndef _LIBS_H_
#define _LIBS_H_

/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
// [ TI LIBS]
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
// [ DRIVER LIBS ]
#include "Drivers/LcdDriver/Crystalfontz128x128_ST7735.h"
#include "Drivers/LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include "Drivers/LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include "Drivers/HAL_I2C.h" //I2C communication
#include "Drivers/HAL_OPT3001.h" //light sensor
#include "msp.h"
// [ C LIBS ]
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // std lib
#include <stdbool.h> // std lib for boolean values
#include <string.h> // lib to use string
#include <time.h> // lib ...


#endif /* _LIBS_H_ */

/*** End of File **************************************************************/
