#include "Code/Menu/gameHub.h"

void main(void) {
    _hwInit();

    drawLogo();
    while(1){
        runGameHub();
    }
}
