//Matteo Piras

#ifndef BATTAGLIA_NAVALE_MATRIX_H
#define BATTAGLIA_NAVALE_MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include "../headers/coords.h"

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
    int getShipDim(coords c);
    std::vector<coords> findLetter(char letter);


    //setters
    bool setElement(char, int, int);
    void hit(coords target);
    void restore(coords target);
    bool isEmpty(coords target);      //true se è vuoto
};

void grid(matrix ships, matrix attack);

#endif //BATTAGLIA_NAVALE_MATRIX_H
