#ifndef CODE_GAMES_MENU_H_
#define CODE_GAMES_MENU_H_

#include "Code/Utilities/init.h"

#define NUM_ELEMENTS 4
#define NUM_GAMES 8

int numGioco;
int menuNumber;


void initElements(Graphics_Image* elementsPtr);
void drawElement(Graphics_Image* imagePtr, int y);
void drawArrow();
void drawMenu(Graphics_Image* elementsPtr);
void updateMenu(Graphics_Image* elementsPtr);
void runMenu();



#endif /* CODE_GAMES_MENU_H_ */
