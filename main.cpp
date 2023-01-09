#include "headers/game.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>


//ESEGUIBILE con argomenti (pcpc | pcumano)
int main(){
    srand(time(0));

    game::start_game(true);

    //startGame();
    /*player pl1{"Pippo Baudo"}, pl2{"Gianni Morandi"};
    pl1.startRandomFleet();
    pl2.startRandomFleet();
    std::cout << "---- PLAYER 1 ----" << std::endl;
    pl1.printFleet();
    std::cout << "\n---- PLAYER 2 ----" << std::endl;
    pl2.printFleet();
    std::cout << std::endl;
    game::humanRound(pl1, pl2);
    pl2.visual();*/

    //startGame();
   /* std::vector<std::pair<coords, coords>> vect1 {
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
    pl2.visual();*/

    return 0;
}

