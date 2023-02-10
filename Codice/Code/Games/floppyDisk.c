/*******************************************************************************
* Title                 :   FLOPPY DISK
* Filename              :   floppyDisk.c
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file floppyDisk.c
 *
 * @brief This module runs the floppy disk game.
 *        The game is inspired from the flappy bird game.
 *        The game is played by moving the floppy disk up and down to avoid the RAM sticks.
 *        The game ends when the floppy disk collides with the RAM sticks or the border.
 *        The score is incremented by 1 every time the floppy disk passes through a RAM stick.
 *        The score is displayed on the screen.
 *        To move the floppy disk, you have to use your hand/finger to cover the light sensor.
 *        The light sensor is located on the top of the board.
 *        The light sensor is used to detect the light intensity.
 *        The light intensity is used to determine if the floppy disk should move up or down.
 *        The light intensity is measured in lux; by default, the light intensity is set to 30 lux.
 *          - If the light intensity is less than 30 lux, the floppy disk will move up.
 *          - If the light intensity is greater than 30 lux, the floppy disk will move down.
 *      The game is played on a 128x136 screen. 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "floppyDisk.h"
#include "Code/Images/floppyDiskImages.h"
#include "Code/Utilities/linkedList.h"

/******************************************************************************
* [ FUNCTIONS DEFINITIONS ]
*******************************************************************************/
/*!
 * @brief This Function runs the floppy disk game and all the functions needed to play the game.
 *               
 *
 * @param[in] none
 * 
 * @var[global] score  Variable for storing the score of the game.
 * @var[global] gameOver  Variable for storing the state of the game.
 * 
 * @var[local] floppyDisk  Location of the floppy disk in coordinates.
 * @var[local] portionSize  Width of the portion depending how many NUM_RAM sticks there are
 * @var[local] lux  Variable for storing lux value returned from OPT3001
 * @var[local] currentPosition  Variable for storing the current position of the ram.
 *
 * 
 * @return none --> void
 */
