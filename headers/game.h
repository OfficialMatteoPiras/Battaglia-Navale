//Matteo Piras

#ifndef BATTAGLIA_NAVALE_GAME_H
#define BATTAGLIA_NAVALE_GAME_H

#include "../headers/coords.h"
#include <vector>

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

    //visualisation
    void visual();
    //void grid(std::vector<std::pair<coords, coords>>);
    void grid(game::matrix ships, game::matrix attack);
    std::vector<std::pair<coords, coords>> read_file();
    bool write_file();          //da vedere cosa prende in input

};


#endif //BATTAGLIA_NAVALE_GAME_H
