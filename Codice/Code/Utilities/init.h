#ifndef _INIT_H_
#define _INIT_H_

#include "Code/Utilities/utilities.h"


// [GLOBAL VARS]


// [FUNCTIONS]
void _adcInit(); // initializes ADC
void _graphicsInit(); // initializes LCD
void _lightSensorInit(); // initializes ligh sensor
void configurePushButtons(); // configures Joystick buttons
void configureTimerA(); // configures Timer_A
void _hwInit(); // initializes hardware


#endif /* _INIT_H_ */
