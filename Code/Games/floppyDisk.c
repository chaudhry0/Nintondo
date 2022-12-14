#include "floppyDisk.h"
#include "Code/Images/floppyDiskImages.h"
#include "Code/Utilities/linkedList.h"

void runFloppyDisk() {
     float lux = 0.0; //Variable for storing lux value returned from OPT3001
     FloppyDisk floppyDisk; // coordinates of floppy
     int portionSize = 0; //width of the portion depending how many NUM_RAM sticks there are
     int currentPosition = 0; // X coordinate of ram
     initFloppyDisk(&floppyDisk, &portionSize);
     drawFloppyDiskBackground();
     drawFloppyDisk(floppyDisk.x, floppyDisk.y);
     drawScoreText();
     drawScore(0);
     while(!gameOver){
         lux = OPT3001_getLux();
         if(lux < MIN_THRESHOLD_LUX ) {
              moveUpFloppyDisk(&floppyDisk);
         }else {
             moveDownFloppyDisk(&floppyDisk);
         }
         drawFloppyDisk(floppyDisk.x, floppyDisk.y);
         clearRam(&currentPosition, &portionSize);
         moveRam(&currentPosition, &portionSize);
         wait(TIME_FLOPPYDISK_GAME);
         drawRam(&currentPosition, &portionSize);
         gameOver = (checkBorderCollisionF(floppyDisk.y + FLOPPY_HEIGHT, floppyDisk.y ,  MAX_Y_SIZE - BORDER, BORDER) ||
                     checkRamCollisionF(&floppyDisk, &currentPosition, &portionSize));
     }
}

void initFloppyDisk(FloppyDisk* floppyDisk, int* portionSize) {
    head = NULL; //linkedList to store all RAM sticks
    score = 0;
    gameOver = false;
    *portionSize = (MAX_X_SIZE/ NUM_RAM);
    floppyDisk->x = FLOPPY_SPAWN_X;
    floppyDisk->y = (MAX_Y_SIZE/2)-FLOPPY_SPAWN_X;
    int i;
    for(i=0; i < NUM_RAM; i++){
        insert_end(0);
    }
}

void moveUpFloppyDisk(FloppyDisk* floppyDisk){
    clearFloppyDisk(floppyDisk->x, floppyDisk->y, FLOPPY_HEIGHT - SPEED_FLOPPY, 0);
    floppyDisk->y = (floppyDisk->y - SPEED_FLOPPY);
}

void moveDownFloppyDisk(FloppyDisk* floppyDisk){
    clearFloppyDisk(floppyDisk->x, floppyDisk->y, 0, - FLOPPY_HEIGHT + SPEED_FLOPPY);
    floppyDisk->y = (floppyDisk->y + SPEED_FLOPPY);
}

void moveRam(int* currentPosition, int* portionSize){
    // this is useful if there are at least two or more portion
    if((*currentPosition) > (*portionSize) + RAM_WIDTH){
        (*currentPosition) -= (*portionSize);
        delete_begin();
        int height = random(10, MAX_Y_SIZE - (2*BORDER) - RAM_HEIGHT_GAP);
        //if(height <= 10) height = 0;
        insert_end(height);
    }
    (*currentPosition) += SPEED_RAM;
}

void drawFloppyDiskBackground(){
    Graphics_drawImage(&g_sContext, &imageFloppyDiskBackground, 0, BORDER);
}

void drawFloppyDisk(int x, int y) {
    Graphics_drawImage(&g_sContext, &imageFloppyDisk, x , y );
}

void drawRam(int* currentPosition, int* portionSize) {
    int currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL) {
        if(ptr->data != 0){
            //bottom ram
            imageRam.ySize = ptr->data;
            Graphics_drawImage(&g_sContext, &imageRam, currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize),
                               MAX_Y_SIZE - ptr->data -BORDER);
            //top ram
            imageRam.ySize = (MAX_Y_SIZE - 2*BORDER) - ptr->data - RAM_HEIGHT_GAP;
            Graphics_drawImage(&g_sContext, &imageRam, currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize), BORDER);
        }
        ptr = ptr->next;
        currentPortion++;
    }
    free(ptr);
}

void clearFloppyDisk(int lastX, int LastY, int up, int down){
    drawRect(lastX,
             lastX + FLOPPY_WIDTH ,
             LastY + up,
             LastY + FLOPPY_HEIGHT + down,
             0x4dafc6);
}

void clearRam(int* currentPosition, int* portionSize) {
    int currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL) {
        if(ptr->data != 0){
            //bottom ram
            drawRect(currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) + 1 + RAM_WIDTH - SPEED_RAM,
                     currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) + BORDER + 3,
                     MAX_Y_SIZE -  ptr->data -BORDER , MAX_Y_SIZE - BORDER -1 , 0x4dafc6);
            //bottom top
            drawRect(currentPortion * (*portionSize)  - (*currentPosition)+ (*portionSize) + 1 +  RAM_WIDTH - SPEED_RAM,
                     currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) + BORDER + 3,
                     BORDER, (MAX_Y_SIZE - 2*BORDER) - ptr->data - RAM_HEIGHT_GAP + BORDER - 1, 0x4dafc6);
        }
    ptr = ptr->next;
    currentPortion++;
    }
    free(ptr);
}

bool checkBorderCollisionF(int bottom, int top, int min, int max) {
    if (bottom >= min  || top <= max ) {
        return true;
    } else{
        return false;
    }
}

bool checkRamCollisionF(FloppyDisk* floppyDisk, int* currentPosition, int* portionSize) {
    bool temp=false;
    int currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL && !temp) {
        if(ptr->data != 0) {
            if (FLOPPY_SPAWN_X + FLOPPY_WIDTH >= currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) &&
                currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) >= 8 ) {
                // When the Floppy Disk is inside the RAM area it also checks for border collision
                temp = checkBorderCollisionF(floppyDisk->y + FLOPPY_HEIGHT, floppyDisk->y ,
                                             MAX_Y_SIZE - BORDER - ptr->data , MAX_Y_SIZE - BORDER - ptr->data - RAM_HEIGHT_GAP);
                // if the FloppyDisk has exceeded the RAM, the score increases
                if(currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize)  == FLOPPY_SPAWN_X - RAM_WIDTH) {
                    score++;
                    drawScore(score);
                }
            }
        }
        ptr = ptr->next;
        currentPortion++;
    }
    free(ptr);
    return temp;
}
