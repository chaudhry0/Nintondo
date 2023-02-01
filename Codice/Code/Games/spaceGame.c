/*******************************************************************************
* Title                 :   SPACE INVADERS
* Filename              :   spaceInvaders.h
* Last Revision Date    :   01/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file spaceInvaders.h
 *
 * @brief this module runs the space invaders game
 *        To play the game, the player has to move the spacecraft with the left and right using joystick
 *        and shoot with the A button. The player has to destroy all the enemies before they reach the bottom
 *        of the screen. If the player loses all the lives, the game is over.
 *        The player has N lives and N bullets.
 *        The player can move the spacecraft only if there is no enemy in the next position.
 *        The player can shoot only if there is no bullet in the next position. ???
 *        
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "spaceGame.h"
#include "Code/Images/spaceGameImages.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/*!
 * @brief This Function is to draw the background of the space invaders game.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawBackground(){
    drawRect(0, MAX_WIDTH, BAR_SIZE, BAR_SIZE + MAX_HEIGHT - 1, DARK_BLUE);
}

/*!
 * @brief This Function is to update the spacecraft basing on the player inputs. 
 *        Only the x position is updated because the y position is fixed.        
 *
 * @param[in] Spacecraft* spacecraft --> pointer to the spacecraft
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is to update the bullets.
 *        Only the y position is updated because the x position is fixed when the bullet is shot.
 *                
 *
 * @param[in] Entity* bullets --> pointer to the bullets array
 * @param[in] int i --> index of the bullet to update
 *
 * 
 * @return none --> void
 */
void updateBullet(Entity* bullets, int i){
    (bullets + i)->y -= 4;
}

/*!
 * @brief This Function is to draw the bullets. 
 *       
 *
 * @param[in] Entity* bullets --> pointer to the bullets array
 * @param[in] int i --> index of the bullet to draw
 *
 * 
 * @return none --> void
 */
void drawBullet(Entity bullets[], int i){
    Graphics_drawImage(&g_sContext, &imageBullet, bullets[i].x, bullets[i].y);
}

/*!
 * @brief This Function is to clean the bullets movement.
 *        It is used to erase the bullets when they are moving. 
 *        Because the bullets have left their trail.
 *
 * @param[in] Entity* bullets --> pointer to the bullets array
 * @param[in] int i --> index of the bullet to clean
 *
 * 
 * @return none --> void
 */
void cleanBulletMovement(Entity bullets[], int i){
    drawRect(bullets[i].x, bullets[i].x + 3, bullets[i].y + 4, bullets[i].y + 7, DARK_BLUE);
}

/*!
 * @brief This Function is to clean the entire bullet.
 *        Not the trail.
 *
 * @param[in] Entity* bullets --> pointer to the bullets array
 * @param[in] int i --> index of the bullet to clean
 *
 * 
 * @return none --> void
 */
void cleanBullet(Entity bullets[], int i){
    drawRect(bullets[i].x, bullets[i].x + 3, bullets[i].y, bullets[i].y + 3, DARK_BLUE);
}

/*!
 * @brief This Function is to draw the spacecraft.
 *       
 *
 * @param[in] Spacecraft spacecraft --> spacecraft to draw
 *
 * 
 * @return none --> void
 */
void drawSpacecraft(Spacecraft spacecraft){
    Graphics_drawImage(&g_sContext, &imageSpacecraft, spacecraft.x - 4, 96);
}

/*!
 * @brief This Function is to clean the spacecraft.
 *        It is based on the last move of the spacecraft.
 *        If the spacecraft moved to the right, the left part of the spacecraft is cleaned. 
 *        Only few pixels are cleaned because the spacecraft is moving.
 *
 * @param[in] Spacecraft spacecraft --> spacecraft to clean
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is to checks if the xPosition is not already occupied by an enemy
 *       
 *
 * @param[in] Entity enemies[] --> array of enemies
 * @param[in] int x --> xPosition to check
 *
 * 
 * @return bool --> true if the xPosition is not occupied by an enemy, false otherwise
 */
bool checkNotDupilcates(Entity enemies[], int x){
    int i;
    for (i=0; i<NUM_ENEMIES; i++){
        if (x == enemies[i].x){
            return false;
        }
    }
    return true;
}

/*!
 * @brief This Function is to initialize the bullets.
 *        The bullets are not active at the beginning.
 *
 * @param[in] Entity* bullets --> pointer to the bullets array
 *
 * 
 * @return none --> void
 */
void initBullets(Entity* bullets){
    int i;
    for (i=0; i<NUM_BULLETS; i++){
        (bullets + i)->isActive = false;
    }
}

/*!
 * @brief This Function is to initialize the enemies.
 *        The enemies are initialized with a random x position but not duplicated.
 *
 * @param[in] Entity* enemies --> pointer to the enemies array
 *
 * 
 * @return none --> void
 */
void initEnemies(Entity* enemies){
    int i;
    for (i=0; i<NUM_ENEMIES; i++){
        int x = random(1, 14) * 8;
        while(!checkNotDupilcates(enemies, x)){ 
            x = random(1, 14) * 8;
        }
        (enemies + i)->x = x;
        (enemies + i)->y = 16;
        (enemies + i)->isActive = true;
    }
}

/*!
 * @brief This Function is to initialize a single enemy.
 *        The enemy is initialized with a random x position but not duplicated.
 *
 * @param[in] Entity* enemies --> pointer to the enemies array
 * @param[in] int i --> index of the enemy to initialize
 *
 * 
 * @return none --> void
 */
