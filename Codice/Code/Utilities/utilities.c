/*******************************************************************************
* Title                 :   UTILITIES
* Filename              :   utilities.c
* Last Revision Date    :   07/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file   utilities.c
 *
 * @brief This module contains the utilities functions.
 *        It contains all the common functions used in the games.
 *        It also contains some Global Variables.
 *        Last but not least, it contains some HANDlERS.
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "utilities.h"

/******************************************************************************
* [ FUNCTIONS DEFINITIONS ]
*******************************************************************************/ 

/*!
 * @brief This Function is to initialize the best scores array.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void initBestScores(){
    int i;
    for (i=0; i<NUM_GAMES; i++){
        bestScores[i] = 0;
    }
}

/*!
 * @brief This Function is to update the best score.
 *                
 *
 * @param[in] selectedGame --> the game selected
 *
 * 
 * @return none --> void
 */
void updateBestScore(int selectedGame){
    if (score > bestScores[selectedGame]){
        bestScores[selectedGame] = score;
    }
}

/*!
 * @brief This Function is to get time in milliseconds. 
 *        Returns Timer_A counter value.
 *                
 *
 * @param[in] none
 *
 * 
 * @return uint32_t --> the time in milliseconds
 */
uint32_t getTimeMils(){
    return Timer_A_getCounterValue(TIMER_A2_BASE);
}

/*!
 * @brief This Function is to wait for a certain amount of time.
 *                
 *
 * @param[in] interval --> the time to wait
 *
 * 
 * @return none --> void
 */
void wait(uint32_t interval){
    interval = interval / 2;
    if (interval <= 60000){
        uint32_t start = getTimeMils();
        if (start + interval >= 65535){
            uint32_t waited = 65535 - start;
            while (getTimeMils() != 0);
            while(interval - waited > getTimeMils());
        } else{
            while(start + interval > getTimeMils());
        }
    }
}

/*!
 * @brief This Function is get a random number between min and max.
 *                
 *
 * @param[in] min --> the minimum number
 * @param[in] max --> the maximum number
 *
 * 
 * @return int --> the random number
 */
int random(int min, int max) {
    return (rand()%(max-min+1))+min;
}

/*!
 * @brief This Function is to draw the score text.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawScoreText(){
    Graphics_setForegroundColor(&g_sContext, WHITE);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) "score: ", 7, 64, 120, TRANSPARENT_TEXT);
}

/*!
 * @brief This Function is to draw the score.
 *                
 *
 * @param[in] score --> the score to draw
 *
 * 
 * @return none --> void
 */
void drawScore(int score) {
    char temp[10];
    drawRect(80, 100, 115, 125, RED);
    Graphics_setForegroundColor(&g_sContext, WHITE);
    sprintf(temp, "%d", score);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) temp, 3, 90, 120, TRANSPARENT_TEXT);
}

/*!
 * @brief This Function is to clean the bottom bar.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void cleanBottomBar(){
    drawRect(CELL_LARGE - 1, MAX_WIDTH - CELL_LARGE, MAX_HEIGHT + CELL_LARGE, MAX_HEIGHT + 2* CELL_LARGE, RED);
}

/*!
 * @brief This Function is to draw a rectangle filled with a color.
 *                
 *
 * @param[in] xMin --> the minimum x coordinate
 * @param[in] xMax --> the maximum x coordinate
 * @param[in] yMin --> the minimum y coordinate
 * @param[in] yMax --> the maximum y coordinate
 * @param[in] color --> the color of the rectangle
 *
 * 
 * @return none --> void
 */
void drawRect(int xMin, int xMax, int yMin, int yMax, uint32_t color) {
    Graphics_Rectangle rect;
    rect.xMin = xMin;
    rect.xMax = xMax;
    rect.yMin = yMin;
    rect.yMax = yMax;
    Graphics_setForegroundColor(&g_sContext, color);
    Graphics_fillRectangle(&g_sContext, &rect);
}

/*!
 * @brief This Function is to check joystick movement.
 *        if the joystick is moved, it returns the direction.
 *        the direction is 1 for up, 2 for down, 3 for left and 4 for right.        
 *
 * @param[in] none 
 *
 * 
 * @return none --> void
 */
