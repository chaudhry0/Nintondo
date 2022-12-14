#include <Code/Games/gameHub.h>
#include <Code/Images/menuImages.h>
#include "Code/Images/backgroundImages.h"

void drawLogo(){
    Graphics_drawImage(&g_sContext, &imageLogo, 16, 52);
    wait(1500);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawImage(&g_sContext, &imageBackground, 0, 0);
}

void cleanDisplayGame(){
    Graphics_setForegroundColor(&g_sContext, 0xffffff);
    Graphics_Rectangle rectangle;
    rectangle.xMin = 0;
    rectangle.xMax = MAX_WIDTH - 1;
    rectangle.yMin = CELL_SIZE_LARGE;
    rectangle.yMax = MAX_HEIGHT + CELL_SIZE_LARGE - 1;
    Graphics_fillRectangle(&g_sContext, &rectangle);
    Graphics_setForegroundColor(&g_sContext, 0xff0000);
    rectangle.xMin = 0;
    rectangle.xMax = MAX_WIDTH - 1;
    rectangle.yMin = CELL_SIZE_LARGE + MAX_HEIGHT;
    rectangle.yMax = CELL_SIZE_LARGE + MAX_HEIGHT + CELL_SIZE_LARGE - 1;
    Graphics_fillRectangle(&g_sContext, &rectangle);
}

void runMenu(){
    direzione = lastMove = selected = 0;
    //int selected = 0;
    bool gameSelected = false;
    initTextImages();
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
                    runPong();
                    break;
                case 2:
                    runRhino();
                    break;
                case 3:
                    runFloppyDisk();
                    break;
            }
            Graphics_drawImage(&g_sContext, &imageGameOver, 16, 48);
            wait(TIME_GAMEOVER_GAME);
        }
        if (direzione != 0 && !gameSelected){
            updateMenu();
            drawMenu();
        }
    }
    cleanDisplayGame();
}

void initTextImages(){
    texts[0] = imageTextSnake;
    texts[1] = imageTextPong;
    texts[2] = imageTextRhino;
    texts[3] = imageTextFloppyDisk;
}

void drawMenu(){
   Graphics_drawImage(&g_sContext, &imageTextSelectGame, 23, 26);
   int i;
   for (i=0; i<NUM_GAMES; i++){
       if (selected == i){
           printTextInverse(&texts[i], 40 + 16 * i);
       } else{
           printText(&texts[i], 40 + 16 * i);
       }
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

void printText(Graphics_Image* imagePtr, int y){
    Graphics_drawImage(&g_sContext, imagePtr, 16, y);
}

void printTextInverse(Graphics_Image* imagePtr, int y){
    imagePtr->pPalette = paletteDefaultInverse;
    Graphics_drawImage(&g_sContext, imagePtr, 16, y);
    imagePtr->pPalette = paletteDefault;
}