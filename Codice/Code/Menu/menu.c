/*******************************************************************************
* Title                 :   MENU
* Filename              :   menu.c
* Last Revision Date    :   06/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file menu.c
 *
 * @brief This module shows the menu screen.
 *        It allows the user to select a game.
 *        To move the arrow UP and DOWN, the user has to use the joystick.  
 *        To select a game, the user has to push the A button.
 *        The menu is composed by 2 pages.
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include <Code/Menu/menu.h>
#include <Code/Images/menuImages.h>

/******************************************************************************
* [ FUNCTIONS DEFINITIONS ]
*******************************************************************************/

/*!
 * @brief This Function is to draw an item(game) of the menu.
 *        It  uses a picture not a text as the title of the game     
 *
 * @param[in] imagePtr --> pointer to the image to draw
 * @param[in] y --> y coordinate of the image
 *
 * 
 * @return none --> void
 */
void drawElement(Graphics_Image* imagePtr, int y){
    Graphics_drawImage(&g_sContext, imagePtr, CELL_LARGE, y);
}

/*!
 * @brief This Function is to draw the arrow.
 *        It is used to show the user which game is selected (pointed).     
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawArrow(){
    int tmpY = BAR_SIZE + CELL_LARGE + CELL_SMALL + CELL_LARGE * selectedGame;
    Graphics_drawImage(&g_sContext, &imageArrow, MAX_WIDTH - CELL_LARGE, tmpY);
}

/*!
 * @brief This Function is to draw the menu.
 *        It draws the title of the menu and the games.     
 *
 * @param[in] elementsPtr --> pointer to the array of images to draw
 *
 * 
 * @return none --> void
 */
void drawMenu(Graphics_Image* elementsPtr){
    Graphics_drawImage(&g_sContext, &imageTextSelectGame, 23, 26);
       int i;
       for (i=0; i<NUM_ELEMENTS; i++){
           drawElement(elementsPtr + i, BAR_SIZE + CELL_LARGE + CELL_SMALL + CELL_LARGE * i);
       }
}

/*!
 * @brief This Function is to initialize the array of images to draw.
 *        It is used to draw the menu.     
 *
 * @param[in] elementsPtr --> pointer to the array of images to draw
 *
 * 
 * @return none --> void
 */
void initElements(Graphics_Image* elementsPtr){
    if (menuNumber == 0){
        *(elementsPtr) = imageTextSnake;
        *(elementsPtr + 1) = imageTextPong;
        *(elementsPtr + 2) = imageTextRhino;
        *(elementsPtr + 3) = imageTextFloppyDisk;
    }
    if (menuNumber == 1){
        *(elementsPtr) = imageTextSpaceInvaders;
        *(elementsPtr + 1) = imageTextSnake;
        *(elementsPtr + 2) = imageTextBestScores;
        *(elementsPtr + 3) = imageTextAbout;
    }
}

/*!
 * @brief This Function is to update the arrow position.
 *        It uses the lastMove variable to know if the user is pushing UP or DOWN.     
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void updateArrow(){
    if (lastMove == 1){ // pushing UP
        selectedGame--;
    }else if (lastMove == 3){ // pushing DOWN
        selectedGame++;
    }
}

/*!
 * @brief This Function is to clean the arrow.
 *        It is used to update the arrow position.     
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void cleanArrow(){
    int tmpY = BAR_SIZE + CELL_LARGE + CELL_SMALL + CELL_LARGE * selectedGame;
    drawRect(MAX_WIDTH - CELL_LARGE, MAX_WIDTH, tmpY, tmpY + CELL_LARGE - 1, WHITE);
}

/*!
 * @brief This Function is to run the menu.
 *        It is used to show the menu and to select a game.     
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void runMenu(){
    bool gameSelected = false;
    selectedGame = 0;
    menuNumber = 0;
    Graphics_Image imageElements[NUM_ELEMENTS];
    direction = 0;
    initElements(&imageElements[0]);
    drawMenu(&imageElements[0]);
    drawArrow();

    while (!gameSelected){
        __sleep(); // LPM
        if (direction){
            cleanArrow();
            updateArrow();
            if (menuNumber == 0){
                if (selectedGame == -1){
                    selectedGame = 0;
                }else if (selectedGame == NUM_ELEMENTS){
                    selectedGame = 0;
                    menuNumber = 1;
                    initElements(&imageElements[0]);
                    drawMenu(&imageElements[0]);
                }
            }
            else if (menuNumber == 1){
                if (selectedGame == NUM_ELEMENTS){
                    selectedGame = NUM_ELEMENTS - 1;
                }else if (selectedGame == -1){
                    selectedGame = NUM_ELEMENTS - 1;
                    menuNumber = 0;
                    initElements(&imageElements[0]);
                    drawMenu(&imageElements[0]);
                }
            }
            drawArrow();
            wait(MENU_SPEED);
        }
        if (consumeButtonA()){
            gameSelected = true;
        }
    }
}

/*** End of File **************************************************************/
