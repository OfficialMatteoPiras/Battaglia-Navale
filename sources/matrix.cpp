// Matteo Piras

#include "../headers/matrix.h"


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

char matrix::getElement(coords c) const{
    return _matrix[c.getX()][c.getY()];
}

char matrix::getElement(int row, int col) const{
    return _matrix[row][col];
}

int matrix::getShipDim(coords c) const{
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

std::vector<coords> matrix::findLetter(char letter) const{
    std::vector<coords> v;
    for(int i = 0; i < 12; i++){
        for (int  j = 0; j < 12; j++){
            coords c(i, j);
            if(getElement(c) == letter)
                v.push_back(c);
        }
    }
    return v;
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

bool matrix::isEmpty(coords target) const{
    return _matrix[target.getX()][target.getY()] == ' ';
}

//stampa due matrici affiancate
void grid(matrix ships, matrix attack) {
    std::string letters = "ABCDEFGHILMN";
    std::string token;

    for (int i = 0; i < 13; i++) {
        for (int k = 0; k < 2; ++k) {
            for (int j = 0; j < 13; j++) {
                token = "";
                if(i == 0){                     // prima riga stampa i numeri
                    if(j == 0) token = "  |";       //se è la prima riga e la prima ripetizione deve stampare uno spazio
                    else{
                        if(j < 10) token = " " + std::to_string(j ) + " |";  //se il numero occupa un solo carattere
                        else token = std::to_string(j ) + " |";         //se il numero occupa 2 caratteri
                    }
                }
                else{
                    if (j == 0) std::cout << letters[i - 1] << " |";        //stampa della lettera
                    else{
                        token = " ";
                        if(k == 0) {    //! griglia 1
                            token += ships.getElement(i - 1, j - 1);
                        }
                        else { //! griglia 2
                            token += attack.getElement(i - 1, j - 1);
                        }
                        token += " |";
                    }
                }
                std::cout << token;
            }
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}