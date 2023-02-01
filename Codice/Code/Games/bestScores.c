/*******************************************************************************
* Title                 :   BEST SCORES
* Filename              :   bestScores.c
* Last Revision Date    :   01/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file bestScores.c
 *
 * @brief This module shows the best scores screen.
 *        It draws a table with the best score from every game.
 *        It also shows the total score.
 *        The screen remains until button A is clicked.
 *        The best scores are saved in the bestScores array.
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "bestScores.h"
#include "Code/Images/bestScoreImages.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/*!
 * @brief This Function is to draw the best scores table.
 *        It draws the table and the total score.
 *        The total score is the sum of the best scores.
 *        If the total score is greater than 99, it is shown as 99.
 *        The best scores are saved in the bestScores array.
 *              
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawScores(){
    int totalScore = 0;
    char value[10];
    int i;
    Graphics_setForegroundColor(&g_sContext, BLACK);
    for (i=0; i<5; i++){
        sprintf(value, "%d", bestScores[i]);
        Graphics_drawString(&g_sContext, (int8_t *) value, 3, 110, BAR_SIZE + 18 + 10*i, TRANSPARENT_TEXT);
        totalScore += bestScores[i];
    }
    if (totalScore<100){
        sprintf(value, "%d", totalScore);
    }else{
        sprintf(value, "99");
    }

    Graphics_drawString(&g_sContext, (int8_t *) value, 3, 110, 76 + BAR_SIZE, TRANSPARENT_TEXT);
}

/*!
 * @brief This Function is to run the best scores screen.
 *        It draws the best scores table and the screen remains until button A is clicked.
 *              
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void runBestScores(){
    Graphics_drawImage(&g_sContext, &imageBestScores, 0, 16);
    drawScores();
    while(!gameOver){
        if (consumeButtonA()){
            gameOver = true;
        }
    }
}


/*** end of file ***/