void initSingleEnemy(Entity* enemies, int i){
    int x = random(1, 14) * 8;
    while(!checkNotDupilcates(enemies, x)){ 
        x = random(1, 14) * 8;
    }
    (enemies + i)->x = x;
    (enemies + i)->y = 18;
    (enemies + i)->isActive = true;
}

/*!
 * @brief This Function is to update enemies position.
 *        The enemies are moving down.
 *
 * @param[in] Entity* enemies --> pointer to the enemies array
 * @param[in] int i --> index of the enemy to update
 *
 * 
 * @return none --> void
 */
void updateEnemies(Entity* enemies, int i){
    (enemies + i)->y += 2;
}

/*!
 * @brief This Function is to draw the enemies of the space invaders game.
 *                
 *
 * @param[in] enemies --> array of enemies
 * @param[in] i --> index of the enemy to draw
 *
 * 
 * @return none --> void
 */
void drawEnemy(Entity enemies[], int i){
    Graphics_drawImage(&g_sContext, &imageSpaceEnemy, enemies[i].x, enemies[i].y);
}

/*!
 * @brief This Function is  usued to clean the trail of the enemies.
 *        Not the entire enemy.
 *
 * @param[in] enemies --> array of enemies
 * @param[in] i --> index of the enemy to clean
 *
 * 
 * @return none --> void
 */
void cleanEnemyMovement(Entity enemies[], int i){
    drawRect(enemies[i].x, enemies[i].x + 7, enemies[i].y - 1, enemies[i].y - 2, DARK_BLUE);
}

/*!
 * @brief This Function is to clean the entire enemies.
 *        It is usued to clean the enemies when they are destroyed. Not the trail.
 *
 * @param[in] enemies --> array of enemies
 * @param[in] i --> index of the enemy to clean
 *
 * 
 * @return none --> void
 */
void cleanEnemy(Entity enemies[], int i){
    drawRect(enemies[i].x, enemies[i].x + 7, enemies[i].y, enemies[i].y + 7, DARK_BLUE);
}

/*!
 * @brief This Function is to draw the bullets of the space invaders game.
 *                
 *
 * @param[in] bullets --> array of bullets
 * @param[in] i --> index of the bullet to draw
 *
 * 
 * @return none --> void
 */
void drawBulletsCompleteBar(){
    int i;
    for (i=0; i<NUM_BULLETS; i++){
        Graphics_drawImage(&g_sContext, &imageBulletBar, 122, 87 - i * 9);
    }
}

/*!
 * @brief This Function is to clean the bullert bar.
 *                
 *
 * @param[in] int numBulletsActive --> number of bullets active
 *
 * 
 * @return none --> void
 */
void cleanBulletBar(int numBulletsActive){
    int y1 = 87 - (3 - numBulletsActive) * 9;
    int y2 = 92 - (3 - numBulletsActive) * 9;
    drawRect(122, 125, y1, y2, BLUE);
}

/*!
 * @brief This Function is to draw the bullet bar.
 *                
 *
 * @param[in] int numBulletsActive --> number of bullets active
 * 
 *
 * 
 * @return none --> void
 */
void drawBulletBar(int numBulletsActive){
    Graphics_drawImage(&g_sContext, &imageBulletBar, 122, 87 - (2 - numBulletsActive) * 9);
}

/*!
 * @brief This Function is to check if the bullet hits an enemy.
 *                
 *
 * @param[in] bullets --> array of bullets
 * @param[in] i --> index of the bullet 
 * @param[in] enemies --> array of enemies
 * @param[in] j --> index of the enemy 
 *
 * 
 * @return bool --> true if the bullet hits the enemy, false otherwise
 */
bool checkBulletHits(Entity bullets[], int i, Entity enemies[], int j){
    if (bullets[i].x - 2 == enemies[j].x){
        if (bullets[i].y <= enemies[j].y + 10){
            return true;
        }
    }
    return false;
}

/*!
 * @brief This Function is to check if an enemy has reached the maximum position (end of screen).
 *       If an enemy has reached the maximum position, the player has lost.
 *                
 *
 * @param[in] enemies --> array of enemies
 *
 * 
 * @return bool --> true if an enemy has reached the maximum position, false otherwise
 */
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

/*!
 * @brief This Function is to check if the bullet is available.
 *       If the bullet is available, the player can shoot.
 *                
 *
 * @param[in] bullets --> array of bullets
 *
 * 
 * @return bool --> true if the bullet is available, false otherwise
 */
bool checkIfBulletAvailable(Entity bullets[]){
    int i;
    for (i=0; i<NUM_BULLETS; i++){
        if (!bullets[i].isActive){
            return true;
        }
    }
    return false;
}

/*!
 * @brief This Function is to check if the bullet has reached the end of the screen.
 *       If the bullet has reached the end of the screen, it is not active anymore.
 *                
 *
 * @param[in] bullets --> array of bullets
 * @param[in] i --> index of the bullet 
 *
 * 
 * @return bool --> true if the bullet has reached the end of the screen, false otherwise
 */
bool checkBulletEnds(Entity bullets[], int i){
    if (bullets[i].y == 16){
        return true;
    }
    return false;
}

/*!
 * @brief This Function is to shoot a bullet.
 *        It uses the scpacecraft position to know where to shoot the bullet.
 *                
 *
 * @param[in] spacecraft --> spacecraft
 * @param[in] bullets --> array of bullets
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is the main function and it runs the space invaders game.
 *        It shows the initial title, the tutorial and the background.
 *                
 *
 * @param[in] none 
 *
 * 
 * @return none --> void
 */
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

/*** end of file ***/
