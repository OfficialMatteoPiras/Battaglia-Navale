// Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_COORDS_H
#define BATTAGLIA_NAVALE_COORDS_H

#include <string>
#include <iostream>
#include <exception>

class coords{
    public:
        //CONSTRUCTORS
        coords(int r, int c);       //costruisce dalle coordinate della matrice (range 0-11)
        coords(std::string);        //esempio: legge "B10" e inizializza con x=1, y=9
        coords() : x{0}, y{0} {};

        //GETTERS
        //matrix coordinates
        int getX() const { return x; }    //riga della matrice (0-11)
        int getY() const { return y; }    //colonna della matrice (0-11)
        //grid coordinates
        char getRow() const { return rowToChar(x); }  //riga della griglia (A-N)
        int getCol() const { return y+1; }   //colonna della griglia (1-12)

        //ADD
        coords add(int r, int c) const;
        coords addRow(int n) const;
        coords addCol(int n) const;

        //converte coords in std::string
        std::string toString() const;

        //OVERLOAD OPERATORI
        bool operator==(const coords&) const;
        bool operator!=(const coords&) const;
        bool operator<(const coords&) const;
        bool operator>(const coords&) const;
        bool operator>=(const coords&) const;
        bool operator<=(const coords&) const;
        int operator-(const coords&) const;     //valido solo per coords con stessa riga o colonna (altrimenti lancia eccezione)

        //EXCEPTION
        class invalidCoords : std::exception {};

    private:
        int x;  //riga della matrice (0-11)
        int y;  //colonna della matrice (0-11)

        //conversione riga da int a char
        static char rowToChar(int r);
        //conversione riga da char a int
        static int rowToInt(char r);

};

//OPERATOR <<
std::ostream& operator<< (std::ostream& os, const coords& c);


#endif //BATTAGLIA_NAVALE_COORDS_H
