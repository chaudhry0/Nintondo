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
#define NUM_RAM 2
// [SPEED]
#define SPEED_RAM 2
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
void runFloppyDisk();
void initFloppyDisk();
void moveUpFloppyDisk();
void moveDownFloppyDisk();
void moveRam();
void drawFloppyDiskBackground();
void drawFloppyDisk(int x, int y);
void drawRam();
void drawScoreF(int score);
void clearFloppyDisk(int lastX, int LastY, int up, int down);
void clearRam();
bool checkBorderCollisionF(int bottom, int top, int min, int max);
bool checkRamCollisionF();

#endif /* CODE_GAMES_FLOPPYDISK_H_ */
