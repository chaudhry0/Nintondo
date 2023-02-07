/*******************************************************************************
* Title                 :   COIN FLIP
* Filename              :   coinFlip.h
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file pong.c
 *
 * @brief This module runs the coinFlip game.
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "coinFlip.h"
#include "Code/Images/coinFlipImages.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/


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
 * @brief This Function is to draw the head animation of the coin.
 *
 *
 * @param[in] --> none
 *
 *
 * @return none --> void
 */
int runAnimation(Graphics_Image* arrayPtr){
    int i;
    for(i=0; i<16; i++){
        Graphics_drawImage(&g_sContext, arrayPtr + i % 8, COIN_X, COIN_Y);
        wait(ANIMATION_TIME);
    }
    int toss = random(0,1);
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
    showTutorialSmall(imageTutorialCoin);
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


