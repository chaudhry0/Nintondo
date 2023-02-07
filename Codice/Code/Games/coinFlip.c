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
//#include "Code/Images/coinFlipImages.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/
/*!
 * @brief This Function is to draw the head animation of the coin.
 *
 *
 * @param[in] --> none
 *
 *
 * @return none --> void
 */
void drawHead(){
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinHead1, COIN_X, COIN_Y);
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinHead2, COIN_X, COIN_Y);
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinHead3, COIN_X, COIN_Y);
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinHead4, COIN_X, COIN_Y);
}

/*!
 * @brief This Function is to draw the tail animation of the coin.
 *
 *
 * @param[in] --> none
 *
 *
 * @return none --> void
 */
void drawTail(){
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinTail1, COIN_X, COIN_Y);
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinTail2, COIN_X, COIN_Y);
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinTail3, COIN_X, COIN_Y);
    wait(ANIMATION_TIME);
    Graphics_drawImage(&g_sContext, &imageCoinTail4, COIN_X, COIN_Y);
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
    Graphics_drawImage(&g_sContext, &imageCoinTail4, COIN_X, COIN_Y);
    int toss;
    bool nome;
    while(!gameOver){
        if(direction == 1){ //moving joystick UP
            toss = random(3,4)
        }
        for(toss){
            if (nome){
                draw head
                nome !=nome
            }else{
                draw tail
                nome !=nome
            }
        }
        toss = 0;

        if (bottone a){
            gameOver = true;
        }
    }
}


