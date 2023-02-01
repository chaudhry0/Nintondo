/*******************************************************************************
* Title                 :   RHINO RUNNER
* Filename              :   rhinoRunner.h
* Last Revision Date    :   24/01/2023
* Notes                 :   None
*******************************************************************************/
/*******************************************************************************
 * @file rhinoRunner.h
 *
 * @brief This is the header file for the rhino runner game
 *        It contains all the useful functions and variables for the game
 * 
 * @par       
 * COPYRIGHT NOTICE: (c) 2023 Nintondo. All rights reserved.
*******************************************************************************/

#ifndef CODE_GAMES_RHINORUNNER_H_
#define CODE_GAMES_RHINORUNNER_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "Code/Utilities/init.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define JUMP_COUNTER 10

#define RHINO_X_SIZE 24
#define RHINO_Y_SIZE 12

#define CACTUS_X_SIZE 8
#define CACTUS_Y_SIZE 16

#define BIRD_X_SIZE 16
#define BIRD_Y_SIZE 14
#define BIRD_HEIGHT 20

#define GAME_SPEED 4

/******************************************************************************
* Enum
*******************************************************************************/
enum Type {CACTUS, BIRD};
enum Action {NONE, GOING_UP, GOING_DOWN};

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct Rhino{
    int x;
    int y;
    enum Action action;
} Rhino;

typedef struct Obstacle{
    int x;
    int y;
    enum Type type;
} Obstacle;

int prova;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
// [FUNCTIONS]
// init functions
void initRhino(Rhino* rhinoPtr, int* counterRhinoPtr); // initializes the rhino
void initObstacle(Obstacle* obstaclePtr, int distance); // initializes an obstacle
// moving/updating functions
void updateRhino(Rhino* rhinoPtr, int* counterRhinoPtr); // updates rhino position
void updateObstacle(Obstacle* obstaclePtr); // updates an obstacle
// bool functions
bool checkIfObstacleEnds(Obstacle obstacle); // checks if an obstacle has reached the end of the screen
bool checkYCollision(Rhino rhino, Obstacle obstacle); // checks if the rhino collides vertically with an obstacle
bool checkRhinoCollision(Rhino rhino, Obstacle obstacle); // checks if the rhino collides with an obstacle
// draw functions
void drawRhinoBackground(); // draws the background
void drawRhino(Rhino rhino); // draws rhino
void clearRhino(Rhino rhino); // clears rhino
void drawObstacle(Obstacle obstacle); // draws an obstacle
void clearObstacle(Obstacle obstacle); // clears an obstacle
// run function
void runRhino(); // runs the Rhino game


#endif /* CODE_GAMES_RHINORUNNER_H_ */

/*** End of File **************************************************************/
