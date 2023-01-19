#include "bestScores.h"
#include "Code/Images/bestScoreImages.h"

void drawScores(){
    //char value[2];
    //sprintf(value, "%d", /*qualcosa*/);
    //Graphics_drawString(&g_sContext, value, 1, 112, 20, opaque);
}

void runBestScores(){
    Graphics_drawImage(&g_sContext, &imageBestScores, 0, 16);
    while(!gameOver){
        if (consumeButtonA()){
            gameOver = true;
        }
    }
}