void checkLastMove(){
    direction = 0;
    if (resultsBuffer[0] < 3000) {
            direction = lastMove = 4;
        } else if (resultsBuffer[0] > 13000) {
            direction = lastMove = 2;
        } else if (resultsBuffer[1] < 3000) {
            direction = lastMove = 3;
        } else if (resultsBuffer[1] > 13000) {
            direction = lastMove = 1;
        }
}

/*!
 * @brief This Function is to initialize the game data.
 *        It resets the score, the game over condition and the button A pressed condition.
 *                
 *
 * @param[in] none 
 *
 * 
 * @return none --> void
 */
void initGameData(){
    score = 0;
    gameOver = false;
    consumeButtonA();   // resets bottom A before the games appear
}

// Old function to get buttonA pressed condition
/*uint16_t getButtons(){
    if (!GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1)){  // A
        return 1;
    }
    if (!GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN5)){  // B
        return 2;
    }
    return 0;
}*/


/*!
 * @brief This Function is to get the button A pressed condition.
 *        It also resets the button A pressed condition.
 *                
 *
 * @param[in] none 
 *
 * 
 * @return bool --> true if button A is pressed, false otherwise
 */
bool consumeButtonA(){
    if (buttonA == 1){
        buttonA = 0;
        return true;
    }
    return false;
}


/*!
 * @brief This Function is to start the LED blinking.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void startLEDBlinking(){
    //Timer_A_setOutputForOutputModeOutBitValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TIMER_A_OUTPUTMODE_OUTBITVALUE);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

/*!
 * @brief This Function is to stop the LED blinking.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void stopLEDBlinking(){
    //Timer_A_setOutputForOutputModeOutBitValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TIMER_A_OUTPUTMODE_OUTBITVALUE_LOW);
    Timer_A_stopTimer(TIMER_A0_BASE);
}

/*!
 * @brief This Function is to draw the large tutorial image.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void showTutorialBig(Graphics_Image image){
    Graphics_drawImage(&g_sContext, &image, 0, CELL_LARGE + MAX_HEIGHT/2 - CELL_LARGE/2 - 6);
    wait(SHORT_TIME);
}

/*!
 * @brief This Function is to draw the small tutorial image.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void showTutorialSmall(Graphics_Image image){
    Graphics_drawImage(&g_sContext, &image, 0, CELL_LARGE + MAX_HEIGHT/2 - CELL_LARGE/2);
    wait(SHORT_TIME);
}

/*!
 * @brief This Function is to draw the initial title image.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void showInitialTitle(Graphics_Image image){
    Graphics_drawImage(&g_sContext, &image, 0, CELL_LARGE);
    wait(SHORT_TIME);
}

/******************************************************************************
* [ HANDLER ]
*******************************************************************************/ 
/*!
 * @brief This is the Timer A2 interrupt service routine.
 *        It clears the interrupt flag.        
 *
 * @param[in] none 
 *
 * 
 * @return none --> void
 */
void TA2_N_IRQHandler(void) {
    Timer_A_clearInterruptFlag(TIMER_A2_BASE);
}

/*!
 * @brief This is the Joystick interrupt handler.
 *        It clears the interrupt flag.
 *        It stores the ADC14 conversion results in the resultsBuffer.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void ADC14_IRQHandler(void) {
    uint64_t status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    if(status & ADC_INT1) { // ADC_MEM1 conversion completed
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0); // Store ADC14 conversion results
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
    }
    checkLastMove();

    /*int buttonPressed = 0;    //sensitive stick button
    if (!(P4IN & GPIO_PIN1))
        buttonPressed = 1;*/
}

/*!
 * @brief This is Port 5 interrupt handler.
 *                
 *
 * @param[in] none 
 *
 * 
 * @return none --> void
 */
void PORT5_IRQHandler(void){
    // Port 5 pin 1 ---> buttonA
    // Port 3 pin 5 ---> buttonB
    __disable_irq();
    if (P5->IFG & BIT1){
        buttonA = 1;
        P5->IFG &= ~BIT1;
    }
    __enable_irq();
}

/*** end of file ***/
