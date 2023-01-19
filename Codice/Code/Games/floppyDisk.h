#ifndef CODE_GAMES_FLOPPYDISK_H_
#define CODE_GAMES_FLOPPYDISK_H_

#include "Code/Utilities/init.h"

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

typedef struct FloppyDisk {
    int x;
    int y;
} FloppyDisk;
FloppyDisk floppyDisk; // coordinates of floppy

// [GLOBAL VARIABLES]
float lux; //Variable for storing lux value returned from OPT3001
int portionSize; //width of the portion depending how many NUM_RAM sticks there are
int currentPosition; // X coordinate of ram

// [FUNCTIONS]
// init functions
void initFloppyDisk();  // initializes floppy spawn point and game score
// moving/updating functions
void moveUpFloppyDisk();    // update floppy position up
void moveDownFloppyDisk();  // update floppy position up
void moveRam(); // update position, removes inactive and create new ram banks
// bool functions
bool checkBorderCollisionF(int bottom, int top, int min, int max);  // check top and bottom border collision
bool checkRamCollisionF();  // check collision between ram banks and floppy
// draw functions
void drawFloppyDiskBackground();    // draw floppy disk background
void drawFloppyDisk(int x, int y);  // draw floppy disk
void drawRam(); // draw ram banks
void clearFloppyDisk(int lastX, int LastY, int up, int down);   // clear floppy of the pixels it moved
void clearRam();    // clear ram banks of the pixels they moved

// run function
void runFloppyDisk();   // run the FloppyDisk game

#endif /* CODE_GAMES_FLOPPYDISK_H_ */
