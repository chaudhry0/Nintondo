#include "Code/Menu/gameHub.h"
#include "Code/Images/backgroundImages.h"

void drawLogo(){
    drawRect(0, MAX_WIDTH - 1, 0, BAR_SIZE + MAX_HEIGHT + BAR_SIZE - 1, WHITE);
    Graphics_drawImage(&g_sContext, &imageLogo, 16, 52);
    wait(1500);
    cleanDisplayGame();
    Graphics_drawImage(&g_sContext, &imageBackground, 0, 0);
}

void drawGameOver(){
    Graphics_drawImage(&g_sContext, &imageGameOver, 16, 48);
    wait(TIME_GAMEOVER_GAME);
    cleanDisplayGame();
    cleanBottomBar();
}

void cleanDisplayGame(){
    drawRect(0, MAX_WIDTH - 1, CELL_SIZE_LARGE, MAX_HEIGHT + CELL_SIZE_LARGE - 1, WHITE);
}

void runGameHub(){
    consumeButtonA();   //to reset bottom A before the games appear
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
                runSuperDario();
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
    if (selectedGame<5){
        updateBestScore(selectedGame); // DA CONTROLLARE!
    }
    drawGameOver();
}
