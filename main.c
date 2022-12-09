#include <Code/Games/gameHub.h>


void main(void) {
    _hwInit();

    drawLogo();
    while(1){
        //PCM_gotoLPM0();
        runMenu();
    }
}
