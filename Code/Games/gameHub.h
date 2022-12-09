#ifndef _CODE_GAMES_GAMEHUB_H_
#define _CODE_GAMES_GAMEHUB_H_

#include "snake.h"
#include "floppyDisk.h"

#define NUM_GAMES 4


// [ GLOBAL VARIABLES ]
int selected; // selected games


// [ FUNCTIONS ]
void runMenu();
void drawMenu();
void updateMenu();
void printTitle(int y);
void printTitleInverse(int y);
void initGameData();


#endif /* _CODE_GAMES_GAMEHUB_H_ */
