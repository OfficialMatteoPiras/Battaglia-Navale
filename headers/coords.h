// Created by Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_COORDS_H
#define BATTAGLIA_NAVALE_COORDS_H

#include <string>
#include <iostream>
#include <exception>

class coords {
    public:
        //CONSTRUCTORS
        coords(int r, int c);       //costruisce dalle coordinate della matrice (0-12)
        coords(std::string);        //legge "B10" e inizializza con y=1, x=9

        //GETTERS
        //matrix coordinates
        int getX() const { return x; }    //colonna della matrice (0-11)
        int getY() const { return y; }    //riga della matrice (0-11)

        //grid coordinates
        char getRow() const { return rowToChar(y); }  //riga della griglia (A-N)
        int getCol() const { return x+1; }   //colonna della griglia (1-12)

        coords addRow(int n);
        coords addCol(int n);

    private:
        int x;  //riga della matrice (0-11)
        int y;  //colonna della matrice (0-11)

        //ROW TYPES CONVERSIONS
        static char rowToChar(int r);
        static int rowToInt(char r);

        //EXCEPTION
        class invalidCoords : std::exception {};
};

//OPERATOR << (stampa come "B10")
std::ostream& operator<< (std::ostream& os, const coords& c);


#endif //BATTAGLIA_NAVALE_COORDS_H
