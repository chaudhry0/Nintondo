#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "Code/Utilities/libs.h"


// [ GOLBAL CONSTANT ]
#define TIME_TITLE_GAME 2000
#define TIME_GAMEOVER_GAME 4000


// [ GLOBAL VARIABLES ]
static uint16_t resultsBuffer[2]; // buffer to store Joystick samples
char errore[20]; // temp Variable to test code
Graphics_Context g_sContext; // Graphic library context
int score; // game score
bool gameOver; // game status
int direzione; // value read from Joystick buffer
int lastMove; // previous move performed (equals to "direzione" but not reset every time)


// [ FUNCTIONS ]
uint32_t getTimeMils(); // returns Timer_A counter
void wait(uint32_t interval); // waits some milliseconds
int random(int min, int max); // generates a random number
uint16_t getButtons(); // returns 1 if A pressed, 2 if B pressed (Joystick), 0 otherwise
void drawRect(int xMin, int xMax, int yMin, int yMax, uint32_t color); // Generic function to draw Rectangle for cleaning purpose
void checkLastMove(); // ...


// [ HANDLER ]
void TA2_N_IRQHandler(void); // handler for timer_A
void ADC14_IRQHandler(void); // hanler for Joystick


#endif /* _UTILITIES_H_ */
