/*******************************************************************************
* Title                 :   RHINO RUNNER
* Filename              :   rhinoRunner.c
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file rhinoRunner.c
 *
 * @brief This module runs the rhino runner game.
 *        The game is inspired by the google chrome game Dino "T-Rex Runner".
 *        The player has to avoid the obstacles (cactus and birds).
 *        The game is over when the player collides with an obstacle.
 *        The player can jump by pressing the button A on the joystick.
 *        When the button is released the rhino starts falling.
 *        
 *      
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "rhinoRunner.h"
#include "Code/Images/rhinoImages.h"

/******************************************************************************
* [ FUNCTIONS DEFINITIONS ]
*******************************************************************************/
/*!
 * @brief This Function runs the rhino runner game.
 *               
 *
 * @param[in] none
 * 
 * 
 * @return none --> void
 */
void runRhino() {
    showInitialTitle(imagetitleRhino);
    drawRhinoBackground();
    showTutorial(imageTutorialRhino, false);
    drawRhinoBackground();
    selectAnimation = 0;
    Rhino rhino;
    uint8_t counterRhino;
    Obstacle obstacle1;
    Obstacle obstacle2;
    initRhino(&rhino, &counterRhino);
    drawRhino(rhino);
    drawScoreText();
    drawScore(score);
    initObstacle(&obstacle1, 0);
    initObstacle(&obstacle2, 80);
    consumeButtonA(); // last reset before the games starts

    while(!gameOver){
        updateRhino(&rhino, &counterRhino);
        clearRhino(rhino);
        drawRhino(rhino);

        if (!checkIfObstacleEnds(obstacle1)){
            updateObstacle(&obstacle1);
            drawObstacle(obstacle1);
            clearObstacle(obstacle1);
        }
        if (!checkIfObstacleEnds(obstacle2)){
            updateObstacle(&obstacle2);
            drawObstacle(obstacle2);
            clearObstacle(obstacle2);
        }

        if (checkRhinoCollision(rhino, obstacle1) || checkRhinoCollision(rhino, obstacle2)){
            gameOver = true;
        }
        if (checkIfObstacleEnds(obstacle1) && obstacle2.x < 128 - 80){
            initObstacle(&obstacle1, 0);
            drawScore(++score);
        }
        if (checkIfObstacleEnds(obstacle2) && obstacle1.x < 128 - 80){
            initObstacle(&obstacle2, 0);
            drawScore(++score);
        }
        wait(20);
    }
}

/*!
 * @brief Initializes all the useful variables.             
 *
 * 
 * @param[in] rhinoPtr  Pointer to the rhino struct.
 * @param[in] counterRhinoPtr  Pointer to the counterRhino variable.
 * 
 * 
 * @return none --> void
 */
void initRhino(Rhino* rhinoPtr, uint8_t* counterRhinoPtr) {
    *counterRhinoPtr = 0;
    rhinoPtr->x = CELL_LARGE;
    rhinoPtr->y = MAX_HEIGHT - RHINO_Y_SIZE;
    rhinoPtr->action = NONE;
}


/*!
 * @brief Initializes initializes an obstacle.
 *        The obstacle can be a cactus or a bird.
 *        The type of the obstacle is chosen randomly.            
 *
 * 
 * @param[in] obstaclePtr  Pointer to the obstacle struct.
 * @param[in] distance  Distance between the obstacle and the previous one.
 * 
 * 
 * @return none --> void
 */
void initObstacle(Obstacle* obstaclePtr, uint8_t distance) {
    if (random(0, 2) == 2){
        obstaclePtr->type = BIRD;
        obstaclePtr->x = MAX_WIDTH - BIRD_X_SIZE + 1 + distance;
        obstaclePtr->y = MAX_HEIGHT - BIRD_HEIGHT - BIRD_Y_SIZE;
    } else{
        obstaclePtr->type = CACTUS;
        obstaclePtr->x = MAX_WIDTH - CACTUS_X_SIZE + 1 + distance;
        obstaclePtr->y = MAX_HEIGHT - CACTUS_Y_SIZE;
    }
}

