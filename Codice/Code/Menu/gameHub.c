/*******************************************************************************
* Title                 :   GAME HUB
* Filename              :   gameHub.c
* Last Revision Date    :   06/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file gameHub.c
 *
 * @brief This module contains the game hub.
 *        It contains the runGameHub function that is the main function of the Ninotondo. (only function called in main.c)
 *        It has all the logic to run the games contained in the menu.
 *        It also draws the logo and the game over screen.
 *        When the game is selected it cleans the display and calls the run function of the game.  
 * 
 * @par       
* COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "Code/Menu/gameHub.h"
#include "Code/Images/backgroundImages.h"

/******************************************************************************
* [ FUNCTIONS DEFINITIONS ]
*******************************************************************************/

/*!
 * @brief This Function is to draw the logo.
 *        It is initial screen of the game.
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawLogo(){
    drawRect(0, MAX_WIDTH - 1, 0, BAR_SIZE + MAX_HEIGHT + BAR_SIZE - 1, WHITE);
    Graphics_drawImage(&g_sContext, &imageLogo, CELL_LARGE, BAR_SIZE + 36);
    wait(LONG_TIME);
    cleanDisplayGame();
    Graphics_drawImage(&g_sContext, &imageBackground, 0, 0);
}

/*!
 * @brief This Function is to draw the game over screen.
 *        It is called when the game is over.
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawGameOver(){
    startLEDBlinking();
    Graphics_drawImage(&g_sContext, &imageGameOver, CELL_LARGE, BAR_SIZE + 32);
    wait(LONG_TIME - 250);
    stopLEDBlinking();
}

/*!
 * @brief This Function is to clean the bottom bar.
 *        It is called after the user has selected a game or when the game is over.
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void cleanDisplayGame(){
    drawRect(0, MAX_WIDTH - 1, CELL_LARGE, MAX_HEIGHT + CELL_LARGE - 1, WHITE);
}

/*!
 * @brief This Function is to run the game hub.
 *        It is the main function of the game. (only this function is called in the main.c)
 *        It calls the menu and then the game selected by the user.
 *        It also updates the best score and draws the game over screen.
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void runGameHub(){
    consumeButtonA();   // resets bottom A before the games appear
    runMenu();
    cleanDisplayGame();
    initGameData();
    if (menuNumber == 0){
        switch(selectedGame){
            case 0:
                runSnake();
                break;
            case 1:
                runPong();
                break;
            case 2:
                runRhino();
                break;
            case 3:
                runFloppyDisk();
                break;
            default:
                break;
        }
    } else{ // menuNumber = 1
        switch(selectedGame){
            case 0:
                runSpaceGame();
                break;
            case 1:
                //runSuperDario();
                break;
            case 2:
                runBestScores();
                break;
            case 3:
                runAbout();
                break;
            default:
                break;
        }
    }
    if (menuNumber==0 || selectedGame<2){
        updateBestScore(selectedGame + menuNumber * NUM_ELEMENTS);
        drawGameOver();
        cleanBottomBar();
    }
    cleanDisplayGame();
}

/*** End of File **************************************************************/
