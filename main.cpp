//Matteo Piras

#include "headers/game.h"
#include "headers/replay.h"

#include <iostream>
#include <cstring>


//ESEGUIBILE con argomenti (pcpc | pcumano)
int main(int argc, char **argv){
    srand(time(0));

    //eliminazione
    std::string name = argv[0];

    if(name.find("battaglia_navale") != std::string::npos ){  //PARTITA
        if(strcmp(argv[1], "pc") == 0 ){
            game::start_menu();     //chiama il menu d'inizio
            //game::start_game(true);
        }
        else if(strcmp(argv[1], "cc") == 0 ){
            game::start_game(false);
        }
        else{
            std::cout << "**** PARAMETRI INVALIDI ****" << std::endl;
        }
    }
    else if (name.find("replay") != std::string::npos ) {         //REPLAY
            replay rep;
            if (strcmp(argv[1], "v") == 0) {
                rep.replay_main('v', argv[2]);
            } else {
                if (strcmp(argv[1], "f") == 0) {
                    rep.replay_main('f', argv[2], argv[3]);
                } else {
                    std::cout << "**** PARAMETRI INVALIDI ****" << std::endl;
                }

            }
        }
    else std::cout << "**** NOME DEL FILE ERRATO *****" << std::endl;


    return 0;
}