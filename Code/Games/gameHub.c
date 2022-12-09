#include <Code/Games/gameHub.h>
#include <Code/Images/menuImages.h>
#include "Code/Images/backgroundImages.h"

void initGameData() {
    score = 0;
    gameOver = false;
}

void runMenu(){
    direzione = lastMove = selected = 0;
    bool gameSelected = false;
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawImage(&g_sContext, &imageBackground, 0, 0);
    drawMenu();
    while (!gameSelected){
        if (getButtons() == 1){
            initGameData();
            gameSelected = true;
            switch(selected){
                case 0:
                    runSnake();
                    break;
                case 1:
                    runFloppyDisk();
                    break;
            }
        }
        if (direzione != 0 && !gameSelected){
            updateMenu();
            drawMenu();
        }
    }
}

void drawMenu(){
   int i;
   int heigh = 40;

   for (i=0; i<selected; i++){
       printTitle(40+16*i);
       heigh+=16;
   }
   printTitleInverse(heigh);
   for (i+=1; i<NUM_GAMES; i++){
       printTitle(40+16*i);
   }
}

void updateMenu(){
    if (direzione == 1){ // up
        if (selected != 0){
            selected--;
        }
    } else if (direzione == 3){ // down
        if (selected != NUM_GAMES-1){
            selected++;
        }
    }
}

void printTitle(int y){
    Graphics_drawImage(&g_sContext, &imageTitleSnake, 16, y);
}

void printTitleInverse(int y){
    imageTitleSnake.pPalette = paletteDefaultInverse;
    Graphics_drawImage(&g_sContext, &imageTitleSnake, 16, y);
    imageTitleSnake.pPalette = paletteDefault;
}
