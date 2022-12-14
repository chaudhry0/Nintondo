#ifndef CODE_GAMES_SUPERDARIO_H_
#define CODE_GAMES_SUPERDARIO_H_

#include "Code/Utilities/init.h"

#define DARIO_HEIGH 16
#define DARIO_WIDTH 8
#define DIRT_HEIGH 8
#define DARIO_SPEED 4
#define MAX_BRICK 5
#define BRICKS_HEIGTH 68

enum XDirection {L, R, xSTOPPED};
enum YDirection {U, D, ySTOPPED};

typedef struct Dario{
    int x;
    int y;
    enum XDirection xDirection;
    enum YDirection yDirection;
} Dario;

typedef struct Brick{
    int x;
    int y;
    int counterToSpawn;
} Brick;

int lastX;
int lastY;

Brick bricks[MAX_BRICK];
bool canMove;

void initBricks();
bool checkBrickCollision(Dario dario, int* index);
bool checkBrickLateralCollision(Dario dario);
void updateDario(Dario* darioPtr);
void drawDario(Dario dario);
void drawBricks();
int getXDifference(Dario dario);
void clearDario(Dario dario);
void drawDarioBackground();
void runSuperDario();

#endif /* CODE_GAMES_SUPERDARIO_H_ */
