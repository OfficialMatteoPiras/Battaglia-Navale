// Matteo Piras

#include "random.h"

coords randomFunction::getRandomCoord(){
    coords c = {getRandomInt(12), getRandomInt(12)};
    return c;
}

coords randomFunction::getRandomCoord(const coords& bow, bool vertical, int distance){ //prende in input la PRUA!
    coords newCoord = coords(bow.getX(), bow.getY());
    distance--;

    //check se sommare o sottrarre
    if(bow.getX() - distance > 0 || bow.getY() - distance > 0) distance *= (-1);

    //modifica della nuova coordinata
    if (vertical) newCoord = newCoord.add(distance, 0);
    else newCoord = newCoord.add(0, distance);

    return newCoord;
}

int randomFunction::getRandomInt(int range, int start){
    srand(rand());
    int random = start + (rand() % range);
    return random;
}

