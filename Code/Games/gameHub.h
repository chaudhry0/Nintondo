#ifndef _CODE_GAMES_GAMEHUB_H_
#define _CODE_GAMES_GAMEHUB_H_

#include "snake.h"
#include "floppyDisk.h"
#include "pong.h"
#include "rhinoRunner.h"
#include "superDario.h"

#define NUM_GAMES 8


// [ GLOBAL VARIABLES ]
int selected; // selected games
Graphics_Image texts[4];
int menuNumber;


// [ FUNCTIONS ]
void drawLogo();
void cleanDisplayGame();
void initTextImages();
void runMenu();
void drawMenu();
void updateMenu();
void printText(Graphics_Image* imagePtr, int y);
void printTextInverse(Graphics_Image* imagePtr, int y);


#endif /* _CODE_GAMES_GAMEHUB_H_ */
