#include "spaceGame.h"
#include "Code/Images/spaceGameImages.h"

void drawBackground(){
    drawRect(0, MAX_WIDTH, BAR_SIZE, BAR_SIZE + MAX_HEIGHT - 1, DARK_BLUE);
}

void updateSpacecraft(Spacecraft* spacecraft){
    switch(direction){
        case 2:
            if(spacecraft->x + 8 < 119){
                spacecraft->x += 8;
                lastMove = 2;
            }
            break;
        case 4:
            if (spacecraft->x > 8){
                spacecraft->x -= 8;
                lastMove = 4;
            }
            break;
        default:
            break;
    }
}

void updateBullet(Entity* bullets, int i){
    (bullets + i)->y -= 4;
}

void drawBullet(Entity bullets[], int i){
    Graphics_drawImage(&g_sContext, &imageBullet, bullets[i].x, bullets[i].y);
}

void cleanBulletMovement(Entity bullets[], int i){
    drawRect(bullets[i].x, bullets[i].x + 3, bullets[i].y + 4, bullets[i].y + 7, DARK_BLUE);
}

void cleanBullet(Entity bullets[], int i){
    drawRect(bullets[i].x, bullets[i].x + 3, bullets[i].y, bullets[i].y + 3, DARK_BLUE);
}

void drawSpacecraft(Spacecraft spacecraft){
    Graphics_drawImage(&g_sContext, &imageSpacecraft, spacecraft.x - 4, 96);
}

void cleanSpacecraft(Spacecraft spacecraft){
    switch(lastMove){
        case 2:
            drawRect(spacecraft.x - 8 - 4, spacecraft.x - 1 - 4, 96, 111, DARK_BLUE);
            break;
        case 4:
            drawRect(spacecraft.x + 16 - 4, spacecraft.x + 23 + 4, 96, 111, DARK_BLUE);
            break;
        default:
            break;
    }
}

bool checkNotDupilcates(Entity enemies[], int x){
    int i;
    for (i=0; i<NUM_ENEMIES; i++){
        if (x == enemies[i].x){
            return false;
        }
    }
    return true;
}

void initBullets(Entity* bullets){
    int i;
    for (i=0; i<NUM_BULLETS; i++){
        (bullets + i)->isActive = false;
    }
}

void initEnemies(Entity* enemies){
    int i;
    for (i=0; i<NUM_ENEMIES; i++){
        int x = random(1, 14) * 8;
        while(!checkNotDupilcates(enemies, x)){ // occhio qua
            x = random(1, 14) * 8;
        }
        (enemies + i)->x = x;
        (enemies + i)->y = 16;
        (enemies + i)->isActive = true;
    }
}

void initSingleEnemy(Entity* enemies, int i){
    int x = random(1, 14) * 8;
    while(!checkNotDupilcates(enemies, x)){ // occhio anche qua
        x = random(1, 14) * 8;
    }
    (enemies + i)->x = x;
    (enemies + i)->y = 18;
    (enemies + i)->isActive = true;
}

void updateEnemies(Entity* enemies, int i){
    (enemies + i)->y += 2;
}

void drawEnemy(Entity enemies[], int i){
    Graphics_drawImage(&g_sContext, &imageSpaceEnemy, enemies[i].x, enemies[i].y);
}

void cleanEnemyMovement(Entity enemies[], int i){
    drawRect(enemies[i].x, enemies[i].x + 7, enemies[i].y - 1, enemies[i].y - 2, DARK_BLUE);
}

void cleanEnemy(Entity enemies[], int i){
    drawRect(enemies[i].x, enemies[i].x + 7, enemies[i].y, enemies[i].y + 7, DARK_BLUE);
}

void drawBulletsCompleteBar(){
    int i;
    for (i=0; i<NUM_BULLETS; i++){
        Graphics_drawImage(&g_sContext, &imageBulletBar, 122, 87 - i * 9);
    }
}

void cleanBulletBar(int numBulletsActive){
    int y1 = 87 - (3 - numBulletsActive) * 9;
    int y2 = 92 - (3 - numBulletsActive) * 9;
    drawRect(122, 125, y1, y2, BLUE);
}

