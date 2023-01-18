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
    //costruttore
    matrix();

    //insert
    void insert(coords, char);      //inserische un carattere nella matrice

    //getters
    char getElement(coords) const;      //restituisce un elemento date le sue coordinate
    char getElement(int row, int col) const;    //overload: restituisce un elemento data riga e colonna
    bool isEmpty(coords target) const;      //date le coordinate, restituisce se la cella è ha un elemento o meno (vuota o piena)
    int getShipDim(coords c) const;     //restituisce la dimensione della nave nelle coordinate c (in base alla lettera)
    std::vector<coords> findLetter(char letter) const;      //funzione che data una lettara restituisce un vettore con le tutte le coordinate in cui è stata trovata nella matrice

    //setters
    void hit(coords target);                //setta la lettara nelle coordinate date in minuscolo
    void restore(coords target);            //setta la lettara nelle coordinate date in maiuscolo
};

//stampa due matrici affiancate
void grid(matrix ships, matrix attack);             //stampa delle griglie affiancate

#endif //BATTAGLIA_NAVALE_MATRIX_H
