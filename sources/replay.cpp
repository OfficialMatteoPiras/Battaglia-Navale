//Created by Claudia De Carlo


//MAIN con argomenti (A = schermo | B = file)

//output (schermo | file)
//legge dal file log
//scrive in un vettore log
//ciclo while (scorre il vettore)
//esegue una mossa
//scrive la mossa in output
//chiama XX XX su quel giocatore
//fine partita...

#include "../headers/player.h"
#include "../headers/ship.h"
#include "../headers/coords.h"
#include "../headers/game.h"
#include <fstream>
/*
int main(){
    std::string lines;
    std::ifstream inFile("log.txt");

    while(getline(inFile, lines)){
        std::cout << lines << std::endl;
    }
    inFile.close();
    std::cout << "END";
    return 0;
}*/