/*******************************************************************************
* Title                 :   ABOUT
* Filename              :   about.c
* Last Revision Date    :   01/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file about.c
 *
 * @brief This module shows the about screen.
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "Code/Games/about.h"
#include "Code/Images/abaoutImages.h"

/******************************************************************************
* [ FUNCTIONS DEFINITIONS ]
*******************************************************************************/

/*!
 * @brief This Function is to draw the first image of the about screen
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawAbout1(){
    Graphics_drawImage(&g_sContext, &imageAbout1, 0, BAR_SIZE);
}

/*!
 * @brief This Function is to draw the second image of the about screen
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawAbout2(){
    Graphics_drawImage(&g_sContext, &imageAbout2, 0, BAR_SIZE);
}

/*!
 * @brief This Function is to run the about screen.
 *        It draws the first image and then waits for the user to press A.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void runAbout(){
    int numAbout = 0;
    drawAbout1();
    wait(500);
    while(!gameOver){
        if (consumeButtonA()){
            if (numAbout == 0){
                drawAbout2();
                numAbout++;
                wait(500);
            } else if (numAbout == 1){
                gameOver = true;
            }
        }
    }
}


/*** end of file ***/
