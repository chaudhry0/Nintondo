/*******************************************************************************
* Title                 :   SPACE INVADERS
* Filename              :   spaceGame.h
* Last Revision Date    :   01/02/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file spaceGame.h
 *
 * @brief This is the header file for the space invaders game
 *        It contains all the useful functions and variables for the game
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/

#ifndef CODE_GAMES_SPACEGAME_H_
#define CODE_GAMES_SPACEGAME_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Code/Utilities/utilities.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define NUM_ENEMIES 3
#define NUM_BULLETS 3
#define SPACEINVADERS_SPEED 100

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct Spacecraft{
    int x;
}Spacecraft;

typedef struct Entity{
    int x;
    int y;
    bool isActive;
}Entity;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
// [FUNCTIONS]
// init functions
    void initBullets(Entity* bullets); // initializes every bullet
    void initEnemies(Entity* enemies); // initializes every enemy
    void initSingleEnemy(Entity* enemies, int i); // initializes a single enemy
// moving/updating functions
    void updateSpacecraft(Spacecraft* spacecraft); // updates the spacecraft basing on player inputs
    void updateBullet(Entity* bullets, int i); // updates bullets
    void updateEnemies(Entity* enemies, int i); // updates enemies
    void shotBullet(Spacecraft spacecraft, Entity* bullets); // shots a bullet basing on the spacecraft position
// bool functions
    bool checkNotDupilcates(Entity enemies[], int x); // checks if the xPosition is not already occupied by an enemy
    bool checkBulletHits(Entity bullets[], int i, Entity enemies[], int j); // checks if a bullet hits an enemy
    bool checkLooseCondition(Entity enemies[]); // checks if an enemy has reached the maximum position
    bool checkIfBulletAvailable(Entity bullets[]); // checks if a bullet is available
    bool checkBulletEnds(Entity bullets[], int i); // checks if the bullet has reached the end of the screen
// draw functions
    void drawBackground(); // draws the bg
    void drawBullet(Entity bullets[], int i); // draws a bullet
    void cleanBulletMovement(Entity bullets[], int i); // cleans a bullet movement
    void cleanBullet(Entity bullets[], int i); // cleans an entire bullet
    void drawSpacecraft(Spacecraft spacecraft); // draws the spacecraft
    void cleanSpacecraft(Spacecraft spacecraft); // cleans the spacecraft
    void drawEnemy(Entity enemies[], int i); // draws an enemy
    void cleanEnemyMovement(Entity enemies[], int i); // cleans an enemy movement
    void cleanEnemy(Entity enemies[], int i); // cleans an entire enemy
    void drawBulletsCompleteBar(); // draws the bullet bar on the right
    void cleanBulletBar(int numBulletsActive); // removes one bullet from the bar
    void drawBulletBar(int numBulletsActive); // adds one bullet from the bar
// run functions
    void runSpaceGame(); // runs the game


#endif

/*** End of File **************************************************************/

