#include "Code/Menu/gameHub.h"

//#define TESTING_SPEED 50

void clean();

void testDrawArrow();
void testMenu();
void testRandomGeneratorFunction();
void testDrawScore();
void testGameOver();
void testDrawRect();
void testSnakeBody();
void testSnakeApple();
void testPongUserAndEnemy();
void testPongBall();
void testRhinoPlayer();
void testRhinoObstacles();
void testFloppyDiskMovement();
void testRamMovement();
void testSpaceGameSpacecraft();
void testSpaceGameEnemies();



void main(void) {

    // preparing the environment for testing
    _hwInit();
    clean();

    // testing menu
    testDrawArrow();
    wait(1000);
    testMenu();
    wait(1000);
    clean();

    // testing gameHub and utilities
    testRandomGeneratorFunction();
    wait(1000);
    testDrawScore();
    wait(1000);
    testDrawRect();
    wait(1000);
    clean();


    // testing snake
    testSnakeBody();
    wait(1000);
    clean();
    testSnakeApple();
    wait(1000);
    clean();

    // testing pong
    testPongUserAndEnemy();
    testPongBall();
    wait(1000);
    clean();

    // testing rhino
    testRhinoPlayer();
    wait(1000);
    clean();
    testRhinoObstacles();
    wait(1000);
    clean();

    // testing floppyDisk
    testFloppyDiskMovement();
    wait(1000);
    clean();
    testRamMovement();
    wait(1000);
    clean();

    // testing spaceInvaders
    testSpaceGameSpacecraft();
    wait(1000);
    clean();
    testSpaceGameEnemies();
    wait(1000);
    clean();

}

void clean(){
    drawRect(0, 127, 0, 127, WHITE);
}

void testDrawArrow(){
    int i;
    for (i=0; i<NUM_ELEMENTS; i++){
        selectedGame = i;
        drawArrow();
        wait(1000);
        cleanArrow();
    }
}

void testMenu(){
    Graphics_Image imageElements[NUM_ELEMENTS];
    initElements(&imageElements[0]);
    initElements(&imageElements[0]);
    drawMenu(&imageElements[0]);
    menuNumber = 0;
    initElements(&imageElements[0]);
    drawMenu(&imageElements[0]);
    wait(1000);
    menuNumber = 1;
    initElements(&imageElements[0]);
    drawMenu(&imageElements[0]);
}

void testRandomGeneratorFunction(){
    int i;
    int result;
    bool minReached = false;
    bool maxReached = false;
    for (i=0; i<1000; i++){
        result = random(0,100);
        if (result < 0 || result > 100){
            printf("Error in the random function\n");
        } else{
            if (result == 0){
                minReached = true;
            }
            if (result == 100){
                maxReached = true;
            }
        }
    }
    if (minReached && maxReached){
        printf("random function test passed\n\n");
    }
}

void testDrawScore(){
    drawRect(0, 127, 16 + 96 - 1, 127, RED);
    drawScoreText();
    wait(1000);
    drawScore(9);
    wait(1000);
    drawScore(99);
    wait(1000);
    drawScore(999);
    wait(1000);
    cleanBottomBar();
}

void testGameOver(){
    drawGameOver();
}

void testDrawRect(){
    int i;
    int j;
    for (i=0; i<8; i++){
       for (j=0; j<8; j++){
           if ((i+j)%2){
               drawRect(i*16, i*16 + 16, j*16, j*16 + 16, RED);
           } else{
               drawRect(i*16, i*16 + 16, j*16, j*16 + 16, BLUE);
           }
       }
    }
    for (i=0; i<16; i++){
        for (j=0; j<16; j++){
            if ((i+j)%2){
                drawRect(i*8, i*8 + 8, j*8, j*8 + 8, RED);
            } else{
                drawRect(i*8, i*8 + 8, j*8, j*8 + 8, BLUE);
            }
        }
    }
}

