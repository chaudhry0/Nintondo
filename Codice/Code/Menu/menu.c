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
       int numTitlesToDraw = NUM_ELEMENTS - menuNumber;
       for (i=0; i<numTitlesToDraw; i++){
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
        *(elementsPtr) = imageTextSnake;
        *(elementsPtr + 1) = imageTextSpaceInvaders;
        *(elementsPtr + 2) = imageTextAbout;
        //*(elementsPtr + 3) = ;
    }
}

void updateMenu(Graphics_Image* elementsPtr){
    if (lastMove == 1){
        if (numGioco != 0){ // if same menu
            numGioco--;
            int y = 40 + 16 * numGioco + 16;
            drawRect(112, 128, y, y+16, WHITE);
        } else if (menuNumber == 1) { // must change menu
            menuNumber = 0;
            numGioco = NUM_ELEMENTS - 1;
            initElements(elementsPtr);
            drawMenu(elementsPtr);
            int y = 40;
            drawRect(112, 128, y, y+16, WHITE);
        }
    }
    if (lastMove == 3){
        if (numGioco != NUM_ELEMENTS - 1){
            numGioco++;
            int y = 40 + 16 * numGioco - 16;
            drawRect(112, 128, y, y+16, WHITE);
        } else if (menuNumber == 0){
            menuNumber = 1;
            numGioco = 0;
            initElements(elementsPtr);
            drawMenu(elementsPtr);
            int y = 40 + 16 * (NUM_ELEMENTS - 1);
            drawRect(112, 128, y, y+16, WHITE);
        }
    }
}

void runMenu(){
    bool gameSelected = false;
    numGioco = 0;
    menuNumber = 0;
    Graphics_Image imageElements[4];
    direzione = 0;
    initElements(&imageElements[0]);
    drawMenu(&imageElements[0]);
    drawArrow();

    while (!gameSelected){
        __sleep(); // LPM or something similar
        if (direzione){
            updateMenu(&imageElements[0]);
            drawArrow();
            wait(150);
        }
        if (consumeButtonA()){
            gameSelected = true;
        }
    }
}
