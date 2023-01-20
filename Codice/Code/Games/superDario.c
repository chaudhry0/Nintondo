#include "superDario.h"
#include "Code/Images/superDarioImages.h"

void initBricks(){
    int i;
    for (i=0; i<MAX_BRICK; i++){
        bricks[i].x = random(0, 15) * CELL_SIZE_SMALL + 1;
        bricks[i].y = BRICKS_HEIGTH;
    }
}

bool checkBrickCollision(Dario dario, int* index){
    int i;
    for (i=0; i<MAX_BRICK; i++){
        if ((dario.x + DARIO_WIDTH >= bricks[i].x &&
             bricks[i].x + CELL_SIZE_SMALL > dario.x) &&
            (dario.y <= bricks[i].y + CELL_SIZE_SMALL - 4)){
            *index = i;
            return true;
        }
    }
    return false;
}

bool checkBrickLateralCollision(Dario dario){
    int i;
    for (i=0; i<MAX_BRICK; i++){
        if ((dario.x + DARIO_WIDTH >= bricks[i].x &&
             bricks[i].x + CELL_SIZE_SMALL > dario.x) &&
            (dario.y < bricks[i].y + CELL_SIZE_SMALL)){
            return true;
        }
    }
    return false;
}

void updateDario(Dario* darioPtr){
    if (canMove == true){
    switch(direction){
        case 1:
            darioPtr->xDirection = xSTOPPED;
            break;
        case 2:
            if (!checkBrickLateralCollision(*darioPtr)){
                darioPtr->x += DARIO_SPEED;
            } else{
                canMove = false;
            }
            if (darioPtr->x > 127 + DARIO_SPEED){
                darioPtr->x = 0 - DARIO_WIDTH;
            }
            darioPtr->xDirection = R;
            break;
        case 3:
            darioPtr->xDirection = xSTOPPED;
            break;
        case 4:
            if (!checkBrickLateralCollision(*darioPtr)){
                darioPtr->x -= DARIO_SPEED;
            } else{
                canMove = false;
            }
            darioPtr->xDirection = L;
            if (darioPtr->x < 0 - DARIO_WIDTH - DARIO_SPEED){
                darioPtr->x = 127 - DARIO_WIDTH;
            }
            break;
        default:
            break;
        }
    }
    if (getButtons() == 1 && darioPtr->y == MAX_HEIGHT + DIRT_HEIGH - DARIO_HEIGH){
        darioPtr->yDirection = U;
    }
    if (darioPtr->yDirection == U){
        if (darioPtr->y >= MAX_HEIGHT + DIRT_HEIGH - DARIO_HEIGH - JUMP_ITERS * DARIO_SPEED){
            darioPtr->y -= DARIO_SPEED;
        } else{
            darioPtr->yDirection = D;
        }
    }
    if (darioPtr->yDirection == D){
        if (darioPtr->y <= MAX_HEIGHT + DIRT_HEIGH - DARIO_HEIGH - 4){
            darioPtr->y += DARIO_SPEED;
        } else{
            darioPtr->yDirection = ySTOPPED;
            canMove = true;
        }
    }
    int index;
    if (checkBrickCollision(*darioPtr, &index) && canMove == 1){
        drawRect(bricks[index].x, bricks[index].x + CELL_SIZE_SMALL - 1, bricks[index].y + CELL_SIZE_SMALL - 1, bricks[index].y, 0xff0000);
        darioPtr->y += DARIO_SPEED;
        darioPtr->yDirection = D;
    }

}

void drawDarioBackground(){
    Graphics_drawImage(&g_sContext, &imageDarioBackground, 0, CELL_SIZE_LARGE);
}

void drawDario(Dario dario){
    Graphics_drawImage(&g_sContext, &imageDario, dario.x, dario.y);
}

void drawBricks(){
    int i;
    for (i=0; i<MAX_BRICK; i++){
        Graphics_drawImage(&g_sContext, &imageDarioBrick, bricks[i].x, bricks[i].y);
    }
}


int getXDifference(Dario dario){
   int speed = 0;
   switch(dario.xDirection){
       case R:
           speed = -DARIO_SPEED;
           break;
       case L:
           speed = DARIO_SPEED;
           break;
       case xSTOPPED:
           speed = 0;
           break;
   }
   return speed;
}

void clearDario(Dario dario){
    switch(dario.xDirection){
        case R:
            drawRect(dario.x - DARIO_SPEED, dario.x - 1, dario.y + DARIO_HEIGH - 1, dario.y, 0x3e8eff);
            break;
        case L:
            drawRect(dario.x + DARIO_WIDTH, dario.x + DARIO_WIDTH + DARIO_SPEED, dario.y + DARIO_HEIGH - 1, dario.y, 0x3e8eff);
            break;
        case xSTOPPED:
            break;
        default:
            break;
    }
    if (dario.yDirection == U){
        drawRect(dario.x - DARIO_SPEED, dario.x + DARIO_WIDTH + DARIO_SPEED, dario.y + DARIO_HEIGH + DARIO_SPEED - 1, dario.y + DARIO_HEIGH - 1, 0x3e8eff);
    }
    if (dario.yDirection == D){
        drawRect(dario.x - DARIO_SPEED, dario.x + DARIO_WIDTH + DARIO_SPEED, dario.y - DARIO_SPEED, dario.y - 1, 0x3e8eff);

    }
}

void runSuperDario(){
    Dario dario;
    dario.x = 16;
    dario.y = MAX_HEIGHT - DIRT_HEIGH;
    dario.xDirection = xSTOPPED;
    dario.yDirection = ySTOPPED;
    canMove = true;
    initBricks();
    drawDarioBackground();
    drawDario(dario);
    drawBricks();

    while(1){
        updateDario(&dario);
        drawDario(dario);
        clearDario(dario);
        wait(10);
        printf("[%d]\n", dario.yDirection);
    }
}
