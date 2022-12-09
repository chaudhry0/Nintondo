#include "utilities.h"


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

uint16_t getButtons(){
    if (!GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1)){  // A
        return 1;
    }
    if (!GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN5)){  // B
        return 2;
    }
    return 0;
}

void drawRect(int xMin, int xMax, int yMin, int yMax, uint32_t color) {
    Graphics_Rectangle rect;
    rect.xMin = xMin;
    rect.xMax = xMax;
    rect.yMin = yMin;
    rect.yMax = yMax;
    //printf("Y: [ %d, %d] \n", yMin, yMax);
    //fflush(stdout);
    Graphics_setForegroundColor(&g_sContext, color);
    Graphics_fillRectangle(&g_sContext, &rect);
}

void checkLastMove(){
    direzione = 0;
    if (resultsBuffer[0] < 3000) {
            direzione = lastMove = 4;
        } else if (resultsBuffer[0] > 13000) {
            direzione = lastMove = 2;
        } else if (resultsBuffer[1] < 3000) {
            direzione = lastMove = 3;
        } else if (resultsBuffer[1] > 13000) {
            direzione = lastMove = 1;
        }
}

void TA2_N_IRQHandler(void) {
    Timer_A_clearInterruptFlag(TIMER_A2_BASE);
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
