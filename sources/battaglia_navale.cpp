//Created by Claudia De Carlo

#include "../headers/player.h"
#include "../headers/ship.h"
#include "../headers/coords.h"
#include "../headers/game.h"
using namespace std;

//ESEGUIBILE con argomenti (A = pcpc | B = pcumano)
/*int main(){

    //FORSE SERVE SRAND(RAND())
    bool human;
    //settare human

    const int maxRounds = 40;
    std::string origin;
    std::string target;

    //creare giocatori p1 e p2
    player p1, p2;      //p1 sempre computer
    if(human){
        cout << "Inserisci il tuo nome!" << endl;
        string name;
        cin >> name;
        p2.setName(name);
        p1.setName("Computer");
    }
    else{
        p1.setName("Giocatore 1");
        p2.setName("Giocatore 2");
    }

    //vettore log per salvare tutte le mosse (bool, coords, coords) | (player, origin, target)
    vector<tuple<bool, std::string, std::string>> log;

    //posizionare navi p1 random
    p1.startRandomFleet();
    //posizionare navi p2 (A random | B cout/cin)
    if(human){
        p2.startFleet();
    }
    else {
        p2.startRandomFleet();
    }

    //sorteggio primo giocatore: p1: roundP1 = true, p2: roundP1 = false        //(p1 = 1, p2 = 0)
    bool roundP1 = false;
    if (rand()%2 == 1)
        roundP1 = true;

    //turni
    for (int i = 0; i < maxRounds && p1.isAlive() && p2.isAlive(); i++){
        std::pair<std::string, std::string> move;
        bool done = false;
        if(roundP1) {     //round P1 (computer)
           move =  game::computerRound(p1, p2);
        }
        else{              //round P2
            if(human){
                move = game::humanRound(p2, p1);
            }
            else {
                move = game::computerRound(p2, p1);
            }
        }
        origin = move.first;
        target = move.second;
        log.push_back(make_tuple(roundP1, origin, target));
        if(origin.compare("AA") != 0 && origin.compare("XX") != 0 )
            !roundP1;
    }
    //FINE PARTITA
        //if p1 è morto
        if(!p1.isAlive()){
            //P1 HA PERSO SFIGATO è MORTO
        }

        //if p2 è morto
        else if(!p2.isAlive()){
            //P2 HA PERSO SFIGATO è MORTO
        }

        //if mosse finite: confronto "punteggi" (unità vive)
        else{
            if(p1.getPoints() > p2.getPoints()){
                //HA VINTO P2 << PUNTI
            }
            else if(p1.getPoints() < p2.getPoints()){
                //HA VINTO P2 << PUNTI
            }
            else{
                //PAREGGIO
            }
        }


    return 0;
}*/