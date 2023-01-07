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

using namespace std;

//ESEGUIBILE con argomenti (pcpc | pcumano)
int main(){
    srand(time(0));
    bool human = false;
    //settare human

    const int maxRounds = 40;       //bisogna farlo settare al giocatore?
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

    //vettore log per salvare tutte le mosse (bool, coords, coords) | (player1, origin, target)
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

    print(p1, p2);

    //sorteggio primo giocatore: p1: roundP1 = true, p2: roundP1 = false        //(p1 = 1, p2 = 0)
    bool roundP1 = false;
    if (rand()%2 == 1)
        roundP1 = true;
    cout << "\nINIZIA IL GIOCATORE: ";
    if(roundP1)
        cout << p1.getName() << endl;
    else
        cout << p2.getName() << endl;

    string prova = "Ciao";

    //turni
    for (int i = 0; i < maxRounds && p1.isAlive() && p2.isAlive(); i++){
        std::pair<std::string, std::string> move;
        if(roundP1) {     //round P1 (computer)
            cout << "TURNO " << i+1 << ":  TOCCA A " << p1.getName() << endl;
            move =  game::computerRound(p1, p2);
        }
        else{              //round P2
            cout << "TURNO " << i+1 << ":  TOCCA A " << p2.getName() << endl;
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
        cout << std::get<0>(iter) << " " << std::get<1>(iter) << " " << std::get<2>(iter);
        cout << endl;
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


    return 0;
}

