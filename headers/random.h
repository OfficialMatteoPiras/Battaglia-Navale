// Matteo Piras

#ifndef BATTAGLIA_NAVALE_RANDOM_H
#define BATTAGLIA_NAVALE_RANDOM_H

#include "../headers/coords.h"

namespace _random {
    coords getRandomCoord();
    coords getRandomCoord(const coords& coord, bool vertical = false, int distance = 1); //prende in input la PRUA!
    int getRandomInt(int range = 11, int start = 0);
};


#endif //BATTAGLIA_NAVALE_RANDOM_H