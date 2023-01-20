#ifndef CODE_GAMES_MENU_H_
#define CODE_GAMES_MENU_H_

#include "Code/Utilities/init.h"

#define NUM_ELEMENTS 4
#define NUM_GAMES 8


int selectedGame; // index of the current selected game
int menuNumber; // 0: first menu; 1: second menu

// [FUNCTIONS]
// init functions
    void initElements(Graphics_Image* elementsPtr);
// moving/updating functions
    void updateArrowAndElements(Graphics_Image* elementsPtr);
// bool functions
// draw functions
    void drawElement(Graphics_Image* imagePtr, int y);
    void drawArrow();
    void drawMenu(Graphics_Image* elementsPtr);
// run functions
    void runMenu();









#endif /* CODE_GAMES_MENU_H_ */