void testSnakeBody(){
    List snakeBody;
    enum Moving moving = RIGHT;
    bool lightGreenCell = true;
    uint8_t lastX = 0;
    uint8_t lastY = 0;
    initSnakeBody(&snakeBody);
    drawSnakeBackground();
    drawSnakeFull(snakeBody);
    int i;
    for (i=0; i<4; i++){
        moveSnake(&snakeBody, &moving, getLastElem(snakeBody).x, getLastElem(snakeBody).y, &lastX, &lastY);
        pop(&snakeBody);
        drawSnakeFull(snakeBody);
        clearSnake(lastX, lastY, &lightGreenCell);
        wait(500);
    }
    moving = DOWN;
    for (i=0; i<4; i++){
        moveSnake(&snakeBody, &moving, getLastElem(snakeBody).x, getLastElem(snakeBody).y, &lastX, &lastY);
        pop(&snakeBody);
        drawSnakeFull(snakeBody);
        clearSnake(lastX, lastY, &lightGreenCell);
        wait(500);
    }
    moving = LEFT;
    for (i=0; i<4; i++){
        moveSnake(&snakeBody, &moving, getLastElem(snakeBody).x, getLastElem(snakeBody).y, &lastX, &lastY);
        pop(&snakeBody);
        drawSnakeFull(snakeBody);
        clearSnake(lastX, lastY, &lightGreenCell);
        wait(500);
    }
    moving = UP;
    for (i=0; i<4; i++){
        moveSnake(&snakeBody, &moving, getLastElem(snakeBody).x, getLastElem(snakeBody).y, &lastX, &lastY);
        pop(&snakeBody);
        drawSnakeFull(snakeBody);
        clearSnake(lastX, lastY, &lightGreenCell);
        wait(500);
    }
}

void testSnakeApple(){
    drawSnakeBackground();
    List snakeBody;
    Apple apple;
    initSnakeBody(&snakeBody);
    generateRandomApple(snakeBody, &apple);
    drawSnakeFull(snakeBody);
    drawApple(apple);
    int i;
    for (i=0; i<100; i++){
        generateRandomApple(snakeBody, &apple);
        drawApple(apple);
        wait(100);
    }
}

void testPongUserAndEnemy(){
    drawPongBackground();
    uint8_t userUpperY = 16;
    uint8_t lastUserY = 16;
    uint8_t enemyUpperY = 16;
    uint8_t lastEnemyY = 16;
    Ball ball;
    ball.x = 60;
    ball.y = 16;
    int i;
    for (i=0; i<50; i++){
        drawPongUser(userUpperY, lastUserY);
        moveUser(&userUpperY, &lastUserY, 3);
    }
    for (i=0; i<50; i++){
        drawPongUser(userUpperY, lastUserY);
        moveUser(&userUpperY, &lastUserY, 1);
    }
    ball.yVel = +2;
    for (i=0; i<50; i++){
        moveBall(&ball);
        drawPongEnemy(enemyUpperY, lastEnemyY);
        moveEnemy(&enemyUpperY, &lastEnemyY, ball);
    }
    ball.yVel = -2;
    for (i=0; i<50; i++){
        moveBall(&ball);
        drawPongEnemy(enemyUpperY, lastEnemyY);
        moveEnemy(&enemyUpperY, &lastEnemyY, ball);
     }
}

void testPongBall(){
    drawPongBackground();
    Ball ball;
    initBall(&ball);
    drawBall(ball);
    int i;
    for (i=0; i<500; i++){
        moveBall(&ball);
        drawBall(ball);
        if (checkPongBorderCollision(ball)){
            invertBallYDirection(&ball);
        }
        if (ball.x == PONG_UNIT){
            //if (checkUserCollision(userUpperY, ball)){
                invertBallXDirection(&ball);
                updateBallY(&ball);
                //drawScore(++score);
            //} else{
            //    gameOver = true;
            //}
        }
        if (ball.x + PONG_UNIT == MAX_WIDTH - PONG_UNIT - PONG_UNIT/PLAYERS_SPEED){
            //if (checkEnemyCollision(enemyUpperY, ball)){
                invertBallXDirection(&ball);
                updateBallY(&ball);
            //} else{
            //    gameOver = true;
            //}
        }
        wait(50);
    }
}

