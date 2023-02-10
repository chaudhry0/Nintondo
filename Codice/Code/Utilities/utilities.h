/*******************************************************************************
* Title                 :   UTILITIES
* Filename              :   utilities.h
* Last Revision Date    :   07/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file utilities.h
 *
 * @brief This is the header file for the utilities. 
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
#ifndef _UTILITIES_H_
#define _UTILITIES_H_

/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "Code/Utilities/libs.h"
#include "Code/Utilities/colors.h"

/******************************************************************************
* [ MACROS - GOLBAL CONSTANT ]
*******************************************************************************/
#define SHORT_TIME 1500
#define LONG_TIME 3000
#define MAX_HEIGHT 96
#define MAX_WIDTH 128
#define CELL_SMALL 8
#define CELL_LARGE 16
#define BAR_SIZE 16
#define NUM_GAMES 5

/******************************************************************************
* [ GLOBAL VARIABLES ]
*******************************************************************************/
static uint16_t resultsBuffer[2]; // buffer to store Joystick samples
Graphics_Context g_sContext; // Graphic library context
uint16_t score; // game score
bool gameOver; // game status
uint8_t direction; // value read from Joystick buffer
uint8_t lastMove; // previous move performed (equals to "direction" but not reset every time)
uint8_t buttonA; // value read from Button A
uint16_t bestScores[5]; // array to store best scores

/******************************************************************************
* [ FUNCTIONS PROTOTYPES ]
*******************************************************************************/  
void initBestScores();
void updateBestScore(uint8_t selectedGame);
uint32_t getTimeMils(); // returns Timer_A counter
void wait(uint32_t interval); // waits some milliseconds
int8_t random(int8_t min, int8_t max); // generates a random number
void drawScoreText(); // draws the current score
void drawScore(uint16_t score); // draws the current score
void cleanBottomBar(); // cleans the bottom bar
uint16_t getButtons(); // returns 1 if A pressed, 2 if B pressed (Joystick), 0 otherwise
void drawRect(uint8_t xMin, uint8_t xMax, uint8_t yMin, uint8_t yMax, uint32_t color); // Generic function to draw Rectangle for cleaning purpose
void checkLastMove(); // This Function is to check joystick movement
void initGameData(); // This Function is to initialize the game data
bool consumeButtonA(); // This Function is to consume the button A
void startLEDBlinking(); // This Function is to start the LED blinking
void stopLEDBlinking(); // This Function is to stop the LED blinking
void showInitialTitle(Graphics_Image image); // This Function is to show the initial title
void showTutorial(Graphics_Image image); // This Function is to show the tutorial
void showTutorialBig(Graphics_Image image); //  This Function is to show the large tutorial
void showTutorialSmall(Graphics_Image image); // his Function is to show the small tutorial

/******************************************************************************
* [ HANDLER ]
*******************************************************************************/ 
void TA2_N_IRQHandler(void); // handler for timer_A
void ADC14_IRQHandler(void); // handler for Joystick


#endif /* _UTILITIES_H_ */

/*** End of File **************************************************************/
