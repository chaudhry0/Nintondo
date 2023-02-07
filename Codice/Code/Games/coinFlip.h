/*******************************************************************************
* Title                 :   COIN FLIP
* Filename              :   coinFlip.h
* Last Revision Date    :   07/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file coinFlip.h
 *
 * @brief This is the header file for the coinFlip game
 *        It contains all the useful functions and variables for the game
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/

#ifndef CODE_UTILITIES_COINFLIP_H_
#define CODE_UTILITIES_COINFLIP_H_

/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "Code/Utilities/init.h"

/******************************************************************************
* [ MACROS ]
*******************************************************************************/
#define COIN_X  44
#define COIN_Y  44
#define ANIMATION_TIME  50

/******************************************************************************
* [ FUNCTIONS PROTOTYPES ]
*******************************************************************************/
// init/draw/logic functions 
void initArray(Graphics_Image* arrayPtr); // initializes the array of coin images
void drawCoinBackground();
// run function
void runCoinFlip(); // runs the coinFlip game

#endif /* CODE_UTILITIES_COINFLIP_H_ */

/*** End of File **************************************************************/