/*!
 * @brief The function draws the rhino background.
 *
 *               
 * @param[in] none
 * 
 *
 * @return none --> void
 */
void drawRhinoBackground() {
    Graphics_drawImage(&g_sContext, &imageRinoBackground, 0, CELL_LARGE);
}

/*!
 * @brief This function draws the background of the game.
 *
 *               
 * @param[in] rhino  The rhino struct.
 * 
 *
 * @return none --> void
 */
void drawRhino(Rhino rhino) {
    Graphics_drawImage(&g_sContext, &imageRino, rhino.x, rhino.y);
    if (selectAnimation == 1){
        imageRino.pPixel = pixelRino2;
        selectAnimation = 0;
    } else{
        imageRino.pPixel = pixelRino;
        selectAnimation++;
    }
}

/*!
 * @brief The function clears the rhino.
 *        The rhino can be in 3 different states:
 *          - NONE: the rhino is falling
 *          - GOING_UP: the rhino is jumping
 *          - GOING_DOWN: the rhino is falling after the jump
 *          Only the part of the rhino that is moving is cleared.
 *               
 * @param[in] rhino  The rhino struct.
 * 
 *
 * @return none --> void
 */
void clearRhino(Rhino rhino) {
    if (rhino.action == NONE){
        drawRect(rhino.x, rhino.x + RHINO_X_SIZE - 1, rhino.y - 1, rhino.y - GAME_SPEED, WHITE);
    }else if (rhino.action == GOING_UP){
        drawRect(rhino.x, rhino.x + RHINO_X_SIZE - 1, rhino.y + RHINO_Y_SIZE, rhino.y + RHINO_Y_SIZE  + GAME_SPEED - 1, WHITE);
    }else if (rhino.action == GOING_DOWN){
        drawRect(rhino.x, rhino.x + RHINO_X_SIZE - 1, rhino.y + 1, rhino.y - GAME_SPEED, WHITE);
    }
}

/*!
 * @brief The function updates rhino position logically.
 *        The rhino can be in 3 different states:
 *         - NONE: the rhino is falling
 *         - GOING_UP: the rhino is jumping  
 *         - GOING_DOWN: the rhino is falling after the jump
 *       The function updates the rhino position according to the state.
 *             
 * 
 * @param[in] rhinoPtr  Pointer to the rhino struct.
 * @param[in] counterRhinoPtr  Pointer to the counterRhino variable.
 * 
 * 
 * @return none --> void
 */
void updateRhino(Rhino* rhinoPtr, uint8_t* counterRhinoPtr){
    if (rhinoPtr->action == NONE && buttonA == 1){
        rhinoPtr->action = GOING_UP;
    }
    if (rhinoPtr->action == GOING_UP){
        rhinoPtr->y -= GAME_SPEED;
        if (++(*counterRhinoPtr) == JUMP_COUNTER){
            rhinoPtr->action = GOING_DOWN;
            consumeButtonA(); // resets the buttonA
        }
    }
    if (rhinoPtr->action == GOING_DOWN){
        rhinoPtr->y += GAME_SPEED;
        if (--(*counterRhinoPtr) == 0){
            rhinoPtr->action = NONE;
        }
    }
}

/*!
 * @brief The function draws the obstacle.
 *        The obstacle can be a cactus or a bird.
 *
 * 
 * @param[in] obstacle  The obstacle struct.
 * 
 * 
 * @return none --> void
 */
void drawObstacle(Obstacle obstacle) {
    if(obstacle.type == CACTUS){
        Graphics_drawImage(&g_sContext, &imageCactus, obstacle.x, obstacle.y);
    }else{
        Graphics_drawImage(&g_sContext, &imageBird, obstacle.x, obstacle.y);
    }
}

/*!
 * @brief The function clears the obstacle.     
 *
 * 
 * @param[in] obstacle  The obstacle struct.
 * 
 * 
 * @return none --> void
 */
