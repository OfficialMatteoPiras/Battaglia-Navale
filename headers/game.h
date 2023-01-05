//Matteo Piras

#ifndef BATTAGLIA_NAVALE_GAME_H
#define BATTAGLIA_NAVALE_GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <map>
#include <functional>
#include <cstdlib>

#include "../headers/coords.h"
#include "../headers/matrix.h"
//#include "../headers/player.h"

namespace game {
    class turn{
        private:
            int MAX_TURN;   //turni massimi
            std::map<coords, coords> history;   //storia delle mosse
        public:
            turn();
    };

    //FUNZIONI RANDOM
    coords getRandomCoord();
    coords getRandomCoord(coords coord, bool vertical = false, int distance = 1); //prende in input la PRUA!
    int getRandomInt(int range = 11, int start = 0);

    //FUNZIONI DI SUPPORTO
    //void grid(std::vector<std::pair<coords, coords>>);
    void grid(matrix ships, matrix attack);
    std::vector<std::pair<coords, coords>> read_file();
    bool write_file();          //da vedere cosa prende in input
};


#endif //BATTAGLIA_NAVALE_GAME_H
