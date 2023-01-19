#include "Code/Games/about.h"
#include "Code/Images/abaoutImages.h"

void drawAbout1(){
    Graphics_drawImage(&g_sContext, &imageAbout1, 0, BAR_SIZE);
}

void drawAbout2(){
    Graphics_drawImage(&g_sContext, &imageAbout2, 0, BAR_SIZE);
}

void runAbout(){
    int numAbout = 0;
    drawAbout1();
    wait(500);
    while(!gameOver){
        if (consumeButtonA()){
            if (numAbout == 0){
                drawAbout2();
                numAbout++;
                wait(500);
            } else if (numAbout == 1){
                gameOver = true;
            }
        }
    }
}
