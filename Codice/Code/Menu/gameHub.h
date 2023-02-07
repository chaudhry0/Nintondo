/*******************************************************************************
* Title                 :   GAME HUB
* Filename              :   gameHub.h
* Last Revision Date    :   06/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file gameHub.h
 *
 * @brief This is the header file for the game hub.
 * 
 * @par       
* COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
#ifndef _CODE_GAMES_GAMEHUB_H_
#define _CODE_GAMES_GAMEHUB_H_

/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "menu.h"
#include "Code/Games/snake.h"
#include "Code/Games/floppyDisk.h"
#include "Code/Games/pong.h"
#include "Code/Games/rhinoRunner.h"
//#include "Code/Games/superDario.h"
#include "Code/Games/spaceGame.h"
#include "Code/Games/bestScores.h"
#include "Code/Games/about.h"

/******************************************************************************
* [ FUNCTIONS PROTOTYPES]
*******************************************************************************/
// init functions
// moving/updating functions
// bool functions
// draw functions
void drawLogo(); // draws initial text "Ninotondo"
void drawGameOver(); //draws the GameOver image (equal for all games)
void cleanDisplayGame(); // clean the display (only the central section, not the red bars)
// run functions
void runGameHub(); // runMenu function


#endif /* _CODE_GAMES_GAMEHUB_H_ */

/*** End of File **************************************************************/
