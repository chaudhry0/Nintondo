#include "utilities.h"


void initBestScores(){
    int i;
    for (i=0; i<NUM_GAMES; i++){
        bestScores[i] = 0;
    }
}

void updateBestScore(int selectedGame){
    if (score > bestScores[selectedGame]){
        bestScores[selectedGame] = score;
    }
}

uint32_t getTimeMils(){
    return Timer_A_getCounterValue(TIMER_A2_BASE);
}

void wait(uint32_t interval){
    interval = interval / 2;
    if (interval <= 60000){
        uint32_t start = getTimeMils();
        if (start + interval >= 65535){
            uint32_t waited = 65535 - start;
            while (getTimeMils() != 0);
            while(interval - waited > getTimeMils());
        } else{
            while(start + interval > getTimeMils());
        }
    }
}

int random(int min, int max) {
    return (rand()%(max-min+1))+min;
}

void drawScoreText(){
    Graphics_setForegroundColor(&g_sContext, WHITE);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) "score: ", 7, 64, 120, TRANSPARENT_TEXT);
}

void drawScore(int score) {
    char temp[10];
    drawRect(80, 100, 115, 125, RED);
    Graphics_setForegroundColor(&g_sContext, WHITE);
    sprintf(temp, "%d", score);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) temp, 3, 90, 120, TRANSPARENT_TEXT);
}

void cleanBottomBar(){
    drawRect(CELL_LARGE - 1, MAX_WIDTH - CELL_LARGE, MAX_HEIGHT + CELL_LARGE, MAX_HEIGHT + 2* CELL_LARGE, RED);
}



void drawRect(int xMin, int xMax, int yMin, int yMax, uint32_t color) {
    Graphics_Rectangle rect;
    rect.xMin = xMin;
    rect.xMax = xMax;
    rect.yMin = yMin;
    rect.yMax = yMax;
    Graphics_setForegroundColor(&g_sContext, color);
    Graphics_fillRectangle(&g_sContext, &rect);
}

void checkLastMove(){
    direction = 0;
    if (resultsBuffer[0] < 3000) {
            direction = lastMove = 4;
        } else if (resultsBuffer[0] > 13000) {
            direction = lastMove = 2;
        } else if (resultsBuffer[1] < 3000) {
            direction = lastMove = 3;
        } else if (resultsBuffer[1] > 13000) {
            direction = lastMove = 1;
        }
}

void initGameData(){
    score = 0;
    gameOver = false;
    consumeButtonA();   // resets bottom A before the games appear
}

void TA2_N_IRQHandler(void) {
    Timer_A_clearInterruptFlag(TIMER_A2_BASE);
}



// Old function to get buttonA pressed condition
/*uint16_t getButtons(){
    if (!GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1)){  // A
        return 1;
    }
    if (!GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN5)){  // B
        return 2;
    }
    return 0;
}*/


void PORT5_IRQHandler(void){
    // Port 5 pin 1 ---> buttonA
    // Port 3 pin 5 ---> buttonB
    __disable_irq();
    if (P5->IFG & BIT1){
        buttonA = 1;
        P5->IFG &= ~BIT1;
    }
    __enable_irq();
}

bool consumeButtonA(){
    if (buttonA == 1){
        buttonA = 0;
        return true;
    }
    return false;
}

void showTutorialBig(Graphics_Image image){
    Graphics_drawImage(&g_sContext, &image, 0, CELL_LARGE + MAX_HEIGHT/2 - CELL_LARGE/2 - 6);
    wait(SHORT_TIME);
}

void showTutorialSmall(Graphics_Image image){
    Graphics_drawImage(&g_sContext, &image, 0, CELL_LARGE + MAX_HEIGHT/2 - CELL_LARGE/2);
    wait(SHORT_TIME);
}

void showInitialTitle(Graphics_Image image){
    Graphics_drawImage(&g_sContext, &image, 0, CELL_LARGE);
    wait(SHORT_TIME);
}


void ADC14_IRQHandler(void) {
    uint64_t status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    if(status & ADC_INT1) { // ADC_MEM1 conversion completed
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0); // Store ADC14 conversion results
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
    }
    checkLastMove();

    /*int buttonPressed = 0;    //sensitive stick button
    if (!(P4IN & GPIO_PIN1))
        buttonPressed = 1;*/
}

void startLEDBlinking(){
    //Timer_A_setOutputForOutputModeOutBitValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TIMER_A_OUTPUTMODE_OUTBITVALUE);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

void stopLEDBlinking(){
    //Timer_A_setOutputForOutputModeOutBitValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TIMER_A_OUTPUTMODE_OUTBITVALUE_LOW);
    Timer_A_stopTimer(TIMER_A0_BASE);
}
