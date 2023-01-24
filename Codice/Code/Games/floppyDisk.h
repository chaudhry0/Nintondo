/*******************************************************************************
* Title                 :   FLOPPY DISK
* Filename              :   floppyDisk.h
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file floppyDisk.c
 *
 * @brief This is the header file for the floppy disk game
 *        It contains all the useful functions and variables for the game
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
#ifndef CODE_GAMES_FLOPPYDISK_H_
#define CODE_GAMES_FLOPPYDISK_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include "Code/Utilities/init.h"
/******************************************************************************
* Macros
*******************************************************************************/
// [DISPLAY]
#define MAX_Y_SIZE 128
#define MAX_X_SIZE 136
#define BORDER 16
// [FLOPPY DISK]
#define FLOPPY_HEIGHT 16
#define FLOPPY_WIDTH 32
#define FLOPPY_SPAWN_X 24
// [RAM]
#define RAM_WIDTH 16
#define RAM_HEIGHT_GAP 40
#define NUM_RAM 1
// [SPEED]
#define SPEED_RAM 4
#define SPEED_FLOPPY 2
#define TIME_FLOPPYDISK_GAME 5
#define MIN_THRESHOLD_LUX 30
/******************************************************************************
* Typedefs
*******************************************************************************/
// [STRUCT]
typedef struct FloppyDisk {
    int x;
    int y;
} FloppyDisk;
/******************************************************************************
* Function Prototypes
*******************************************************************************/
// [FUNCTIONS]
// init functions
void initFloppyDisk();  // initializes floppy spawn point and game score
// moving/updating functions
void moveUpFloppyDisk(FloppyDisk* floppyDisk); // Decrements Y coordinate of the floppy disk
void moveDownFloppyDisk(FloppyDisk* floppyDisk); // Increments Y coordinate of the floppy disk
void moveRam(int* currentPosition, int* portionSize); // Increments currentPosition of the ram and generates random height for the next Ram. Delete the Ram that has already gone through.
// draw/clear functions
void drawFloppyDiskBackground(); // Draws the floppy disk background
void drawFloppyDisk(int x, int y); // Draws a single snake body cell
void drawRam(int* currentPosition, int* portionSize); // Draw all the rams that are contained in the list
void clearFloppyDisk(int lastX, int LastY, int up, int down); // Eraser only few pixel of the floppy disk depending on SPEED_FLOPPY
void clearRam(int* currentPosition, int* portionSize); // Eraser only few pixel of the ram depending on SPEED_FLOPPY
// collision functions
bool checkBorderCollisionF(int bottom, int top, int min, int max); // Given bottom and top coordinates in Y axis, check if it collides with min and max
bool checkRamCollisionF(FloppyDisk* floppyDisk,int* currentPosition, int* portionSize); // check collision between RAM and Floppy

// run function
void runFloppyDisk();   // run the FloppyDisk game

#endif /* CODE_GAMES_FLOPPYDISK_H_ */

/*** End of File **************************************************************/
