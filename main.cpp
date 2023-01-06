#include "headers/player.h"
#include "headers/ship.h"
#include <iostream>
#include <string.h>

int main(int argc, char **argv){
    srand(time(0));

    /*
    ------ DISTINZIONE DEGLI ESEGUIBILI ------              //todo: testare
    if(strcmp(argv[0], "battaglia_navale") == 0){
        std::cout << "** PARTITA BATTAGLIA NAVALE **" << std::endl;
        if(strcmp(argv[1], "pc") == 0) std::cout << "PARTITA CON GIOCATORE VS COMPUTER" << std::endl;
        if(strcmp(argv[0], "cc") == 0) std::cout << "PARTITA CON COMPUTER VS COMPUTER" << std::endl;
    }
    else{
        if(strcmp(argv[0], "replay") == 0){
            std::cout << "** REPLAY **" << std::endl;
        }
        else{
            std::cout << "** IMPOSSIBILE ESEGUIRE IL PROGRAMMA RICHIESTO | CHIUSURA DEL PROGRAMMA **" << std::endl;
        }
    }
     */


    /*int d = 1;
    for (int i = 0; i < 3; ++i) {

        coords c1 = game::getRandomCoord();
        coords c2 = game::getRandomCoord(c1, false, d);

        std::cout << "c1-> " << c1 << std::endl;
        std::cout << "c2-> " << c2 << std::endl;
        std::cout << " ---------------- "<< std::endl;

        d+=2;
    }*/

    //game::turn();

    player pl1("PANE TOSTATO");
    pl1.startRandomFleet();
    //pl1.startFleet();
    pl1.visual();
    pl1.printFleet();

    return 0;
}

