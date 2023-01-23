#include "floppyDisk.h"
#include "Code/Images/floppyDiskImages.h"
#include "Code/Utilities/linkedList.h"

// Runs the floppy disk game
void runFloppyDisk() {
     initFloppyDisk();
     drawFloppyDiskBackground();
     drawFloppyDisk(floppyDisk.x, floppyDisk.y);
     drawScoreText();
     drawScore(score);
     while(!gameOver){
         lux = OPT3001_getLux();
         if(lux < MIN_THRESHOLD_LUX ) {
              moveUpFloppyDisk();
         }else {
             moveDownFloppyDisk();
         }
         drawFloppyDisk(floppyDisk.x, floppyDisk.y);
         clearRam();
         moveRam();
         wait(TIME_FLOPPYDISK_GAME);
         drawRam();
         gameOver = (checkBorderCollisionF(floppyDisk.y + FLOPPY_HEIGHT, floppyDisk.y ,  MAX_Y_SIZE - BORDER, BORDER) || checkRamCollisionF());
     }
}

// Initializes all the useful GLOBAL variables
void initFloppyDisk() {
    head = NULL;
    score = 0;
    currentPosition = 0;
    gameOver = false;
    floppyDisk.x = FLOPPY_SPAWN_X;
    floppyDisk.y = (MAX_Y_SIZE/2)-FLOPPY_SPAWN_X;
    portionSize = (MAX_X_SIZE/ NUM_RAM) ;
    int i;
    for(i=0; i < NUM_RAM; i++){
        insert_end(0);
    }
}

// Decrements Y coordinate of the floppy disk
void moveUpFloppyDisk(){
    clearFloppyDisk(floppyDisk.x, floppyDisk.y, FLOPPY_HEIGHT - SPEED_FLOPPY, 0);
    floppyDisk.y = (floppyDisk.y - SPEED_FLOPPY);
}

// Increments Y coordinate of the floppy disk
void moveDownFloppyDisk(){
    clearFloppyDisk(floppyDisk.x, floppyDisk.y, 0, - FLOPPY_HEIGHT + SPEED_FLOPPY);
    floppyDisk.y = (floppyDisk.y + SPEED_FLOPPY);
}

// Increments currentPosition of the ram and generates random height for the next Ram. Delete the Ram that has already gone through.
void moveRam(){
    if(currentPosition > portionSize + RAM_WIDTH){
        currentPosition -= portionSize;
        delete_begin();
        int height = random(10, MAX_Y_SIZE - (2*BORDER) - RAM_HEIGHT_GAP);
        //if(height <= 10) height = 0;
        insert_end(height);
    }
    currentPosition += SPEED_RAM;
}

// Draws the floppy disk background
void drawFloppyDiskBackground(){
    Graphics_drawImage(&g_sContext, &imageFloppyDiskBackground, 0, BORDER);
}

// Draws a single snake body cell
void drawFloppyDisk(int x, int y) {
    Graphics_drawImage(&g_sContext, &imageFloppyDisk, x , y );
}

// Draw all the rams that are contained in the list
void drawRam() {
    int currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL) {
        if(ptr->data != 0){
            imageRam.ySize = ptr->data;
            Graphics_drawImage(&g_sContext, &imageRam, currentPortion * portionSize  - currentPosition + portionSize, MAX_Y_SIZE - ptr->data -BORDER);
            imageRam.ySize = (MAX_Y_SIZE - 2*BORDER) - ptr->data - RAM_HEIGHT_GAP ;
            Graphics_drawImage(&g_sContext, &imageRam, currentPortion * portionSize  - currentPosition + portionSize, BORDER);
        }
        ptr = ptr->next;
        currentPortion++;
    }
    free(ptr);
}

// Eraser only few pixel of the floppy disk depending on SPEED_FLOPPY
void clearFloppyDisk(int lastX, int LastY, int up, int down){
    drawRect(lastX,
             lastX + FLOPPY_WIDTH ,
             LastY + up,
             LastY + FLOPPY_HEIGHT + down,
             LIGTH_BLUE);// ex colore 0x4dafc6
}

// Eraser only few pixel of the ram depending on SPEED_FLOPPY
void clearRam() {
    int currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL) {
        if(ptr->data != 0){
            drawRect(currentPortion * portionSize  - currentPosition + portionSize + 1 + RAM_WIDTH - SPEED_RAM,
                     currentPortion * portionSize  - currentPosition + portionSize + BORDER + 3,
                     MAX_Y_SIZE -  ptr->data - BORDER ,
                     MAX_Y_SIZE - BORDER - 1,
                     LIGTH_BLUE);// ex colore 0x4dafc6
            drawRect(currentPortion * portionSize  - currentPosition+ portionSize + 1 +  RAM_WIDTH - SPEED_RAM,
                     currentPortion * portionSize  - currentPosition + portionSize + BORDER + 3,
                     BORDER,
                     (MAX_Y_SIZE - 2*BORDER) - ptr->data - RAM_HEIGHT_GAP + BORDER, //-1, penso che era l'origine del bug
                     LIGTH_BLUE);// ex colore 0x4dafc6
        }
    ptr = ptr->next;
    currentPortion++;
    }
    free(ptr);
}

// Given bottom and top coordinates in Y axis, check if it collides with min and max
bool checkBorderCollisionF(int bottom, int top, int min, int max) {
    if (bottom >= min  || top <= max ) {
        return true;
    } else{
        return false;
    }
}

// check collision between RAM and Floppy
bool checkRamCollisionF() {
    bool temp=false;
    int currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL && !temp) {
        if(ptr->data != 0) {
            if (FLOPPY_SPAWN_X + FLOPPY_WIDTH >= currentPortion * portionSize  - currentPosition + portionSize    && currentPortion * portionSize  - currentPosition + portionSize >= 8 ) {
                temp = checkBorderCollisionF(floppyDisk.y + FLOPPY_HEIGHT, floppyDisk.y , MAX_Y_SIZE - BORDER - ptr->data , MAX_Y_SIZE - BORDER - ptr->data - RAM_HEIGHT_GAP);
                if(currentPortion * portionSize  - currentPosition + portionSize  == FLOPPY_SPAWN_X - RAM_WIDTH) {
                    drawScore(++score);
                }
            }
        }
        ptr = ptr->next;
        currentPortion++;
    }
    free(ptr);
    return temp;
}



