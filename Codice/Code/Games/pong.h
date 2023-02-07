/*******************************************************************************
* Title                 :   PONG
* Filename              :   pong.h
* Last Revision Date    :   25/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file pong.h
 *
 * @brief This is the header file for the pong game
 *        It contains all the useful functions and variables for the game
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/

#ifndef _CODE_GAMES_PONG_H_
#define _CODE_GAMES_PONG_H_

/******************************************************************************
* [ INCLUDES ]
*******************************************************************************/
#include "Code/Utilities/init.h"

/******************************************************************************
* [ MACROS ]
*******************************************************************************/
#define INITIAL_Y_POSITION 60
#define PONG_UNIT 4
#define PLAYERS_SPEED 2
#define PONG_SPEED 20

/******************************************************************************
* [ TYPEDEFS STRUCTS ]
*******************************************************************************/
typedef struct Ball {
    int x;
    int y;
    int xVel;
    int yVel;
} Ball;

/******************************************************************************
* [ FUNCTIONS PROTOTYPES ]
*******************************************************************************/
// init functions
void initBall(Ball* ballPtr); // initializes the ball
// moving/updating functions
void moveUser(int* userUpperYPtr, int* lastUserYPtr); // moves the user
void moveEnemy(int* enemyUpperYPtr, int* lastEnemyYPtr, Ball ball); // moves the enemy
void moveBall(Ball* ballPtr); // moves the ball
void invertBallXDirection(Ball* ballPtr); // inverts the ball horizontal direction
void invertBallYDirection(Ball* ballPtr); // inverts the ball vertical direction
void updateBallY(Ball* ballPtr); // updates the ball vertical velocity
// bool functions
bool checkUserCollision(int userUpperY, Ball ball); // checks if the ball collides with the user
bool checkEnemyCollision(int enemyUpperY, Ball ball);  // checks if the ball collides with the enemy
bool checkPongBorderCollision(Ball ball); // checks if the ball collides with any border
// draw functions
void drawPongBackground(); // draws the background
void drawPongUser(int userUpperY, int lastUserY); // draws the user
void drawPongEnemy(int enemyUpperY, int lastEnemyY); // draws the enemy
void drawBall(Ball ball); // draws the ball
// run function
void runPong(); // runs the Pong game


#endif /* _CODE_GAMES_PONG_H_ */

/*** End of File **************************************************************/
