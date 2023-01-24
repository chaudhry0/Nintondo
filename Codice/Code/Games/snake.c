/*******************************************************************************
* Title                 :   SNAKE
* Filename              :   snake.c
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file snake.c
 *
 * @brief This module runs the snake game.
 *        The snake is controlled by the joystick.
 *        The snake grows when it eats an apple.
 *        The game ends when the snake collides with the border or itself.
 *        The game can be restarted from the menu.
 *        The length of the snake is increased by 1 every time it eats an apple.
 *        The speed of the snake increases with the score.
 *        The body of the snake is stored in a list.
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/
#include "snake.h"
#include "Code/Images/snakeImages.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/*!
 * @brief This Function initializes snake body (after clearing it).
 *        The snake is initialized with INITIAL_LENGTH cells.       
 *
 * @param[in] snakeBody  Pointer to the list containing the snake body.
 *
 * 
 * @return none --> void
 */
void initSnakeBody(List* snakeBody){
    initList(snakeBody);
    int i = 0;
    for (i=0; i<INITIAL_LENGTH; i++){
        push(snakeBody, i+1, CELL_SIZE_SMALL - 1);
    }
}

/*!
 * @brief This Function checks if the user prompts a not allowed movement     
 *         (e.g. if the snake is moving right, the user cannot prompt left).
 *       If the user prompts an allowed movement, the function returns false.
 *
 * 
 * @param[in] moving  The direction the snake is moving.
 *
 * 
 * @return true if the user prompts an allowed movement, false otherwise
 */
bool checkIfOpposite(enum Moving moving) {
    if ((moving == RIGHT && lastMove == 4) ||
        (moving == LEFT && lastMove == 2) ||
        (moving == DOWN && lastMove == 1) ||
        (moving == UP && lastMove == 3)) {
        return true;
    }
    return false;
}

/*!
 * @brief This Function is to move the snake logically.
 *        Updates snake xVel and yVel; 
 *        Then it pushes the tail to the head (updating cords).
 * 
 * 
 * @param[in] snakeBodyPtr  Pointer to the list containing the snake body.
 * @param[in] moving        The direction the snake is moving.
 * @param[in] xHead         The x coordinate of the head of the snake.
 * @param[in] yHead         The y coordinate of the head of the snake.
 * @param[in] lastXPtr      Pointer to the x coordinate of the tail of the snake.
 * @param[in] lastYPtr      Pointer to the y coordinate of the tail of the snake.
 * 
 * 
 * @return node --> void
 */
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

/*!
 * @brief This Function is to draw the background of the snake game.
 *        
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
void drawSnakeBackground() {
    Graphics_drawImage(&g_sContext, &imageSnakeBackground, 0, CELL_SIZE_SMALL * 2);
}

/*!
 * @brief This Function is to clear the old background cell after snake movements
 *        
 *
 * @param[in] tailx           The x coordinate of the tail of the snake.
 * @param[in] taily           The y coordinate of the tail of the snake.
 * @param[in] lightGreenCell  Pointer to a boolean variable that indicates if the last cell was light green.
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is to draw a single snake body cell.
 *        
 *
 * @param[in] x  The x coordinate of the cell.
 * @param[in] y  The y coordinate of the cell.
 *
 * 
 * @return none --> void
 */
void drawSnakeCell(int x, int y) {
    Graphics_drawImage(&g_sContext, &imageSnakeBody, x * CELL_SIZE_SMALL, y * CELL_SIZE_SMALL);
}

/*!
 * @brief This Function is to draw the whole snake body.
 *        
 *
 * @param[in] snakeBody  The list containing the snake body.
 *
 * 
 * @return none --> void
 */
void drawSnakeFull(List snakeBody) {
    int i;
    for (i=0; i<snakeBody.length; i++){
        drawSnakeCell(getElem(snakeBody, i + 1).x, getElem(snakeBody, i + 1).y);
    }
}

/*!
 * @brief This Function is to generate new apple cords avoiding overlaps with the snake.
 *        
 *
 * @param[in] snakeBody  The list containing the snake body.
 * @param[in] apple      Pointer to the apple struct.
 *
 * 
 * @return none --> void
 */
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

/*!
 * @brief This Function is to draw the apple.
 *        
 *
 * @param[in] apple  Pointer to the apple struct.
 *
 * 
 * @return none --> void
 */
void drawApple(Apple apple) {
    Graphics_drawImage(&g_sContext, &imageSnakeApple, apple.x * CELL_SIZE_SMALL, apple.y * CELL_SIZE_SMALL);
}

/*!
 * @brief This Function is to check if the apple is eaten.
 *        
 *
 * @param[in] snakeBody  The list containing the snake body.
 * @param[in] apple      Pointer to the apple struct.
 *
 * 
 * @return true if the apple is eaten, false otherwise.
 */
bool checkAppleCollision(List snakeBody, Apple apple) {
    if (apple.x == getLastElem(snakeBody).x && apple.y == getLastElem(snakeBody).y){
        return true;
    } else{
        return false;
    }
}

/*!
 * @brief This Function is to check if the snake collides with the border.
 *        
 *
 * @param[in] snakeBody  The list containing the snake body.
 *
 * 
 * @return true if the snake collides with the border, false otherwise.
 */
bool checkBorderCollision(List snakeBody) {
    if (getLastElem(snakeBody).x < 0 || getLastElem(snakeBody).x > 15 || getLastElem(snakeBody).y < 2 || getLastElem(snakeBody).y > 13){
        return true;
    } else{
        return false;
    }
}

/*!
 * @brief This Function is to check if the snake collides with itself.
 *        
 *
 * @param[in] snakeBody  The list containing the snake body.
 *
 * 
 * @return true if the snake collides with itself, false otherwise.
 */
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

/*!
 * @brief This Function is the main function and it runs the snake game.
 *        It shows the initial title, the tutorial, and the game itself.
 *        
 *
 * @param[in] none
 *
 * 
 * @return none --> void
 */
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