void runFloppyDisk() {
    showInitialTitle(imageFloppyDiskTitle);
    drawFloppyDiskBackground();
    showTutorialBig(imageTutorialFloppyDisk);
    uint32_t lux = 0.0;
    FloppyDisk floppyDisk;
    uint8_t portionSize = 0;
    uint8_t currentPosition = 0;
    initFloppyDisk(&floppyDisk, &portionSize);
    drawFloppyDiskBackground();
    drawFloppyDisk(floppyDisk.x, floppyDisk.y);
    drawScoreText();
    drawScore(score);
    while(!gameOver){
        lux = OPT3001_getLux();
        //printf("%d \n", lux);
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

/*!
 * @brief Initializes all the useful Local and global variables.
 *        Initializes the linked list to store all the RAM sticks.
 *        Initializes the score to 0.
 *        Initializes the game over state to false.
 *        The floppy disk is initialized at the center of the screen.
 *        The RAM sticks are initialized at the right side of the screen.       
 *
 * 
 * @param[in] floppyDisk Location of the floppy disk in coordinates.
 * @param[in] portionSize Width of the portion depending how many NUM_RAM sticks there are
 * 
 * @var[global] score  Variable for storing the score of the game.
 * @var[global] gameOver  Variable for storing the state of the game.
 * @var[global] head  Pointer to the head of the linked list.
 * 
 * @var[local] i  Variable for storing the current index of the RAM sticks.
 * 
 * @return none --> void
 */
void initFloppyDisk(FloppyDisk* floppyDisk, uint8_t* portionSize) {
    head = NULL; 
    score = 0;
    gameOver = false;
    *portionSize = (MAX_X_SIZE/ NUM_RAM);
    floppyDisk->x = FLOPPY_SPAWN_X;
    floppyDisk->y = (MAX_Y_SIZE/2)-FLOPPY_SPAWN_X;
    uint8_t i;
    for(i=0; i < NUM_RAM; i++){
        insert_end(0);
    }
}

/*!
 * @brief This Function moves the floppy disk up. 
 *        Decrements Y coordinate of the floppy disk by SPEED_FLOPPY.
 *        Clears the floppy disk from the previous position.
 *        Draws the floppy disk at the new position.
 *               
 *
 * @param[in] floppyDisk Location of the floppy disk in coordinates.
 * 
 * @var[global] none
 * 
 * @var[local] none
 *
 * @return none --> void
 */
void moveUpFloppyDisk(FloppyDisk* floppyDisk){
    clearFloppyDisk(floppyDisk->x, floppyDisk->y, FLOPPY_HEIGHT - SPEED_FLOPPY, 0);
    floppyDisk->y = (floppyDisk->y - SPEED_FLOPPY);
}

/*!
 * @brief This Function moves the floppy disk down. 
 *        Increments Y coordinate of the floppy disk by SPEED_FLOPPY.
 *        Clears the floppy disk from the previous position.
 *        Draws the floppy disk at the new position.
 *               
 *
 * @param[in] floppyDisk Location of the floppy disk in coordinates.
 * 
 * @var[global] none
 * 
 * @var[local] none
 *
 * @return none --> void
 */
void moveDownFloppyDisk(FloppyDisk* floppyDisk){
    clearFloppyDisk(floppyDisk->x, floppyDisk->y, 0, - FLOPPY_HEIGHT + SPEED_FLOPPY);
    floppyDisk->y = (floppyDisk->y + SPEED_FLOPPY);
}

/*!
 * @brief This Function moves the Ram sticks.
 *        Increments the current position of the RAM sticks by the portion size.
 *        Deletes the RAM stick at the beginning of the linked list.
 *        Inserts a new RAM stick at the end of the linked list with a random height.
 *        The height of the RAM stick is between 10 and the maximum height of the screen minus the border. 
 *               
 *
 * @param[in] portionSize Width of the portion depending how many NUM_RAM sticks there are
 * @param[in] currentPosition  Variable for storing the current position of the ram.
 * 
 * @var[global] none
 * 
 * @var[local] none
 *
 * @return none --> void
 */
void moveRam(uint8_t* currentPosition, uint8_t* portionSize){
    // this is useful if there are at least two or more portion
    if((*currentPosition) > (*portionSize) + RAM_WIDTH){
        (*currentPosition) -= (*portionSize);
        delete_begin();
        uint8_t height = random(10, MAX_Y_SIZE - (2*BORDER) - RAM_HEIGHT_GAP);
        //if(height <= 10) height = 0;
        insert_end(height);
    }
    (*currentPosition) += SPEED_RAM;
}

/*!
 * @brief This function draws the floppy disk background
 *               
 *
 * @param[in] none
 * 
 * @var[global] none
 * 
 * @var[local] none
 *
 * @return none --> void
 */
void drawFloppyDiskBackground(){
    Graphics_drawImage(&g_sContext, &imageFloppyDiskBackground, 0, BORDER);
}

/*!
 * @brief This function draws the floppy disk
 *               
 *
 * @param[in] x X coordinate of the floppy disk
 * @param[in] y Y coordinate of the floppy disk
 * 
 * @var[global] none
 * 
 * @var[local] none
 *
 * @return none --> void
 */
void drawFloppyDisk(uint8_t x, uint8_t y) {
    Graphics_drawImage(&g_sContext, &imageFloppyDisk, x , y );
}

/*!
 * @brief This function draw all the rams that are contained in the liked list. 
 *               
 *
 * @param[in] currentPosition  Variable for storing the current position of the ram.
 * @param[in] portionSize Width of the portion depending how many NUM_RAM sticks there are
 * 
 * @var[global] none
 * 
 * @var[local] currentPortion  Variable for storing the current index of the RAM sticks.
 * @var[local] ptr  Pointer to the current node of the linked list.
 *
 * @return none --> void
 */
void drawRam(uint8_t* currentPosition, uint8_t* portionSize) {
    uint8_t currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL) {
        if(ptr->data != 0){
            //bottom ram
            imageRam.ySize = ptr->data;
            Graphics_drawImage(&g_sContext, &imageRam, currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize),
                               MAX_Y_SIZE - ptr->data -BORDER);
            //top ram
            imageRam.ySize = (MAX_Y_SIZE - 2 * BORDER) - ptr->data - RAM_HEIGHT_GAP;
            Graphics_drawImage(&g_sContext, &imageRam, currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize), BORDER);
        }
        ptr = ptr->next;
        currentPortion++;
    }
    free(ptr);
}

/*!
 * @brief This function clears the floppy disk
 *        Eraser only few pixel of the floppy disk depending on SPEED_FLOPPY  
 *      
 *
 * @param[in] lastX X coordinate of the floppy disk
 * @param[in] lastY Y coordinate of the floppy disk
 * @param[in] up if up = 0, eraser the floppy disk from the top
 * @param[in] down if down = 0, eraser the floppy disk from the bottom
 * 
 * @var[global] none
 * 
 * @var[local] none
 *
 * @return none --> void
 */
