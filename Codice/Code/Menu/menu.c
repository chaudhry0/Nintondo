#include <Code/Menu/menu.h>
#include <Code/Images/menuImages.h>

void drawElement(Graphics_Image* imagePtr, int y){
    Graphics_drawImage(&g_sContext, imagePtr, CELL_LARGE, y);
}

void drawArrow(){
    int tmpY = BAR_SIZE + CELL_LARGE + CELL_SMALL + CELL_LARGE * selectedGame;
    Graphics_drawImage(&g_sContext, &imageArrow, MAX_WIDTH - CELL_LARGE, tmpY);
}

void drawMenu(Graphics_Image* elementsPtr){
    Graphics_drawImage(&g_sContext, &imageTextSelectGame, 23, 26);
       int i;
       for (i=0; i<NUM_ELEMENTS; i++){
           drawElement(elementsPtr + i, BAR_SIZE + CELL_LARGE + CELL_SMALL + CELL_LARGE * i);
       }
}

void initElements(Graphics_Image* elementsPtr){
    if (menuNumber == 0){
        *(elementsPtr) = imageTextSnake;
        *(elementsPtr + 1) = imageTextPong;
        *(elementsPtr + 2) = imageTextRhino;
        *(elementsPtr + 3) = imageTextFloppyDisk;
    }
    if (menuNumber == 1){
        *(elementsPtr) = imageTextSpaceInvaders;
        *(elementsPtr + 1) = imageTextSnake;
        *(elementsPtr + 2) = imageTextBestScores;
        *(elementsPtr + 3) = imageTextAbout;
    }
}

void updateArrow(){
    if (lastMove == 1){ // pushing UP
        selectedGame--;
    }else if (lastMove == 3){ // pushing DOWN
        selectedGame++;
    }
}

void cleanArrow(){
    int tmpY = BAR_SIZE + CELL_LARGE + CELL_SMALL + CELL_LARGE * selectedGame;
    drawRect(MAX_WIDTH - CELL_LARGE, MAX_WIDTH, tmpY, tmpY + CELL_LARGE - 1, WHITE);
}

void runMenu(){
    bool gameSelected = false;
    selectedGame = 0;
    menuNumber = 0;
    Graphics_Image imageElements[NUM_ELEMENTS];
    direction = 0;
    initElements(&imageElements[0]);
    drawMenu(&imageElements[0]);
    drawArrow();

    while (!gameSelected){
        __sleep(); // LPM
        if (direction){
            cleanArrow();
            updateArrow();
            if (menuNumber == 0){
                if (selectedGame == -1){
                    selectedGame = 0;
                }else if (selectedGame == NUM_ELEMENTS){
                    selectedGame = 0;
                    menuNumber = 1;
                    initElements(&imageElements[0]);
                    drawMenu(&imageElements[0]);
                }
            }
            else if (menuNumber == 1){
                if (selectedGame == NUM_ELEMENTS){
                    selectedGame = NUM_ELEMENTS - 1;
                }else if (selectedGame == -1){
                    selectedGame = NUM_ELEMENTS - 1;
                    menuNumber = 0;
                    initElements(&imageElements[0]);
                    drawMenu(&imageElements[0]);
                }
            }
            drawArrow();
            wait(MENU_SPEED);
        }
        if (consumeButtonA()){
            gameSelected = true;
        }
    }
}
