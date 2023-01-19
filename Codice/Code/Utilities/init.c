#include "init.h"

const Timer_A_ContinuousModeConfig continuousModeConfig = {
        TIMER_A_CLOCKSOURCE_ACLK,           // ACLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_64,     // ACLK/64 = 1 kHz
        TIMER_A_TAIE_INTERRUPT_ENABLE,      // Enable Overflow ISR
        TIMER_A_DO_CLEAR                    // Clear Counter
};

void _adcInit() {
    /* Configures Pin 6.0 and 4.4 as ADC input */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
    /* Initializing ADC (ADCOSC/64/8) */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);
    /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A15, A9)  with repeat) with internal 2.5v reference */
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);
    /* Enabling the interrupt when a conversion on channel 1 (end of sequence) is complete and enabling conversions */
    ADC14_enableInterrupt(ADC_INT1);
    /* Enabling Interrupts */
    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();
    /* Setting up the sample timer to automatically step through the sequence convert */
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    /* Triggering the start of the sample */
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}

void _graphicsInit() {
    Crystalfontz128x128_Init(); // Initializes display
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP); // Set default screen orientation
    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_PURPLE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);
}

void _lightSensorInit() {
    /* Initialize I2C communication */
    Init_I2C_GPIO();
    I2C_init();

    /* Initialize OPT3001 digital ambient light sensor */
    OPT3001_init();

    __delay_cycles(100000);

}

void configurePushButtons() {
    // Button B
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5,GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5,GPIO_PIN1);
    // Button A
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3,GPIO_PIN5);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P3,GPIO_PIN5);
}

void configureTimerA() {
    Timer_A_configureContinuousMode(TIMER_A2_BASE, &continuousModeConfig); // setup clock for the wait function
    Interrupt_enableInterrupt(INT_TA2_N); // enabling interrupts and going to sleep
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_CONTINUOUS_MODE); // Starting the Timer_A2 in continuous mode
}


void _initButton(){
    P5->SEL0 &= ~BIT1;
    P5->SEL0 &= ~BIT1;
    P5->DIR &= ~BIT1;
    P5->REN |= BIT1;
    P5->OUT |= BIT1;
    P5->IFG &= ~BIT1;
    P5->IES |= BIT1;
    P5->IE |= BIT1;
    NVIC_EnableIRQ(PORT5_IRQn);
}

void _hwInit() {
    /* Halting WDT and disabling master interrupts */
    WDT_A_holdTimer();
    Interrupt_disableMaster();
    /* Set the core voltage level to VCORE1 */
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    /* Initializes Clock System */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_3);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    // other configurations/initializations
    configureTimerA();
    _lightSensorInit();
    _graphicsInit();
    _adcInit();
    configurePushButtons();
    _initButton();

    srand(time(0));
}