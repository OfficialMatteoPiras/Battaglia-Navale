//Matteo Piras

#include "headers/matrix.h"


matrix::matrix(){
    for(int i = 0; i<12; i++){
        for(int j = 0; j<12; j++){
            _matrix[i][j] = ' ';
        }
    }
}

void matrix::insert(coords coord, char c) {
    _matrix[coord.getX()][coord.getY()] = c;
}

char* matrix::getRow(int r){
    return _matrix[r];
}

char matrix::getElement(coords c) {
    return _matrix[c.getX()][c.getY()];
}
char matrix::getElement(int row, int col) {
    return _matrix[row][col];
}

int matrix::getShipDim(coords c){
    char letter = getElement(c);
    int dim;
    if (letter == 'c' || letter == 'C')
        dim = 5;
    else if (letter == 's' || letter == 'S')
        dim = 3;
    else if (letter == 'e' || letter == 'E')
        dim = 1;
    else
        dim = 0;
    return dim;
}

void matrix::hit(coords target){
    int x = target.getX();
    int y = target.getY();
    _matrix[x][y] = char(tolower(_matrix[x][y]));
}

void matrix::restore(coords target){
    int x = target.getX();
    int y = target.getY();
    _matrix[x][y] = char(toupper(_matrix[x][y]));
}

bool matrix::isEmpty(coords target){
    return _matrix[target.getX()][target.getY()] == ' ';
}

bool matrix::setElement(char c, int row, int col){
    std::string letters = "ABCDEFGHILMN";
    if(letters.find(toupper(c)) < 0) throw invalidChar();    //se non trova il carattere inserito nella lista
    _matrix[row][col] = c;
    return true;
}