#ifndef _CODE_GAMES_GAMEHUB_H_
#define _CODE_GAMES_GAMEHUB_H_

#include "menu.h"
#include "Code/Games/snake.h"
#include "Code/Games/floppyDisk.h"
#include "Code/Games/pong.h"
#include "Code/Games/rhinoRunner.h"
#include "Code/Games/superDario.h"
#include "Code/Games/spaceGame.h"
#include "Code/Games/bestScores.h"
#include "Code/Games/about.h"


// [ FUNCTIONS ]
// init functions
// moving/updating functions
// bool functions
// draw functions
    void drawLogo(); // draws initial text "Ninotondo"
    void drawGameOver(); //draws the GameOver image (equal for all games)
    void cleanDisplayGame(); // clean the display (only the central section, not the red bars)
// run functions
    void runGameHub(); // runMenu function



#endif /* _CODE_GAMES_GAMEHUB_H_ */
