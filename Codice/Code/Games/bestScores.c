#include "bestScores.h"
#include "Code/Images/bestScoreImages.h"

void drawScores(){
    int totalScore = 0;
    char value[2];
    int i;
    for (i=0; i<5; i++){
        sprintf(value, "%d", bestScores[i]);
        Graphics_drawString(&g_sContext, (int8_t *) value, 1, 112, BAR_SIZE + 20 + 9*i, true);
        totalScore += bestScores[i];
    }
    sprintf(value, "%d", totalScore);
    Graphics_drawString(&g_sContext, (int8_t *) value, 1, 112, 78 + BAR_SIZE, true);
}

void runBestScores(){
    Graphics_drawImage(&g_sContext, &imageBestScores, 0, 16);
    while(!gameOver){
        if (consumeButtonA()){
            gameOver = true;
        }
    }
}
