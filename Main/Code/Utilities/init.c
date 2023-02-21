/*******************************************************************************
* Title                 :   INIT
* Filename              :   init.c
* Last Revision Date    :   07/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file init.c
 *
 * @brief This module is the implementation file for the initialization functions.
 *        It contains the functions to initialize the hardware.
 *        It contains the functions to initialize the peripherals.
 *        It contains the functions to initialize the LCD.
 *        It contains the functions to initialize the ADC.
 *        It contains the functions to initialize the light sensor.
 *        It contains the functions to initialize the Timer_A.
 *        It contains the functions to initialize the Joystick buttons.       
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "init.h"

const Timer_A_ContinuousModeConfig continuousModeConfig = {
        TIMER_A_CLOCKSOURCE_ACLK,           // it uses the ACLK Clock Source (32.768khz)
        TIMER_A_CLOCKSOURCE_DIVIDER_64,     // 32768/64 = 512 Hz (512 ticks each second)
        TIMER_A_TAIE_INTERRUPT_ENABLE,      // Enable Overflow ISR
        TIMER_A_DO_CLEAR                    // to clear decides the divider, direction and count
};

/* Timer_A Compare Configuration Parameter  (PWM) */
Timer_A_CompareModeConfig compareConfig_PWM = {
        TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CaptureCompareRegister3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // output mode
        23437                                       // 50% Duty Cycle (46874/2)
        };

/* Timer_A Up Configuration Parameter */
const Timer_A_UpModeConfig upConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK = 3 MhZ
        TIMER_A_CLOCKSOURCE_DIVIDER_64,         // SMCLK/64 = 46875 Hz (46874 each second)
        46874,                                  // 1 second
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // to clear decides the divider, direction and count
        };

/******************************************************************************
* [ FUNCTIONS PROTOTYPES ]
*******************************************************************************/ 
/*!
 * @brief This Function is to initialize the hardware for led.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void _ledInit(){
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6,
    GPIO_PRIMARY_MODULE_FUNCTION);
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM);
}

/*!
 * @brief This Function is to initialize the hardware for ADC.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void _adcInit() {
    // Configures Pin 6.0 and 4.4 as ADC input
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
    /* Initializing ADC (ADCOSC/64/8) */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);
    /* configures the ADC module to use a a multiple memory sample scheme
     * (multiple samples will be taken and stored in multiple memory locations)
     *
     * ADC_MEM0 is the address of the first space, ADC_MEM1 the address of the last space where to store converted values.
     * The last "true" value enables the "repeatMode": conversions are repeated after that the first one is completed
     */
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
    /*  some other memory configurations for the ADC module
     *  parameters:
     *              - memorySelect:     memory address to configure
     *              - refSelect:        voltage reference to use for the selected memory spot
     *              - channelSelect:    selects the channel to be used for ADC sampling
     *              - differntialMode:  configures the selected channel in the differential mode
     */
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);
    // enables the interrupt when a conversion takes place on the channel 1
    ADC14_enableInterrupt(ADC_INT1);
    // enables the specified interrupt in the interrupt controller
    Interrupt_enableInterrupt(INT_ADC14);
    // to enable interrupts
    Interrupt_enableMaster();
    /*  configures the ADC module with the Sample Timer
     *  ADC_AUTOMATIC_ITERATION: After one sample/convert is finished, the ADC module will
     *                           automatically continue on to the next sample
     */
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    // enables conversion
    ADC14_enableConversion();
    // triggers the first conversion ---> the ADC will continue to take conversions
    ADC14_toggleConversionTrigger();
}

/*!
 * @brief This Function is to initialize the hardware for LCD.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is to initialize the hardware for light sensor.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void _lightSensorInit() {
    /* Initialize I2C communication */
    Init_I2C_GPIO();
    I2C_init();
    /* Initialize OPT3001 digital ambient light sensor */
    OPT3001_init();
    __delay_cycles(100000);
}

/*!
 * @brief This Function is to configure the hardware for Timer_A2_BASE.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void configureTimer_A2_BASE() {
    Timer_A_configureContinuousMode(TIMER_A2_BASE, &continuousModeConfig); // setup clock for the wait function
    Interrupt_enableInterrupt(INT_TA2_N); // enabling interrupts and going to sleep
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_CONTINUOUS_MODE); // Starting the Timer_A2 in continuous mode
}

/*!
 * @brief This Function is to initialize the hardware for buttons.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function calls all other initialization functions.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
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
    configureTimer_A2_BASE();
    _lightSensorInit();
    _graphicsInit();
    _adcInit();
    _ledInit();
    _initButton();

    srand(time(0));
}

/*** End of File **************************************************************/
