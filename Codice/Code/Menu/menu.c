#include <Code/Menu/menu.h>
#include <Code/Images/menuImages.h>

void drawElement(Graphics_Image* imagePtr, int y){
    Graphics_drawImage(&g_sContext, imagePtr, 16, y);
}

void drawArrow(){
    int y = 40 + 16 * numGioco;
    switch(lastMove){
        case 1:
            break;
        case 3:
            break;
        default:
            break;
    }
    Graphics_drawImage(&g_sContext, &imageArrow, 112, y);
}

void drawMenu(Graphics_Image* elementsPtr){
    Graphics_drawImage(&g_sContext, &imageTextSelectGame, 23, 26);
       int i;
       for (i=0; i<NUM_ELEMENTS; i++){
           drawElement(elementsPtr + i, 40 + 16 * i);
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

void updateArrowAndElements(Graphics_Image* elementsPtr){
    if (lastMove == 1){ // pushing UP
        if (numGioco != 0){ // if the selected game isn't the first of the relative list
            numGioco--;
            int tmpY = 40 + 16 * numGioco + 16;
            drawRect(112, 127, tmpY, tmpY+15, WHITE); // clean arrow
        } else if (menuNumber == 1) { // if you are on the second menu
            menuNumber = 0; // change menuNumber
            numGioco = NUM_ELEMENTS - 1; // change the current selected game
            initElements(elementsPtr); // inits new Titles
            drawMenu(elementsPtr); // draw the new menu
            drawRect(112, 128, 40, 40+16, WHITE);
        }
    }
    if (lastMove == 3){ // pushing DOWN
        if (numGioco != NUM_ELEMENTS - 1){ // if the selected game isn't the last of the relative list
            numGioco++;
            int tmpY = 40 + 16 * numGioco - 16;
            drawRect(112, 128, tmpY, tmpY+16, WHITE); // clean arrow
        } else if (menuNumber == 0){ // if you are on the first menu
            menuNumber = 1; // change menuNumber
            numGioco = 0; // change the current selected game
            initElements(elementsPtr); // inits new Titles
            drawMenu(elementsPtr); // draw the new menu
            int tmpY = 40 + 16 * (NUM_ELEMENTS - 1);
            drawRect(112, 128, tmpY, tmpY+16, WHITE);
        }
    }
}

void runMenu(){
    bool gameSelected = false;
    numGioco = 0;
    menuNumber = 0;
    Graphics_Image imageElements[4];
    direction = 0;
    initElements(&imageElements[0]);
    drawMenu(&imageElements[0]);
    drawArrow();

    while (!gameSelected){
        __sleep(); // LPM or something similar
        if (direction){
            updateArrowAndElements(&imageElements[0]);
            drawArrow();
            wait(150);
        }
        if (consumeButtonA()){
            gameSelected = true;
        }
    }
}
