//Matteo Piras

#ifndef BATTAGLIA_NAVALE_GAME_H
#define BATTAGLIA_NAVALE_GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include "../headers/coords.h"

namespace game {
    class matrix {
    private:
        char _matrix[12][12] = {};
        //exception
        class invalidChar : std::exception {};
    public:
        matrix();
        //insert
        void insert(coords, char);
        //getters
        char* getRow(int);
        char getElement(coords);
        char getElement(int row, int col);
        //setters
        bool setElement(char, int, int);
        void hit(coords target);
        void restore(coords target);
        bool isEmpty(coords target);      //true se è vuoto
    };

    //FUNZIONI RANDOM
    coords getRandomCoord();
    coords getRandomCoord(coords coord, bool vertical = false, int distance = 1); //prende in input la PRUA!
    int getRandomInt(int range = 11, int start = 0);

    //FUNZIONI DI SUPPORTO
    //visualisation
    void visual();
    //void grid(std::vector<std::pair<coords, coords>>);
    void grid(game::matrix ships, game::matrix attack);
    std::vector<std::pair<coords, coords>> read_file();
    bool write_file();          //da vedere cosa prende in input
};


#endif //BATTAGLIA_NAVALE_GAME_H
