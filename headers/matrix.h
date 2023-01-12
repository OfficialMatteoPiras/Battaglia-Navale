//Matteo Piras

#ifndef BATTAGLIA_NAVALE_MATRIX_H
#define BATTAGLIA_NAVALE_MATRIX_H

#include <iostream>
#include <vector>
#include "../headers/coords.h"

class matrix {
private:
    char _matrix[12][12] = {};

public:
    matrix();

    //insert
    void insert(coords, char);

    //getters
    char getElement(coords) const;
    char getElement(int row, int col) const;
    bool isEmpty(coords target) const;
    int getShipDim(coords c) const;     //restituisce la dimensione della nave nelle coordinate c (in base alla lettera)
    std::vector<coords> findLetter(char letter) const;

    //setters
    void hit(coords target);
    void restore(coords target);
};

//stampa due matrici affiancate
void grid(matrix ships, matrix attack);

#endif //BATTAGLIA_NAVALE_MATRIX_H
