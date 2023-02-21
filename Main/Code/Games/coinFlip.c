/*******************************************************************************
* Title                 :   COIN FLIP
* Filename              :   coinFlip.c
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file pong.c
 *
 * @brief This module runs the coinFlip game.
 *        It is randomly generated and the user has to guess the result.
 *        To flip the coin, the user has to move the joystick up.
 *        There is an aniimation that shows the coin flipping.
 *        The user has 5 seconds to guess the result.
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "coinFlip.h"
#include "Code/Images/coinFlipImages.h"

/******************************************************************************
* [ FUNCTIONS DEFINITIONS ]
*******************************************************************************/

/*!
 * @brief This Function is to initialize the array of images for the coin animation.
 *
 *
 * @param[in] arrayPtr --> pointer to the array of images
 *
 *
 * @return none --> void
 */
void initArray(Graphics_Image* arrayPtr){
    *(arrayPtr) = imageCoinHead1;
    *(arrayPtr + 1) = imageCoinVertical;
    *(arrayPtr + 2) = imageCoinHead2;
    *(arrayPtr + 3) = imageCoinHead;
    *(arrayPtr + 4) = imageCoinTail1;
    *(arrayPtr + 5) = imageCoinVertical;
    *(arrayPtr + 6) = imageCoinTail2;
    *(arrayPtr + 7) = imageCoinTail;
}

/*!
 * @brief This Function contains logic for the coin flip game.
 *         It draws the coin animation.
 *        The drawing is based on the result of the random toss.
 *
 *
 * @param[in] --> none
 *
 *
 * @return none --> void
 */
uint8_t runAnimation(Graphics_Image* arrayPtr){
    uint8_t i;
    for(i=0; i<16; i++){
        Graphics_drawImage(&g_sContext, arrayPtr + i % 8, COIN_X, COIN_Y);
        wait(ANIMATION_TIME);
    }
    uint8_t toss = random(0,1);
    if (toss == 1){
        for(i=0; i<4; i++){
            Graphics_drawImage(&g_sContext, arrayPtr + i, COIN_X, COIN_Y);
            wait(ANIMATION_TIME);
        }
    }
    for(i=0; i<4; i++){
        Graphics_drawImage(&g_sContext, arrayPtr + i + toss * 4, COIN_X, COIN_Y);
        wait(ANIMATION_TIME + i * 50);
    }


    return toss;
}

/*!
 * @brief This Function is to clean the area where the coin was.
 *
 *
 * @param[in] --> none
 *
 *
 * @return none --> void
 */
void drawCoinBackground(){
    drawRect(0, MAX_WIDTH - 1, CELL_LARGE, MAX_HEIGHT + CELL_LARGE - 1, WHITE);
}

/*!
 * @brief This Function is the main function and it runs the coinFlip game.
 *        It draws the background, the title and the tutorial.
 *        If the joystick is moved up, the coin animation is played.
 *        If the A button is pressed, the game is over.
 *
 *
 * @param[in] none
 *
 *
 * @return none --> void
 */
void runCoinFlip(){
    showInitialTitle(imageCoinTitle);
    drawCoinBackground();
    showTutorial(imageTutorialCoin, false);
    drawCoinBackground();
    Graphics_Image coinImages[8];
    initArray(&coinImages[0]);
    Graphics_drawImage(&g_sContext, &imageCoinTail, COIN_X, COIN_Y);
    direction = 0;  //resets direction
    while(!gameOver){
        if(direction == 1){
            runAnimation(&coinImages[0]);
        }
        if (consumeButtonA()){
            gameOver = true;
        }
        direction = 0;
    }
}

/*** End of File **************************************************************/
