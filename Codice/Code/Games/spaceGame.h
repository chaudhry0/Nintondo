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
* [ INCLUDES ]
*******************************************************************************/
#include "Code/Utilities/utilities.h"

/******************************************************************************
* [ MACROS ]
*******************************************************************************/
#define NUM_ENEMIES 3
#define NUM_BULLETS 3
#define SPACEINVADERS_SPEED 100

/******************************************************************************
* [ TYPEDEFS STRUCTS]
*******************************************************************************/
typedef struct Spacecraft{
    uint8_t x;
}Spacecraft;

typedef struct Entity{
    uint8_t x;
    uint8_t y;
    bool isActive;
}Entity;

/******************************************************************************
* [ FUNCTIONS PROTOTYPES ]
*******************************************************************************/
// init functions
    void initBullets(Entity* bullets); // initializes every bullet
    void initEnemies(Entity* enemies); // initializes every enemy
    void initSingleEnemy(Entity* enemies, uint8_t i); // initializes a single enemy
// moving/updating functions
    void updateSpacecraft(Spacecraft* spacecraft); // updates the spacecraft basing on player inputs
    void updateBullet(Entity* bullets, uint8_t i); // updates bullets
    void updateEnemies(Entity* enemies, uint8_t i); // updates enemies
    void shotBullet(Spacecraft spacecraft, Entity* bullets); // shots a bullet basing on the spacecraft position
// bool functions
    bool checkNotDupilcates(Entity enemies[], uint8_t x); // checks if the xPosition is not already occupied by an enemy
    bool checkBulletHits(Entity bullets[], uint8_t i, Entity enemies[], uint8_t j); // checks if a bullet hits an enemy
    bool checkLooseCondition(Entity enemies[]); // checks if an enemy has reached the maximum position
    bool checkIfBulletAvailable(Entity bullets[]); // checks if a bullet is available
    bool checkBulletEnds(Entity bullets[], uint8_t i); // checks if the bullet has reached the end of the screen
// draw functions
    void drawBackground(); // draws the bg
    void drawBullet(Entity bullets[], uint8_t i); // draws a bullet
    void cleanBulletMovement(Entity bullets[], uint8_t i); // cleans a bullet movement
    void cleanBullet(Entity bullets[], uint8_t i); // cleans an entire bullet
    void drawSpacecraft(Spacecraft spacecraft); // draws the spacecraft
    void cleanSpacecraft(Spacecraft spacecraft); // cleans the spacecraft
    void drawEnemy(Entity enemies[], uint8_t i); // draws an enemy
    void cleanEnemyMovement(Entity enemies[], uint8_t i); // cleans an enemy movement
    void cleanEnemy(Entity enemies[], uint8_t i); // cleans an entire enemy
    void drawBulletsCompleteBar(); // draws the bullet bar on the right
    void cleanBulletBar(uint8_t numBulletsActive); // removes one bullet from the bar
    void drawBulletBar(uint8_t numBulletsActive); // adds one bullet from the bar
// run functions
    void runSpaceGame(); // runs the game


#endif

/*** End of File **************************************************************/

