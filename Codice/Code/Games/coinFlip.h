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
* Includes
*******************************************************************************/
#include "Code/Utilities/init.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define COIN_X
#define COIN_Y
#define ANIMATION_TIME  50

/******************************************************************************
* Function Prototypes
*******************************************************************************/
// draw function
void drawHead();
void drawTail();
void drawCoinBackground();
// run function
void runCoinFlip(); // runs the coinFlip game

#endif /* CODE_UTILITIES_COINFLIP_H_ */

/*** End of File **************************************************************/
