// Created by Claudia De Carlo

#include "../headers/coords.h"

//CONSTRUCTORS
coords::coords(int r, int c){
    if(r < 0 || r > 11 || c < 0 || c > 11)
        throw invalidCoords();
    x = c;
    y = r;
}

coords::coords(std::string s){  //"YX" ("riga-colonna")
    int r, c;
    try {
        r = rowToInt(s[0]);
        s.erase(0,1);
        c = std::stoi(s) - 1;
    } catch (std::invalid_argument& e){
        throw invalidCoords();
    }
    if(r < 0 || r > 11 || c < 0 || c > 11)
        throw invalidCoords();
    x = c;      // x = col
    y = r;      // y = row
}

coords coords::addRow(int n) {
    return coords(x+n, y);
}

coords coords::addCol(int n) {
    return coords(x, y+n);
}

//ROW TYPES CONVERSIONS
char coords::rowToChar(int r) {
    std::string s = "ABCDEFGHILMN";
    return s[r];
}

int coords::rowToInt(char r) {
    std::string s = "ABCDEFGHILMN";
    return s.find(r);
}

//OPERATOR <<
std::ostream& operator<< (std::ostream& os, const coords& c){
    return os << c.getRow() << c.getCol();
}