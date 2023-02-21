// This function returns the current CounterValue of the TIMER_A2
uint32_t getTimeMils(){
    return Timer_A_getCounterValue(TIMER_A2_BASE);
}

/*  The max CounterValue is 65535 since we works with 16-bit registers (max_value = 2^(16)-1).
 *  The complex part is the management of situations in witch the CounterValue is reset because of
 *  it reaches it maximum value. So two different scenarios are managed: if this not happens and if not
 */
void wait(uint32_t interval){
    interval = interval / 2; // since 1000 ms = 512 ticks (about half)
    if (interval <= 60000){
        uint32_t start = getTimeMils();
        if (start + interval >= 65535){                 // if the CounterValue will be reset
            uint32_t waited = 65535 - start;
            while (getTimeMils() != 0);
            while(interval - waited > getTimeMils());
        } else{                                         // if not
            while(start + interval > getTimeMils());
        }
    }
}

// This function returns a random value between min and max
int8_t random(int8_t min, int8_t max) {
    return (rand()%(max-min+1))+min;
}

/*  This function updates the direction and lastMove variables by comparing the buffer values
 *  (updated in the handler) with a treshold value.
 *  The difference between direction and lastMove is that lastMove keeps its value until it's
 *  overwritten while direction is resetted at each interrupt
 */
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

// If the button A has been pressed it consumes its value and returns true, otherwise false
bool consumeButtonA(){
    if (buttonA == 1){
        buttonA = 0;
        return true;
    }
    return false;
}

// This function makes the LED start blinking
void startLEDBlinking(){
    //Timer_A_setOutputForOutputModeOutBitValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TIMER_A_OUTPUTMODE_OUTBITVALUE);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

// This function makes the LED stop blinking
void stopLEDBlinking(){
    //Timer_A_setOutputForOutputModeOutBitValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TIMER_A_OUTPUTMODE_OUTBITVALUE_LOW);
    Timer_A_stopTimer(TIMER_A0_BASE);
}

/*  Handler for the 2-Axis-Joystick event interrupts. The handler clears the interrupt flag and
 *  updates the buffer containing the x and y values.
 *  Finally it calls the checkLastMove() function
 */
void ADC14_IRQHandler(void) {
    uint64_t status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    if(status & ADC_INT1) { // ADC_MEM1 conversion completed
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0); // Store ADC14 conversion results
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
    }
    checkLastMove(); // function call
}

/*  Handler for the pressed button interrupt event.
 *  It works by checking single register bits. At the end it resets the interrupt flags
 *  Port 5 pin 1 ---> buttonA
 *  Port 3 pin 5 ---> buttonB
 */
void PORT5_IRQHandler(void){
    __disable_irq();
    if (P5->IFG & BIT1){
        buttonA = 1;
        P5->IFG &= ~BIT1;
    }
    __enable_irq();
}
