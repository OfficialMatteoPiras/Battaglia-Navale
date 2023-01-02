//! Created by Matteo Piras

#include "../headers/backing.h"
#include <cctype>

void backing::grid(backing::matrix ships, backing::matrix attack) {
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

std::vector<std::pair<coords, coords>> backing::read_file(){        //!DA TESTARE
    std::vector<std::pair<coords, coords>> read_coords;         //vettore per la lettura delle coordinate
    std::ifstream inFile("../file/log.txt");      //apertura del file ("../" serve per cercare in automatico il percorso del file)

    if (!inFile) {      //controllo corretta apertura
        std::cout << "Errore di apertura del file" << std::endl; // controllo
    } else {
        //lettura delle mosse dal file log
        std::string str, start;
        std::string delimiter = " ";

        while (std::getline(inFile, str)){
            //estraggo start
            start = str.substr(0, str.find(delimiter));     //estraggo dalla lettura la mossa di partenza
            str.erase(0, str.find(delimiter) + delimiter.length());     //cancello dalla string la mossa di partenza estrapolando la mossa di destinazione
            coords first (start);       //creo l'oggetto partendo dalla prima stringa
            coords second (str);        //creo l'oggetto partendo dalla seconda stringa
            read_coords.emplace_back(first, second);        //salvo la composizione degli oggetti nell'array
        }
    }

    inFile.close(); //chiusura del collegamento
    return read_coords;
}

bool backing::write_file() {    //!DA FINIRE E VEDERE COSA PRENDE IN INPUT
    std::ofstream outFile; // Dichiarazione di tipo
    bool finish = false;
    //OutFile.open("file.txt", std::ios::app); // Apertura del file con sovrascrittura
    outFile.open("file.txt"); // Apertura del file senza sovrascrittura
    if (!outFile) {
        std::cout << "Errore di apertura del file" << std::endl; // controllo
    } else {
        //codice per la scrittura su file
        //! OutFile << std::endl;       //inserisco nel file (comando per inserimento outFile::)
        finish = true;
    }

    outFile.close();
    return finish;
}

backing::matrix::matrix(){
    for(int i = 0; i<12; i++){
        for(int j = 0; j<12; j++){
            _matrix[i][j] = ' ';
        }
    }
}

void backing::matrix::insert(coords coord, char c) {
    _matrix[coord.getX()][coord.getY()] = c;
}

char* backing::matrix::getRow(int r){
    return _matrix[r];
}

char backing::matrix::getElement(coords c) {
    return _matrix[c.getX()][c.getY()];
}
char backing::matrix::getElement(int row, int col) {
    return _matrix[row][col];
}

void backing::matrix::hit(coords target){
    int x = target.getX();
    int y = target.getY();
    _matrix[x][y] = char(tolower(_matrix[x][y]));
}

void backing::matrix::restore(coords target){
    int x = target.getX();
    int y = target.getY();
    _matrix[x][y] = char(toupper(_matrix[x][y]));
}

bool backing::matrix::isEmpty(coords target){
    return _matrix[target.getX()][target.getY()] == ' ';
}

bool backing::matrix::setElement(char c, int row, int col){
    std::string letters = "ABCDEFGHILMN";
    if(letters.find(toupper(c)) < 0) throw invalidChar();    //se non trova il carattere inserito nella lista
    _matrix[row][col] = c;
    return true;
}















