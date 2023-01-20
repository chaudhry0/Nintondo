#include "pong.h"
#include "Code/Images/pongImages.h"

void initBall(Ball* ballPtr){
    ballPtr->x = 100;
    ballPtr->y = 70;
    ballPtr->xVel = -2;
    ballPtr->yVel = 0;
}

void drawPongBackground(){
    Graphics_drawImage(&g_sContext, &imagePongBackground, 0, CELL_SIZE_LARGE);
}

void drawPongUser(int userUpperY, int lastUserY){
    Graphics_drawImage(&g_sContext, &imagePongUser, 0, userUpperY);
    if (lastUserY < userUpperY){ // moving down
        drawRect(0, 3, userUpperY - 1, userUpperY -2, GREEN);
    } else if (lastUserY > userUpperY){ // moving down
        drawRect(0, 3, userUpperY + CELL_SIZE_LARGE , userUpperY + CELL_SIZE_LARGE + 1, GREEN);
    }
}

void drawPongEnemy(int enemyUpperY, int lastEnemyY){
    Graphics_drawImage(&g_sContext, &imagePongEnemy, 124, enemyUpperY);
    if (lastEnemyY < enemyUpperY){ // moving down
        drawRect(124, 127, enemyUpperY - 1, enemyUpperY -4, GREEN);
    } else if (lastEnemyY > enemyUpperY){ // moving down
        drawRect(124, 127, enemyUpperY + CELL_SIZE_LARGE , enemyUpperY + CELL_SIZE_LARGE + 3, GREEN);
    }
}

void drawBall(Ball ball){
    drawRect(ball.x - ball.xVel, ball.x - ball.xVel + 3, ball.y - ball.yVel, ball.y - ball.yVel + 3, GREEN);
    Graphics_drawImage(&g_sContext, &imagePongBall, ball.x, ball.y);
}

void moveUser(int* userUpperYPtr, int* lastUserYPtr){
    *lastUserYPtr = *userUpperYPtr;
    switch(direction){
        case 1: // UP
            if (*userUpperYPtr > CELL_SIZE_LARGE){
                *userUpperYPtr -= 2;
            }
            break;
        case 3: // DOWN
            if (*userUpperYPtr < 96){
                *userUpperYPtr += 2;
            }
            break;
        default:
            break;
    }
}

void moveEnemy(int* enemyUpperYPtr, int* lastEnemyYPtr, Ball ball){
    if (random(1, 100) > 28){
        *lastEnemyYPtr = *enemyUpperYPtr;
        if (*enemyUpperYPtr + 7 > ball.y + 1 && *enemyUpperYPtr > CELL_SIZE_LARGE){
            *enemyUpperYPtr -= 4;
        }
        if (*enemyUpperYPtr + CELL_SIZE_LARGE - 1 - 7 < ball.y + 2 && *enemyUpperYPtr + CELL_SIZE_LARGE - 1 < 111){
            *enemyUpperYPtr += 4;
        }
    }
}

void moveBall(Ball* ballPtr){
    ballPtr->x += ballPtr->xVel;
    ballPtr->y += ballPtr->yVel;
}

bool checkUserCollision(int userUpperY, Ball ball){
    int i;
    for (i=0; i<CELL_SIZE_LARGE; i++){
        if (userUpperY + i == ball.y || userUpperY + i == ball.y + 3){
            return true;
        }
    }
    return false;
}

bool checkEnemyCollision(int enemyUpperY, Ball ball){
    int i;
    for (i=0; i<CELL_SIZE_LARGE; i++){
        if (enemyUpperY + i == ball.y || enemyUpperY + i == ball.y + 3){
            return true;
        }
    }
    return false;
}

bool checkPongBorderCollision(Ball ball){
    if (ball.y <= 20 || ball.y + 3 >= 107){
        return true;
    }
    return false;
}

void invertBallXDirection(Ball* ballPtr){
    ballPtr->xVel = - ballPtr->xVel;
}

void invertBallYDirection(Ball* ballPtr){
    ballPtr->yVel = - ballPtr->yVel;
}

void updateBallY(Ball* ballPtr){
    ballPtr->yVel = random(-3, 3);
}

void runPong(){
    showInitialTitle(imagePongTitle);
    Ball ball;
    int userUpperY = INITIAL_Y_POSITION;
    int lastUserY = INITIAL_Y_POSITION;
    int enemyUpperY = INITIAL_Y_POSITION;
    int lastEnemyY = INITIAL_Y_POSITION;
    initBall(&ball);
    drawPongBackground();
    drawPongUser(userUpperY, lastUserY);
    drawPongEnemy(enemyUpperY, lastEnemyY);
    drawScoreText();
    drawScore(score);

    while(!gameOver){
        moveUser(&userUpperY, &lastUserY);
        moveEnemy(&enemyUpperY, &lastEnemyY, ball);
        moveBall(&ball);
        drawPongUser(userUpperY, lastUserY);
        drawPongEnemy(enemyUpperY, lastEnemyY);
        drawBall(ball);
        if (checkPongBorderCollision(ball)){
            invertBallYDirection(&ball);
        }
        if (ball.x == 4){
            if (checkUserCollision(userUpperY, ball)){
                invertBallXDirection(&ball);
                updateBallY(&ball);
                drawScore(++score);
            } else{
                gameOver = true;
            }
        }
        if (ball.x + 3 == 123){
            if (checkEnemyCollision(enemyUpperY, ball)){
                invertBallXDirection(&ball);
                updateBallY(&ball);
            } else{
                gameOver = true;
            }
        }
        wait(20);
    }
}
