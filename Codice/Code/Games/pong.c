/*******************************************************************************
* Title                 :   PONG
* Filename              :   pong.h
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file pong.c
 *
 * @brief This module runs the pong game.
 *        To play the game, the user must use the joystick to move the paddle
 *        and hit the ball back to the opponent. The user must hit the ball
 *        if he doesn't want to lose the game.
 *        The game ends when the user or the opponent misses the ball.
 *        The speed of the ball increases every time the user hits the ball.
 *        The difficulty of the game is set by default.
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "pong.h"
#include "Code/Images/pongImages.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/*!
 * @brief This Function initializes the ball.
 *        It sets the ball position and velocity.        
 *
 * @param[in] ballPtr --> pointer to the ball
 *
 * 
 * @return none --> void
 */
void initBall(Ball* ballPtr){
    ballPtr->x = 100;
    ballPtr->y = 70;
    ballPtr->xVel = -2;
    ballPtr->yVel = 0;
}

/*!
 * @brief This Function is to draw the background of the pong game.
 *                
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawPongBackground(){
    Graphics_drawImage(&g_sContext, &imagePongBackground, 0, CELL_SIZE_LARGE);
}

/*!
 * @brief This Function is to draw the user of the pong game.
 *                
 *
 * @param[in] userUpperY --> the upper y coordinate of the user
 * @param[in] lastUserY --> the last upper y coordinate of the user
 *
 * 
 * @return none --> void
 */
void drawPongUser(int userUpperY, int lastUserY){
    Graphics_drawImage(&g_sContext, &imagePongUser, 0, userUpperY);
    if (lastUserY < userUpperY){ // moving down
        drawRect(0, 3, userUpperY - 1, userUpperY -2, GREEN);
    } else if (lastUserY > userUpperY){ // moving down
        drawRect(0, 3, userUpperY + CELL_SIZE_LARGE , userUpperY + CELL_SIZE_LARGE + 1, GREEN);
    }
}

/*!
 * @brief This Function is to draw the enemy of the pong game.
 *                
 *
 * @param[in] enemyUpperY --> the upper y coordinate of the enemy
 * @param[in] lastEnemyY --> the last upper y coordinate of the enemy
 *
 * 
 * @return none --> void
 */
void drawPongEnemy(int enemyUpperY, int lastEnemyY){
    Graphics_drawImage(&g_sContext, &imagePongEnemy, 124, enemyUpperY);
    if (lastEnemyY < enemyUpperY){ // moving down
        drawRect(124, 127, enemyUpperY - 1, enemyUpperY -4, GREEN);
    } else if (lastEnemyY > enemyUpperY){ // moving down
        drawRect(124, 127, enemyUpperY + CELL_SIZE_LARGE , enemyUpperY + CELL_SIZE_LARGE + 3, GREEN);
    }
}

/*!
 * @brief This Function is to draw the ball of the pong game.
 *       
 *
 * @param[in] ball --> the ball
 *
 * 
 * @return none --> void
 */
void drawBall(Ball ball){
    drawRect(ball.x - ball.xVel, ball.x - ball.xVel + 3, ball.y - ball.yVel, ball.y - ball.yVel + 3, GREEN);
    Graphics_drawImage(&g_sContext, &imagePongBall, ball.x, ball.y);
}

/*!
 * @brief This Function is to moves the user.
 *        It moves the user according to the direction variable.
 *        The direction variable is set by the joystick.
 *        The user can move up and down.
 *                
 *
 * @param[in] userScore --> the score of the user
 * @param[in] enemyScore --> the score of the enemy
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is to moves the enemy.
 *        It moves the enemy according to the ball position.
 *        The enemy moves up and down.
 *                
 *
 * @param[in] enemyUpperY --> the upper y coordinate of the enemy
 * @param[in] lastEnemyY --> the last upper y coordinate of the enemy
 * @param[in] ball --> the ball
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is to moves the ball.
 *        It moves the ball according to the ball velocity.
 *                
 *
 * @param[in] ballPtr --> pointer to the ball
 *
 * 
 * @return none --> void
 */
void moveBall(Ball* ballPtr){
    ballPtr->x += ballPtr->xVel;
    ballPtr->y += ballPtr->yVel;
}

/*!
 * @brief This Function is to check if the ball collides with the user.
 *        It checks if the ball collides with the user.
 *        If the ball collides with the user, the ball bounces back.
 *                
 *
 * @param[in] userUpperY --> the upper y coordinate of the user
 * @param[in] ball --> the ball
 *
 * 
 * @return true --> if the ball collides with the user
 * @return false --> if the ball does not collide with the user
 */
bool checkUserCollision(int userUpperY, Ball ball){
    int i;
    for (i=0; i<CELL_SIZE_LARGE; i++){
        if (userUpperY + i == ball.y || userUpperY + i == ball.y + 3){
            return true;
        }
    }
    return false;
}

/*!
 * @brief This Function is to check if the ball collides with the enemy.
 *        It checks if the ball collides with the enemy.
 *        If the ball collides with the enemy, the ball bounces back.
 *                
 *
 * @param[in] enemyUpperY --> the upper y coordinate of the enemy
 * @param[in] ball --> the ball
 *
 * 
 * @return true --> if the ball collides with the enemy
 * @return false --> if the ball does not collide with the enemy
 */
bool checkEnemyCollision(int enemyUpperY, Ball ball){
    int i;
    for (i=0; i<CELL_SIZE_LARGE; i++){
        if (enemyUpperY + i == ball.y || enemyUpperY + i == ball.y + 3){
            return true;
        }
    }
    return false;
}

/*!
 * @brief This Function is to check if the ball collides with the border.
 *        It checks if the ball collides with the border.
 *        If the ball collides with the border, the ball bounces back.
 *                
 *
 * @param[in] ball --> the ball
 *
 * 
 * @return true --> if the ball collides with the border
 * @return false --> if the ball does not collide with the border
 */
bool checkPongBorderCollision(Ball ball){
    if (ball.y <= 20 || ball.y + 3 >= 107){
        return true;
    }
    return false;
}

/*!
 * @brief This Function is to inverts the ball horizontal direction.
 *                
 *
 * @param[in] ballPtr --> pointer to the ball
 *
 * 
 * @return none --> void
 */
void invertBallXDirection(Ball* ballPtr){
    ballPtr->xVel = - ballPtr->xVel;
}

/*!
 * @brief This Function is to inverts the ball vertical direction.
 *                
 *
 * @param[in] ballPtr --> pointer to the ball
 *
 * 
 * @return none --> void
 */
void invertBallYDirection(Ball* ballPtr){
    ballPtr->yVel = - ballPtr->yVel;
}

/*!
 * @brief This Function is to updates the ball vertical velocity
 *        It updates the ball vertical velocity randomly from -3 to 3.
 *        
 *                
 *
 * @param[in] ballPtr --> pointer to the ball
 *
 * 
 * @return none --> void
 */
void updateBallY(Ball* ballPtr){
    ballPtr->yVel = random(-3, 3);
}

/*!
 * @brief This Function is the main function and it runs the pong game.              
 *        It shows the initial title, the tutorial, and the game itself.
 *        It draws the background, the user, the enemy, the score text, and the score.        
 *        It moves the user, the enemy, and the ball.
 *        It checks if the ball collides with the user, the enemy, or the border.
 *        It updates the score and the ball velocity.
 *        It draws the user, the enemy, the ball, and the score.
 *        
 *          
 * @param[in] none
 * 
 * @return none --> void
 */
void runPong(){
    showInitialTitle(imagePongTitle);
    drawPongBackground();
    showTutorialSmall(imageTutorialPong);
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