void testRhinoPlayer(){
    drawRhinoBackground();
    Rhino rhino;
    uint8_t counterRhino;
    selectAnimation = 0;
    initRhino(&rhino, &counterRhino);
    drawRhino(rhino);
    int i;
    for (i=0; i<80; i++){
        updateRhino(&rhino, &counterRhino);
        clearRhino(rhino);
        drawRhino(rhino);
    }
    for (i=0; i<80; i++){
        buttonA = 1;
        updateRhino(&rhino, &counterRhino);
        clearRhino(rhino);
        drawRhino(rhino);
    }
}

void testRhinoObstacles(){
        drawRhinoBackground();
        Obstacle obstacle1;
        Obstacle obstacle2;
        initObstacle(&obstacle1, 0);
        initObstacle(&obstacle2, 80);
        int i;
        for (i=0; i<100; i++){
            updateObstacle(&obstacle1);
            updateObstacle(&obstacle2);
            clearObstacle(obstacle1);
            clearObstacle(obstacle2);
            drawObstacle(obstacle1);
            drawObstacle(obstacle2);
            if (checkIfObstacleEnds(obstacle1) && obstacle2.x < 128 - 80){
                initObstacle(&obstacle1, 0);
            }
            if (checkIfObstacleEnds(obstacle2) && obstacle1.x < 128 - 80){
                initObstacle(&obstacle2, 0);
            }
            wait(20);
        }
}

void testSpaceGameSpacecraft(){
    drawBackground();
    Spacecraft spacecraft;
    spacecraft.x = CELL_SMALL;
    int i;
    for (i=0; i<15; i++){
        updateSpacecraft(&spacecraft, 2);
        drawSpacecraft(spacecraft);
        cleanSpacecraft(spacecraft);
        wait(200);
    }
    for (i=0; i<15; i++){
        updateSpacecraft(&spacecraft, 4);
        drawSpacecraft(spacecraft);
        cleanSpacecraft(spacecraft);
        wait(200);
    }
}

void testSpaceGameEnemies(){
    drawBackground();
    Entity enemies[NUM_ENEMIES];
    initEnemies(enemies);
    int i;
    for (i=0; i<100; i++){
        uint8_t j;
        for (j=0; j<NUM_ENEMIES; j++){
            if (enemies[j].isActive){
                updateEnemies(enemies, j);
                drawEnemy(enemies, j);
                cleanEnemyMovement(enemies, j);
            }
        }
        if (checkLooseCondition(enemies)){
            initEnemies(enemies);
        }
        wait(50);
    }
}

void testFloppyDiskMovement() {
    uint8_t y = 16;
    uint8_t x = 16;
    for(y = 16; y < 96; y+=2) {
        drawFloppyDisk(x, y);
        clearFloppyDisk(x, y, 0 , - FLOPPY_HEIGHT + SPEED_FLOPPY );
    }
    for(y = 96; y > 16; y-=2) {
        drawFloppyDisk(x, y);
        clearFloppyDisk(x, y,  FLOPPY_HEIGHT - SPEED_FLOPPY, 0 );
    }
}

void testRamMovement() {
    FloppyDisk floppyDisk;
    uint8_t portionSize = 0;
    uint8_t currentPosition = 0;
    initFloppyDisk(&floppyDisk, &portionSize);
    int x = 0;
    for(x = 272; x >= 2; x-=2) {
        moveRam(&currentPosition, &portionSize);
        drawRam(&currentPosition, &portionSize);
        clearRam(&currentPosition, &portionSize);
    }
}
