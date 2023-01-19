#include "rhinoRunner.h"
#include "Code/Images/rhinoImages.h"

void runRhino() {
    showInitialTitle(imagetitleRhino);
    prova = 0;
    Rhino rhino;
    int counterRhino;
    Obstacle obstacle1;
    Obstacle obstacle2;
    initRhino(&rhino, &counterRhino);
    drawRhinoBackground();
    drawRhino(rhino);
    drawScoreText();
    drawScore(score);
    initObstacle(&obstacle1, 0);
    initObstacle(&obstacle2, 80);

    while(!gameOver){
        updateRhino(&rhino, &counterRhino);
        clearRhino(rhino);
        drawRhino(rhino);
        updateObstacle(&obstacle1);
        updateObstacle(&obstacle2);
        clearObstacle(obstacle1);
        clearObstacle(obstacle2);
        drawObstacle(obstacle1);
        drawObstacle(obstacle2);

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

void initRhino(Rhino* rhinoPtr, int* counterRhinoPtr) {
    *counterRhinoPtr = 0;
    rhinoPtr->x = CELL_SIZE_LARGE;
    rhinoPtr->y = MAX_HEIGHT - RHINO_Y_SIZE;
    rhinoPtr->action = NONE;
}



void initObstacle(Obstacle* obstaclePtr, int distance) {
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

void drawRhinoBackground() {
    Graphics_drawImage(&g_sContext, &imageRinoBackground, 0, CELL_SIZE_LARGE);
}

void drawRhino(Rhino rhino) {
    Graphics_drawImage(&g_sContext, &imageRino, rhino.x, rhino.y);
    if (prova == 1){
        imageRino.pPixel = pixelRino2;
        prova = 0;
    } else{
        imageRino.pPixel = pixelRino;
        prova++;
    }
}

void clearRhino(Rhino rhino) {
    if (rhino.action == NONE){
        drawRect(rhino.x, rhino.x + RHINO_X_SIZE - 1, rhino.y - 1, rhino.y - GAME_SPEED, WHITE);
    }else if (rhino.action == GOING_UP){
        drawRect(rhino.x, rhino.x + RHINO_X_SIZE - 1, rhino.y + RHINO_Y_SIZE, rhino.y + RHINO_Y_SIZE  + GAME_SPEED - 1, WHITE);
    }else if (rhino.action == GOING_DOWN){
        drawRect(rhino.x, rhino.x + RHINO_X_SIZE - 1, rhino.y + 1, rhino.y - GAME_SPEED, WHITE);
    }
}

void updateRhino(Rhino* rhinoPtr, int* counterRhinoPtr){
    if (rhinoPtr->action == NONE && getButtons() == 1){
        rhinoPtr->action = GOING_UP;
    }
    if (rhinoPtr->action == GOING_UP){
        rhinoPtr->y -= GAME_SPEED;
        if (++(*counterRhinoPtr) == JUMP_COUNTER || getButtons() == 0){
            rhinoPtr->action = GOING_DOWN;
        }
    }
    if (rhinoPtr->action == GOING_DOWN){
        rhinoPtr->y += GAME_SPEED;
        if (--(*counterRhinoPtr) == 0){
            rhinoPtr->action = NONE;
        }
    }
}

void drawObstacle(Obstacle obstacle) {
    if(obstacle.type == CACTUS){
        Graphics_drawImage(&g_sContext, &imageCactus, obstacle.x, obstacle.y);
    }else{
        Graphics_drawImage(&g_sContext, &imageBird, obstacle.x, obstacle.y);
    }
}

void clearObstacle(Obstacle obstacle) {
    if(obstacle.type == CACTUS){
        drawRect(obstacle.x + CACTUS_X_SIZE, obstacle.x + CACTUS_X_SIZE + GAME_SPEED - 1, MAX_HEIGHT-CACTUS_Y_SIZE, MAX_HEIGHT-1, WHITE);
    }else{
        drawRect(obstacle.x + BIRD_X_SIZE, obstacle.x + BIRD_X_SIZE + GAME_SPEED - 1, MAX_HEIGHT - BIRD_HEIGHT - BIRD_Y_SIZE, MAX_HEIGHT - BIRD_HEIGHT - 1, WHITE);
    }
}

bool checkIfObstacleEnds(Obstacle obstacle) {
    if (obstacle.x <= 0 - CACTUS_X_SIZE && obstacle.type == CACTUS){
        return true;
    }else if (obstacle.x <= 0 - BIRD_X_SIZE && obstacle.type == BIRD){
        return true;
    }
    return false;
}

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

bool checkRhinoCollision(Rhino rhino, Obstacle obstacle) {
    if (rhino.x <= obstacle.x && obstacle.x <= rhino.x + RHINO_X_SIZE){
        if(checkYCollision(rhino, obstacle)){
            return true;
        }
    }
    return false;
}

void updateObstacle(Obstacle* obstaclePtr) {
    obstaclePtr->x -= GAME_SPEED;
}
