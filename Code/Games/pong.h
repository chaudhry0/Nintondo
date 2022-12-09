#ifndef _CODE_GAMES_PONG_H_
#define _CODE_GAMES_PONG_H_

#include "Code/Utilities/init.h"

#define INITIAL_Y_POSITION 60

typedef struct Ball {
    int x;
    int y;
    int xVel;
    int yVel;
} Ball;


    // [FUNCTIONS]
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
void drawPongInitial(); // draws initial text
void drawPongBackground(); // draws the background
void drawPongUser(int userUpperY, int lastUserY); // draws the user
void drawPongEnemy(int enemyUpperY, int lastEnemyY); // draws the enemy
void drawBall(Ball ball); // draws the ball
// run function
void runPong(); // runs the Pong game


#endif /* _CODE_GAMES_PONG_H_ */
