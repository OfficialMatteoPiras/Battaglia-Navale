//Matteo Piras

#include "headers/game.h"
#include "headers/replay.h"

#include <iostream>

std::string getExeName(std::string path){
    std::string delimiter = "\\", str_exe = ".", token;
    //ricavo il nome.exe (se presente l'estenezione)
    //int pos = path.find(delimiter);
    int pos = 0;

    //cancello il percorso
    while ((pos = path.find(delimiter)) != std::string::npos) {
        path.erase(0, pos + delimiter.length());
    }

    //cancello i caratteri speciali dell'esecuzione
    delimiter = "./";
    while ((pos = path.find(delimiter)) != std::string::npos) {
        path.erase(0, pos + delimiter.length());
    }

    //cancello se presente l'estensione
    if(path.find(str_exe)){     //se trova '.' è presente l'estensione, quindi la rimuovo
        path.erase(  path.find(str_exe), path.size() - 1);
    }

    //std::cout << path << std::endl;

    return path;
}


//ESEGUIBILE con argomenti (pcpc | pcumano)
int main(int argc, char **argv){
    srand(time(0));

    //eliminazione
    std::string name = getExeName(argv[0]);

    //switch
    if(name == "battaglia_navale"){  //PARTITA
        if(strcmp(argv[1], "pc") == 0 ){            //!segmentation fault -> sistemare
            game::start_game(true);
        }
        else if(strcmp(argv[1], "cc") == 0 ){
            game::start_game(false);
        }
        else{
            std::cout << "**** PARAMETRI INVALIDI ****" << std::endl;
        }
    }
    else    //REPLAY
        if(name == "replay"){
            replay rep;
            if(strcmp(argv[1], "v") == 0){
                rep.replay_main('v', argv[2]);
            }
            else{
                if(strcmp(argv[1], "f") == 0 ){
                    rep.replay_main('f', argv[2], argv[3]);
                }
                else{
                    std::cout << "**** PARAMETRI INVALIDI ****" << std::endl;
                }

            }
        }


    return 0;
}

