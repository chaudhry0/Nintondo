#include "Code/Menu/gameHub.h"
#include "Code/Images/backgroundImages.h"

void drawLogo(){
    drawRect(0, MAX_WIDTH - 1, 0, BAR_SIZE + MAX_HEIGHT + BAR_SIZE - 1, WHITE);
    Graphics_drawImage(&g_sContext, &imageLogo, CELL_LARGE, BAR_SIZE + 36);
    wait(LONG_TIME);
    cleanDisplayGame();
    Graphics_drawImage(&g_sContext, &imageBackground, 0, 0);
}

void drawGameOver(){
    Graphics_drawImage(&g_sContext, &imageGameOver, CELL_LARGE, BAR_SIZE + 32);
    wait(LONG_TIME);
}

void cleanDisplayGame(){
    drawRect(0, MAX_WIDTH - 1, CELL_LARGE, MAX_HEIGHT + CELL_LARGE - 1, WHITE);
}

void runGameHub(){
    consumeButtonA();   // resets bottom A before the games appear
    runMenu();
    cleanDisplayGame();
    initGameData();
    if (menuNumber == 0){
        switch(selectedGame){
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
            default:
                break;
        }
    } else{ // menuNumber = 1
        switch(selectedGame){
            case 0:
                runSpaceGame();
                break;
            case 1:
                //runSuperDario();
                break;
            case 2:
                runBestScores();
                break;
            case 3:
                runAbout();
                break;
            default:
                break;
        }
    }
    if (menuNumber==0 || selectedGame<2){
        updateBestScore(selectedGame + menuNumber * NUM_ELEMENTS);
        drawGameOver();
        cleanBottomBar();
    }
    cleanDisplayGame();
}
