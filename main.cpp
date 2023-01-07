#include "headers/ship.h"
#include "headers/player.h"
#include "headers/game.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

void print(player p1, player p2){
    std::string token = " ------------------------------------- ";
    std::string n1 = p1.getName();
    std::string n2 = p2.getName();
    std::cout <<std::endl << token << n1 << token << std::endl;
    p1.visual();
    std::cout << "FLOTTA: " << std::endl;
    for(auto& iter: p1.fleet) {
        coords c = iter.first;
        std::cout << c << ": " << *iter.second << std::endl;
    }

    sleep(1);
    std::cout <<std::endl << token << n2 << token << std::endl;
    p2.visual();
    std::cout << "FLOTTA: " << std::endl;
    for(auto& iter: p2.fleet) {
        coords c = iter.first;
        std::cout << c << ": " << *iter.second << std::endl;
    }
    std::cout << std::endl;
    sleep(1);
}

void startGame(){
    bool human = false;
    //settare human

    const int maxRounds = 40;       //bisogna farlo settare al giocatore?
    std::string origin;
    std::string target;

    //creare giocatori p1 e p2
    player p1, p2;      //p1 sempre computer
    if(human){
        std::cout << "Inserisci il tuo nome!" << std::endl;
        std::string name;
        std::cin >> name;
        p2.setName(name);
        p1.setName("Computer");
    }
    else{
        p1.setName("Giocatore 1");
        p2.setName("Giocatore 2");
    }

    //vettore log per salvare tutte le mosse (bool, coords, coords) | (player1, origin, target)
    std::vector<std::tuple<bool, std::string, std::string>> log;

    //posizionare navi p1 random
    p1.startRandomFleet();



    //posizionare navi p2 (A random | B cout/cin)
    if(human){
        p2.startFleet();
    }
    else {
        p2.startRandomFleet();
    }

    print(p1, p2);

    //sorteggio primo giocatore: p1: roundP1 = true, p2: roundP1 = false        //(p1 = 1, p2 = 0)
    bool roundP1 = false;
    if (rand()%2 == 1)
        roundP1 = true;
    std::cout << "\nINIZIA IL GIOCATORE: ";
    if(roundP1)
        std::cout << p1.getName() << std::endl;
    else
        std::cout << p2.getName() << std::endl;

    std::string prova = "Ciao";

    //turni
    for (int i = 0; i < maxRounds && p1.isAlive() && p2.isAlive(); i++){
        std::pair<std::string, std::string> move;
        if(roundP1) {     //round P1 (computer)
            std::cout << "TURNO " << i+1 << ":  TOCCA A " << p1.getName() << std::endl;
            move =  game::computerRound(p1, p2);
        }
        else{              //round P2
            std::cout << "TURNO " << i+1 << ":  TOCCA A " << p2.getName() << std::endl;
            if(human){

                move = game::humanRound(p2, p1);
            }
            else {
                move = game::computerRound(p2, p1);
            }
        }
        if(origin != "AA" && origin != "XX") {
            origin = move.first;
            target = move.second;
            log.emplace_back(roundP1, origin, target);
            //cout << origin << " -> " << target << endl;
            //cout << std::get<0>(log[i]) << " " << std::get<1>(log[i]) << " " << std::get<2>(log[i]);

            roundP1 = !roundP1;
        }
        print(p1, p2);
    }

    for(auto& iter: log){
        std::cout << std::get<0>(iter) << " " << std::get<1>(iter) << " " << std::get<2>(iter);
        std::cout << std::endl;
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
        //PAREGGIO
        //punti?
    }
}



//ESEGUIBILE con argomenti (pcpc | pcumano)
int main(){
    srand(time(0));

    //startGame();
    std::vector<std::pair<coords, coords>> vect1 {
            {{"A1"}, {"A5"}},
            {{"B1"}, {"B5"}},
            {{"C1"}, {"C5"}},    //CORAZZATA
            {{"D1"}, {"D3"}},
            {{"E1"}, {"E3"}},
            {{"F1"}, {"F3"}},    //SUPPORTO
            {{"G1"}, {"G1"}},
            {{"H1"}, {"H1"}},    //SOTTOMARINO
    };
    std::vector<std::pair<coords, coords>> vect2 {
            {{"A1"}, {"E1"}},
            {{"A2"}, {"E2"}},
            {{"A3"}, {"E3"}},    //CORAZZATA
            {{"A4"}, {"C4"}},
            {{"A5"}, {"C5"}},
            {{"A6"}, {"C6"}},    //SUPPORTO
            {{"A7"}, {"A7"}},
            {{"A8"}, {"A8"}},    //SOTTOMARINO
    };

    player pl1;
    pl1.startReplayFleet(vect1);
    pl1.visual();

    std::cout << " ---------------------  " << std::endl;

    player pl2;
    pl2.startReplayFleet(vect2);
    pl2.visual();

    return 0;
}

