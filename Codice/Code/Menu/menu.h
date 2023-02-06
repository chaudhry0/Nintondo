/*******************************************************************************
* Title                 :   MENU
* Filename              :   menu.h
* Last Revision Date    :   06/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file menu.h
 *
 * @brief This is the header file for the menu.
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
#ifndef CODE_GAMES_MENU_H_
#define CODE_GAMES_MENU_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Code/Utilities/init.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define NUM_ELEMENTS 4
#define MENU_SPEED 150

/******************************************************************************
* Global Variables
*******************************************************************************/
int selectedGame; // index of the current selected game
int menuNumber; // 0: first menu; 1: second menu

/******************************************************************************
* Function Prototypes
*******************************************************************************/
// [FUNCTIONS]
// init functions
    void initElements(Graphics_Image* elementsPtr);
// moving/updating functions
    void updateArrow();
// bool functions
// draw functions
    void drawElement(Graphics_Image* imagePtr, int y);
    void drawArrow();
    void drawMenu(Graphics_Image* elementsPtr);
    void cleanArrow();
// run functions
    void runMenu();



#endif /* CODE_GAMES_MENU_H_ */

/*** End of File **************************************************************/

