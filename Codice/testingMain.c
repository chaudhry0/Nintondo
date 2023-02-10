#include "Code/Menu/gameHub.h"

//#define TESTING_SPEED 50

void clean();

void testDrawArrow();
void testMenu();
void testRandomGeneratorFunction();
void testDrawScore();
void testGameOver();
void testDrawRect();
void testPong();

// --------------- Floppy Disk ---------------

void testFloppyDiskMovement();
void testRamMovement();

void main(void) {

    // preparing the environment for testing
    _hwInit();
    clean();

    /*
    // testing FD
    testFloppyDiskMovement();
    wait(1000);
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
    */

    // testing pong
    //testPongUserAndEnemy()
    //testin floppy disk
    testFloppyDiskMovement();
    wait(1000);
    clean();
    testRamMovement();
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

void testPongUserAndEnemy(){
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




//    direction = 1;
//    for (i=0; i<50){
//        drawPongUser(userUpperY, lastUserY);
//        moveUser(&userUpperY, &lastUserY);
//    }

}














// ---------------------------- FLOPPY DISK TESTS ----------------------------
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