void clearFloppyDisk(uint8_t lastX, uint8_t LastY, int8_t up, int8_t down){
    drawRect(lastX,
             lastX + FLOPPY_WIDTH ,
             LastY + up,
             LastY + FLOPPY_HEIGHT + down,
             LIGTH_BLUE);
}

/*!
 * @brief This function clears the ram sticks
 *        Eraser only few pixel of the ram sticks depending on SPEED_RAM  
 *      
 *
 * @param[in] currentPosition  Variable for storing the current position of the ram.
 * @param[in] portionSize Width of the portion depending how many NUM_RAM sticks there are
 * 
 * @var[global] none
 * 
 * @var[local] currentPortion  Variable for storing the current index of the RAM sticks.
 * @var[local] ptr  Pointer to the current node of the linked list.
 *
 * @return none --> void
 */
void clearRam(uint8_t* currentPosition, uint8_t* portionSize) {
    uint8_t currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL) {
        if(ptr->data != 0){
            //bottom ram
            drawRect(currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) + 1 + RAM_WIDTH - SPEED_RAM,
                     currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) + BORDER + 3,
                     MAX_Y_SIZE -  ptr->data -BORDER, MAX_Y_SIZE - BORDER - 1, LIGTH_BLUE);
            //bottom top
            drawRect(currentPortion * (*portionSize)  - (*currentPosition)+ (*portionSize) + 1 +  RAM_WIDTH - SPEED_RAM,
                     currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) + BORDER + 3,
                     BORDER, (MAX_Y_SIZE - 2 * BORDER) - ptr->data - RAM_HEIGHT_GAP + BORDER , //-1, penso che era l'origine del bug
                     LIGTH_BLUE);
        }
    ptr = ptr->next;
    currentPortion++;
    }
    free(ptr);
}

/*!
 * @brief This function checks border collision of the floppy disk.
 *        Given bottom and top coordinates in Y axis, check if it collides with min and max
 *               
 *
 * @param[in] bottom Bottom coordinate of the floppy disk
 * @param[in] top Top coordinate of the floppy disk
 * @param[in] min Min coordinate of the border
 * @param[in] max Max coordinate of the border
 * 
 * @var[global] none
 * 
 * @var[local] none
 *
 * @return true if the floppy disk collides with the border.
 * @return false if the floppy disk doesn't collide with the border.
 */
bool checkBorderCollisionF(uint8_t bottom, uint8_t top, uint8_t min, uint8_t max) {
    if (bottom >= min  || top <= max ) {
        return true;
    } else{
        return false;
    }
}

/*!
 * @brief This function checks if the floppy disk is inside the ram sticks.
 *        Given the floppy disk, the current position of the ram and the portion size, check if the floppy disk is inside the ram sticks.         
 *               
 *
 * @param[in] floppyDisk Pointer to the floppy disk
 * @param[in] currentPosition  Variable for storing the current position of the ram.
 * @param[in] portionSize Width of the portion depending how many NUM_RAM sticks there are
 * 
 * @var[global] none
 * 
 * @var[local] currentPortion  Variable for storing the current index of the RAM sticks.
 * @var[local] ptr  Pointer to the current node of the linked list.
 *
 * @return true if the floppy disk is inside the ram sticks.
 * @return false if the floppy disk is not inside the ram sticks.
 */
bool checkRamCollisionF(FloppyDisk* floppyDisk, uint8_t* currentPosition, uint8_t* portionSize) {
    bool temp=false;
    uint8_t currentPortion= 0;
    struct node* ptr = head;
    while(ptr!=NULL && !temp) {
        if(ptr->data != 0) {
            if (FLOPPY_SPAWN_X + FLOPPY_WIDTH >= currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) &&
                currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize) >= CELL_SMALL ) {
                // When the Floppy Disk is inside the RAM area it also checks for border collision
                temp = checkBorderCollisionF(floppyDisk->y + FLOPPY_HEIGHT, floppyDisk->y ,
                                             MAX_Y_SIZE - BORDER - ptr->data , MAX_Y_SIZE - BORDER - ptr->data - RAM_HEIGHT_GAP);
                // if the FloppyDisk has exceeded the RAM, the score increases
                if(currentPortion * (*portionSize)  - (*currentPosition) + (*portionSize)  == FLOPPY_SPAWN_X - RAM_WIDTH) {
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

/*** end of file ***/
