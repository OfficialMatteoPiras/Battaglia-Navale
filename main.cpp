#include "headers/ship.h"
#include "headers/player.h"
#include <iostream>

int main(int argc, char **argv){
    srand(time(0));
    /*int d = 1;
    for (int i = 0; i < 3; ++i) {

        coords c1 = game::getRandomCoord();
        coords c2 = game::getRandomCoord(c1, false, d);

        std::cout << "c1-> " << c1 << std::endl;
        std::cout << "c2-> " << c2 << std::endl;
        std::cout << " ---------------- "<< std::endl;

        d+=2;
    }*/

    player pl1;
    pl1.startRandomFleet();

    return 0;
}

