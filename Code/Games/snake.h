#ifndef SNAKE_H_
#define SNAKE_H_

#include "Code/Utilities/init.h"
#include "Code/Utilities/list.h"

#define INITIAL_LENGTH 3
#define SNAKE_SPEED 200

enum Moving {UP, RIGHT, DOWN, LEFT};

typedef struct Apple {
    int x;
    int y;
} Apple;


    // [FUNCTIONS]
// init functions
void initSnakeBody(List* snakeBody); // initializes snake body (after clearing it)
// moving/updating functions
void moveSnake(List* snakeBodyPtr, enum Moving* moving, int xHead, int yHead, int* lastXPtr, int* lastYPtr); // updates snake xVel and yVel; then it pushes the tail to the head (updating cords)
void generateRandomApple(List snakeBody, Apple* apple); // generate new apple cords avoiding overlaps with the snake
// bool functions
bool checkIfOpposite(enum Moving moving); // checks if the user prompts a not allowed movement
bool checkAppleCollision(List snakeBody, Apple apple); // checks if the apple is eaten
bool checkBorderCollision(List snakeBody); // checks if snake collides with the border
bool checkSnakeCollision(List snakeBody); // checks if snake collides with itself
// draw functions
void drawSnakeBackground(); // draws the background
void drawSnakeCell(int x, int y); // draws a single snake body cell
void drawSnakeFull(List snakeBody); // draws the full snake body
void clearSnake(int tailx, int taily, bool* lightGreenCell); // clears the old background cell after snake movements
void drawApple(); // draw the apple
// run function
void runSnake(); // runs the Snake game


#endif /* SNAKE_H_ */
