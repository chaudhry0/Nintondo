#include "snake.h"
#include "Code/Images/snakeImages.h"

void initSnakeBody(List* snakeBody){
    initList(snakeBody);
    int i = 0;
    for (i=0; i<INITIAL_LENGTH; i++){
        push(snakeBody, i+1, CELL_SIZE_SMALL - 1);
    }
}

bool checkIfOpposite(enum Moving moving) {
    if ((moving == RIGHT && lastMove == 4) ||
        (moving == LEFT && lastMove == 2) ||
        (moving == DOWN && lastMove == 1) ||
        (moving == UP && lastMove == 3)) {
        return true;
    }
    return false;
}

void moveSnake(List* snakeBodyPtr, enum Moving* moving, int xHead, int yHead, int* lastXPtr, int* lastYPtr){
    int xVel = 0;
    int yVel = 0;
    if (!checkIfOpposite(*moving)){
        switch(lastMove){
            case 1:
                *moving = UP;
                break;
            case 2:
                *moving = RIGHT;
                break;
            case 3:
                *moving = DOWN;
                break;
            case 4:
                *moving = LEFT;
                break;
            default:
                break;
        }
    }
    switch(*moving){
        case UP:
            yVel = -1;
            xVel = 0;
            break;
        case RIGHT:
            xVel = 1;
            yVel = 0;
            break;
       case DOWN:
           yVel = 1;
           xVel = 0;
           break;
       case LEFT:
           xVel = -1;
           yVel = 0;
           break;
       default:
           break;
    }
    Cords cordsHead = getFirstElem(*snakeBodyPtr);
    *lastXPtr = cordsHead.x;
    *lastYPtr = cordsHead.y;
    push(snakeBodyPtr, xHead + xVel, yHead + yVel);
}

void drawSnakeBackground() {
    Graphics_drawImage(&g_sContext, &imageSnakeBackground, 0, CELL_SIZE_SMALL * 2);
}

void clearSnake(int tailx, int taily, bool* lightGreenCell){
    if (*lightGreenCell){
        drawRect(CELL_SIZE_SMALL * tailx,
                 CELL_SIZE_SMALL * tailx + CELL_SIZE_SMALL -1,
                 CELL_SIZE_SMALL * taily,
                 CELL_SIZE_SMALL * taily + CELL_SIZE_SMALL -1,
                 LIGTH_GREEN);
    }else {
        drawRect(CELL_SIZE_SMALL * tailx,
                 CELL_SIZE_SMALL * tailx + CELL_SIZE_SMALL -1,
                 CELL_SIZE_SMALL * taily,
                 CELL_SIZE_SMALL * taily + CELL_SIZE_SMALL -1,
                 GREEN);
    }
    *lightGreenCell = !(*lightGreenCell);
}

void drawSnakeCell(int x, int y) {
    Graphics_drawImage(&g_sContext, &imageSnakeBody, x * CELL_SIZE_SMALL, y * CELL_SIZE_SMALL);
}

void drawSnakeFull(List snakeBody) {
    int i;
    for (i=0; i<snakeBody.length; i++){
        drawSnakeCell(getElem(snakeBody, i + 1).x, getElem(snakeBody, i + 1).y);
    }
}

void generateRandomApple(List snakeBody, Apple* apple) {
    apple->x = random(0, 15);
    apple->y = random(2, 13);
    int i;
    for (i=0; i<snakeBody.length; i++){
        if (apple->x == getElem(snakeBody, snakeBody.length - i).x && apple->y == getElem(snakeBody, snakeBody.length - i).y){
            generateRandomApple(snakeBody, apple);
        }
    }
}

void drawApple(Apple apple) {
    Graphics_drawImage(&g_sContext, &imageSnakeApple, apple.x * CELL_SIZE_SMALL, apple.y * CELL_SIZE_SMALL);
}

bool checkAppleCollision(List snakeBody, Apple apple) {
    if (apple.x == getLastElem(snakeBody).x && apple.y == getLastElem(snakeBody).y){
        return true;
    } else{
        return false;
    }
}

bool checkBorderCollision(List snakeBody) {
    if (getLastElem(snakeBody).x < 0 || getLastElem(snakeBody).x > 15 || getLastElem(snakeBody).y < 2 || getLastElem(snakeBody).y > 13){
        return true;
    } else{
        return false;
    }
}

bool checkSnakeCollision(List snakeBody) {
    int i = 0;
    for (i=3; i<=snakeBody.length-1; i++){
        if ((getLastElem(snakeBody).x == getElem(snakeBody, snakeBody.length - i).x) &&
           (getLastElem(snakeBody).y == getElem(snakeBody, snakeBody.length - i).y)){
            return true;
        }
    }
    return false;
}

void runSnake() {
    showInitialTitle(imageSnakeTitle);
    drawSnakeBackground();
    showTutorialSmall(imageTutorialSnake);
    bool lightGreenCell = true;
    int speed = 300;
    int lastX = 0;
    int lastY = 0;
    lastMove = 0;
    List snakeBody;
    Apple apple;
    enum Moving moving = RIGHT;
    initSnakeBody(&snakeBody);
    generateRandomApple(snakeBody, &apple);
    drawSnakeBackground();
    drawSnakeFull(snakeBody);
    drawApple(apple);
    drawScoreText();
    drawScore(score);

    while(!gameOver){
        moveSnake(&snakeBody, &moving, getLastElem(snakeBody).x, getLastElem(snakeBody).y, &lastX, &lastY);
        if (checkBorderCollision(snakeBody) || checkSnakeCollision(snakeBody) || score == 100){
            gameOver = true;
        } else{
            if (!checkAppleCollision(snakeBody, apple)){
                pop(&snakeBody);
                clearSnake(lastX, lastY, &lightGreenCell);
            } else{
                generateRandomApple(snakeBody, &apple);
                drawApple(apple);
                drawScore(++score);
                if (speed > 100){
                    speed -= 5;
            }
        }
        drawSnakeCell(getLastElem(snakeBody).x, getLastElem(snakeBody).y);
        wait(speed);
        }
    }
}