void clearObstacle(Obstacle obstacle) {
    if (checkIfObstacleEnds(obstacle)){
        if(obstacle.type == CACTUS){
            drawRect(0, CACTUS_X_SIZE, MAX_HEIGHT-CACTUS_Y_SIZE, MAX_HEIGHT-1, WHITE);
        }else{
            drawRect(0, BIRD_X_SIZE, MAX_HEIGHT - BIRD_HEIGHT - BIRD_Y_SIZE, MAX_HEIGHT - BIRD_HEIGHT - 1, WHITE);
        }
    }else{
        if(obstacle.type == CACTUS){
            drawRect(obstacle.x + CACTUS_X_SIZE, obstacle.x + CACTUS_X_SIZE + GAME_SPEED - 1, MAX_HEIGHT-CACTUS_Y_SIZE, MAX_HEIGHT-1, WHITE);
            //Graphics_drawStringCentered(&g_sContext, (int8_t *) "score: ", 7, 64, 20, TRANSPARENT_TEXT);
            //printf("drawRect cactus (Xmax-Xmin): %d \n",(obstacle.x + CACTUS_X_SIZE + GAME_SPEED - 1) - (obstacle.x + CACTUS_X_SIZE));
        }else{
            drawRect(obstacle.x + BIRD_X_SIZE, obstacle.x + BIRD_X_SIZE + GAME_SPEED - 1, MAX_HEIGHT - BIRD_HEIGHT - BIRD_Y_SIZE, MAX_HEIGHT - BIRD_HEIGHT - 1, WHITE);
            //printf("drawRect bird (Xmax-Xmin): %d \n",( obstacle.x + BIRD_X_SIZE + GAME_SPEED - 1) - (obstacle.x + BIRD_X_SIZE));
        }
    }
}

/*!
 * @brief The function checks if the obstacle is out of the screen.
 *
 * 
 * @param[in] obstacle  The obstacle struct.
 * 
 * 
 * @return true if the obstacle is out of the screen, false otherwise.
 */
bool checkIfObstacleEnds(Obstacle obstacle) {
    if (obstacle.x <= 0 - CACTUS_X_SIZE  && obstacle.type == CACTUS){
        return true;
    }else if (obstacle.x <= 0 - BIRD_X_SIZE && obstacle.type == BIRD){
        return true;
    }
    return false;
}

/*!
 * @brief The function checks if the rhino collides vertically with an obstacle.
 *        The function checks if the rhino collides with the obstacle in the y axis.
 *             
 * 
 * @param[in] rhino  The rhino struct.
 * @param[in] obstacle  The obstacle struct.
 * 
 * 
 * @return true if the rhino collides with the obstacle, false otherwise.
 */
bool checkYCollision(Rhino rhino, Obstacle obstacle) {
    if (obstacle.type == CACTUS){
        if(rhino.y + RHINO_Y_SIZE >= obstacle.y){
            return true;
        }
    }else if(rhino.y <= obstacle.y + BIRD_HEIGHT){
        return true;
    }
    return false;
}

/*!
 * @brief The function checks if the rhino collides with the obstacle.
 *        The obstacle can be a cactus or a bird.
 *        The function checks if the rhino collides with the obstacle in the x axis.
 *        If the rhino collides in the x axis, the function checks if the rhino collides in the y axis.
 *        The function returns true if the rhino collides with the obstacle, false otherwise.
 *
 * 
 * @param[in] rhino  The rhino struct.
 * @param[in] obstacle  The obstacle struct.
 * 
 * 
 * @return true if the rhino collides with the obstacle, false otherwise.
 */
bool checkRhinoCollision(Rhino rhino, Obstacle obstacle) {
    if (rhino.x <= obstacle.x && obstacle.x <= rhino.x + RHINO_X_SIZE){
        if(checkYCollision(rhino, obstacle)){
            return true;
        }
    }
    return false;
}

/*!
 * @brief The function updates the obstacle position.
 *        The function updates the obstacle position according to the GAME_SPEED.
 *        The obstacle moves to the left.
 *             
 * 
 * @param[in] obstaclePtr  Pointer to the obstacle struct.
 * 
 * 
 * @return none --> void
 */
void updateObstacle(Obstacle* obstaclePtr) {
    obstaclePtr->x -= GAME_SPEED;
}

/*** End of File **************************************************************/