void drawBulletBar(int numBulletsActive){
    Graphics_drawImage(&g_sContext, &imageBulletBar, 122, 87 - (2 - numBulletsActive) * 9);
}

bool checkBulletHits(Entity bullets[], int i, Entity enemies[], int j){
    if (bullets[i].x - 2 == enemies[j].x){
        if (bullets[i].y <= enemies[j].y + 10){
            return true;
        }
    }
    return false;
}

bool checkLooseCondition(Entity enemies[]){
    int i;
    for (i=0; i<NUM_ENEMIES; i++){
        if (enemies[i].isActive){
            if (enemies[i].y >= 88){
                return true;
            }
        }
    }
    return false;
}

bool checkIfBulletAvailable(Entity bullets[]){
    int i;
    for (i=0; i<NUM_BULLETS; i++){
        if (!bullets[i].isActive){
            return true;
        }
    }
    return false;
}

bool checkBulletEnds(Entity bullets[], int i){
    if (bullets[i].y == 16){
        return true;
    }
    return false;
}

void shotBullet(Spacecraft spacecraft, Entity* bullets){
    int i;
    for (i=0; i<NUM_BULLETS; i++){
        if (!(bullets + i)->isActive){
            (bullets + i)->isActive = true;
            (bullets + i)->x = spacecraft.x + 2;
            (bullets + i)->y = 92;
            return;
        }
    }
}

void runSpaceGame(){
    showInitialTitle(imageSpaceInvadersTitle);
    drawBackground();
    showTutorialBig(imageTutorialSpaceInvaders);
    consumeButtonA(); // resets the variable storing if button A has been pressed
    int numBulletsActive = 0; // numbers of bullets on the screen
    int shotCountdown = 0; // countdown to avoid bullets spam
    Spacecraft spacecraft;
    spacecraft.x = 8;
    Entity bullets[NUM_BULLETS];
    initBullets(bullets);
    Entity enemies[NUM_ENEMIES];
    initEnemies(enemies);
    drawBackground();
    drawBulletsCompleteBar();
    drawScoreText();
    drawScore(score);
    wait(100);

    while(!gameOver){
        updateSpacecraft(&spacecraft);
        if (shotCountdown == 0){ // if allowed
            if (consumeButtonA()){ // if button pressed
                if (checkIfBulletAvailable(bullets)){ // if at least one bullet avialable
                    shotBullet(spacecraft, bullets); // shoot the bullet
                    cleanBulletBar(++numBulletsActive);
                    shotCountdown = 1;
                }
            }
        } else{
            shotCountdown--;
            consumeButtonA(); // MMMh
        }
        int i;
        for (i=0; i<NUM_BULLETS; i++){
            if (bullets[i].isActive){ // if bullet active
                updateBullet(bullets, i);
                drawBullet(bullets, i);
                cleanBulletMovement(bullets, i);
                if (checkBulletEnds(bullets, i)){ // if bullet ends
                    bullets[i].isActive = false;
                    cleanBullet(bullets, i);
                    drawBulletBar(--numBulletsActive);
                } else{
                    int j;
                    for (j=0; j<NUM_ENEMIES; j++){
                        if (enemies[j].isActive && bullets[i].isActive){
                            if (checkBulletHits(bullets, i, enemies, j)){ // if the bullet hits an enemy
                                bullets[i].isActive = false;
                                enemies[j].isActive = false;
                                cleanEnemy(enemies, j);
                                cleanBullet(bullets, i);
                                initSingleEnemy(enemies, j);
                                drawBulletBar(--numBulletsActive);
                                drawScore(++score);
                            }
                        }
                    }
                }
            }
        }
        int j;
        for (j=0; j<NUM_ENEMIES; j++){
            if (enemies[j].isActive){
                updateEnemies(enemies, j);
                drawEnemy(enemies, j);
                cleanEnemyMovement(enemies, j);
            }
        }
        drawSpacecraft(spacecraft);
        cleanSpacecraft(spacecraft);
        if (checkLooseCondition(enemies)){
            gameOver = true;
        }
        wait(SPACEINVADERS_SPEED);
    }
}
