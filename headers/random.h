// Matteo Piras

#ifndef BATTAGLIA_NAVALE_RANDOM_H
#define BATTAGLIA_NAVALE_RANDOM_H

#include "../headers/coords.h"

namespace randomFunction {
    coords getRandomCoord();        //genera delle coordinate casuali
    coords getRandomCoord(const coords& coord, bool vertical = false, int distance = 1);            //genera delle coordinate date la prua della nave, se è in verticale e la dimensione della nave
    int getRandomInt(int range = 11, int start = 0);        //genera un intero random
};


#endif //BATTAGLIA_NAVALE_RANDOM_H