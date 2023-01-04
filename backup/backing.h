//! Created by Matteo Piras

#ifndef BATTAGLIA_NAVALE_BACKING_H
#define BATTAGLIA_NAVALE_BACKING_H

#include <iostream>
#include <vector>
#include <fstream>
#include "headers/coords.h"
//boh
namespace backing {
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

    //void grid(std::vector<std::pair<coords, coords>>);
    void grid(backing::matrix ships, backing::matrix attack);
    std::vector<std::pair<coords, coords>> read_file();
    bool write_file();          //da vedere cosa prende in input

}

#endif //BATTAGLIA_NAVALE_BACKING_H