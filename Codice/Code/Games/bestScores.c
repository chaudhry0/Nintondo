#include "bestScores.h"
#include "Code/Images/bestScoreImages.h"

void drawScores(){
    int totalScore = 0;
    char value[10];
    int i;
    Graphics_setForegroundColor(&g_sContext, BLACK);
    for (i=0; i<5; i++){
        sprintf(value, "%d", bestScores[i]);
        Graphics_drawString(&g_sContext, (int8_t *) value, 3, 110, BAR_SIZE + 18 + 10*i, TRANSPARENT_TEXT);
        totalScore += bestScores[i];
    }
    if (totalScore<100){
        sprintf(value, "%d", totalScore);
    }else{
        sprintf(value, "99");
    }

    Graphics_drawString(&g_sContext, (int8_t *) value, 3, 110, 76 + BAR_SIZE, TRANSPARENT_TEXT);
}

void runBestScores(){
    Graphics_drawImage(&g_sContext, &imageBestScores, 0, 16);
    drawScores();
    while(!gameOver){
        if (consumeButtonA()){
            gameOver = true;
        }
    }
}
