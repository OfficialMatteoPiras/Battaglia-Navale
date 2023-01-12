// Created by Claudia De Carlo

#include "../headers/coords.h"

//CONSTRUCTORS
coords::coords(int r, int c){
    if(r < 0 || r > 11 || c < 0 || c > 11)
        throw invalidCoords();
    x = r;      // x = row
    y = c;      // y = column
}

coords::coords(std::string s){  //"XY" ("riga-colonna")
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
    x = r;      // x = row
    y = c;      // y = column
}


//ADD
coords coords::addRow (int n) const {
    return coords(x+n, y);
}

coords coords::addCol(int n) const {
    return coords(x, y+n);
}

coords coords::add(int r, int c) const {
    return coords(x+r, y+c);
}

//COORDS TO STRING
std::string coords::toString() const{
    std::string s;
    s += getRow() + std::to_string(getCol());
    return s;
}

//OVERLOAD ==, <, >
bool coords::operator==(const coords& c) const{
    return ((x == c.getX())&&(y == c.getY()));
}

bool coords::operator<(const coords& c) const{
    if(x == c.getX())
        return y < c.getY();
    return x < c.getX();
}

bool coords::operator>(const coords& c) const{
    if(x == c.getX())
        return y > c.getY();
    return x > c.getX();
}

bool coords::operator>=(const coords& c) const{
    return !(operator<(c));
}

bool coords::operator<=(const coords& c) const{
    return !(operator>(c));
}

bool coords::operator!=(const coords& c) const {
    return !(operator==(c));
}

int coords::operator-(const coords &c) const {
    int n;
    if(c.getY() == y)       //se è verticale ho y uguali
        n = c.getX() - x;
    else if(c.getX() == x)      //se è orizzontale ho x uguali
        n = c.getY() - y;
    else
        throw invalidCoords();

    if(n < 0) n*= (-1);

    return n;
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
std::ostream& operator<< (std::ostream& os, coords& c){
    return os << c.toString();
}