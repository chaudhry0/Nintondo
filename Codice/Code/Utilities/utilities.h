#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "Code/Utilities/libs.h"


// [ GOLBAL CONSTANT ]
#define TIME_TITLE_GAME 2000
#define TIME_GAMEOVER_GAME 4000
#define MAX_HEIGHT 96
#define MAX_WIDTH 128
#define CELL_SIZE_SMALL 8
#define CELL_SIZE_LARGE 16
#define BAR_SIZE 16


// [ GLOBAL VARIABLES ]
static uint16_t resultsBuffer[2]; // buffer to store Joystick samples
Graphics_Context g_sContext; // Graphic library context
int score; // game score
bool gameOver; // game status
int direzione; // value read from Joystick buffer
int lastMove; // previous move performed (equals to "direzione" but not reset every time)
int buttonA;
int bestScores[5];


// [ FUNCTIONS ]
void initBestScores();
void updateBestScore(int numGioco);
uint32_t getTimeMils(); // returns Timer_A counter
void wait(uint32_t interval); // waits some milliseconds
int random(int min, int max); // generates a random number
void drawScoreText(); // draws the current score
void drawScore(int score); // draws the current score
void cleanBottomBar();
uint16_t getButtons(); // returns 1 if A pressed, 2 if B pressed (Joystick), 0 otherwise
void drawRect(int xMin, int xMax, int yMin, int yMax, uint32_t color); // Generic function to draw Rectangle for cleaning purpose
void checkLastMove(); // ...
void initGameData();
bool consumeButtonA();
void showInitialTitle(Graphics_Image image);


// [ HANDLER ]
void TA2_N_IRQHandler(void); // handler for timer_A
void ADC14_IRQHandler(void); // handler for Joystick


#endif /* _UTILITIES_H_ */
