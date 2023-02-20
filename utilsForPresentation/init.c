#include "init.h"

/*  This timer is used in the wait() function
 *  CONTINUOUS MODE: the timer counts up to the maximum value reachable
 *  (16bit-registers ---> 0xFFFF = 65535). After that it starts again from 0
 */
const Timer_A_ContinuousModeConfig continuousModeConfig = {
        TIMER_A_CLOCKSOURCE_ACLK,           // it uses the ACLK Clock Source (32.768khz)
        TIMER_A_CLOCKSOURCE_DIVIDER_64,     // 32768/64 = 512 Hz (512 ticks each second)
        TIMER_A_TAIE_INTERRUPT_ENABLE,      // Enable Overflow ISR
        TIMER_A_DO_CLEAR                    // to clear decides the divider, direction and count
};

/* Timer_A Compare Configuration Parameter  (PWM)
 * COMPARE MODE: the timer counts until the Timer Register is equal to the Compare Register
 */
Timer_A_CompareModeConfig compareConfig_PWM = {
        TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CaptureCompareRegister3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // output mode
        23437                                       // 50% Duty Cycle (46874/2)
        };

/* Timer_A Up Configuration Parameter
 * UP MODE: the timer repeatedly counts from zero to the value of the Compare Register
 */
const Timer_A_UpModeConfig upConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK = 3 MhZ
        TIMER_A_CLOCKSOURCE_DIVIDER_64,         // SMCLK/64 = 46875 Hz (46874 each second)
        46874,                                  // 1 second
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // to clear decides the divider, direction and count
        };

// Function to initialize the red LED (pin 6, port 2). It will works in the PWM mode
void _ledInit(){
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig); // configures the TIMER_A0 with the "upConfig" configuration
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM); // inits the TIMER_A0 with the compareConfig_PWM configuration
}

/*  ADC initializations, required by the Joystick
 * Port 6, Pin 0 for the X-axis
 * Port 4, Pin 4 for the Y-axis
 *
 */
void _adcInit() {
    // Configures Pin 6.0 and 4.4 as ADC input
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
    // enables the ADC block
    ADC14_enableModule();
    // Initializes the ADC module and sets up the clock system with the  divider and pre-divider (ADCOSC/(64*8))
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

// Function to initialize the display
void _graphicsInit() {
    Crystalfontz128x128_Init(); // Initializes display
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP); // Sets default screen orientation
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs); // initializes the context
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE); // Sets the bg color font
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8); // Sets the default font
    Graphics_clearDisplay(&g_sContext); // cleans the display
}

void _lightSensorInit() {
    /* Initialize I2C communication */
    Init_I2C_GPIO();
    I2C_init();
    /* Initialize OPT3001 digital ambient light sensor */
    OPT3001_init();
    __delay_cycles(100000);

}

// Timer_A2 configuration, useful for the wait() function implementation
void configureTimer_A2_BASE() {
    // configures the Timer_A2 in continuous mode
    Timer_A_configureContinuousMode(TIMER_A2_BASE, &continuousModeConfig);
    // enables interrupts
    Interrupt_enableInterrupt(INT_TA2_N);
    // starts the Timer_A2 timer (continuous mode)
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_CONTINUOUS_MODE);
}

// Function to initialize the the pin 1 of the port 5 (for the button A pressed event)
void _initButton(){
    P5->SEL0 &= ~BIT1;              // sets as I/O
    P5->SEL0 &= ~BIT1;              // sets as I/O
    P5->DIR &= ~BIT1;               // configure as input
    P5->REN |= BIT1;                // enable the pullup mode
    P5->OUT |= BIT1;                // select the pullup mode
    P5->IFG &= ~BIT1;               // cleans the InterruptFlag
    P5->IES |= BIT1;                // Port Interrupt Edge Select
    P5->IE |= BIT1;                 // to set the rising edge mode
    NVIC_EnableIRQ(PORT5_IRQn);     // to enable interrupts from the port 5
}

void _hwInit() {
    WDT_A_holdTimer(); // Halting WDT and disabling master interrupts
    Interrupt_disableMaster();
    PCM_setCoreVoltageLevel(PCM_VCORE1); // Set the core voltage level to VCORE1
    // Initializes Clock System
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_3);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    // Configurations and Initializations of sensors and hardware stuff
    configureTimer_A2_BASE();
    _lightSensorInit();
    _graphicsInit();
    _adcInit();
    _ledInit();
    _initButton();
    srand(time(0));
}
