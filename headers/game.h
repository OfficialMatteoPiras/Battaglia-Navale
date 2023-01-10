//Matteo Piras

#ifndef BATTAGLIA_NAVALE_GAME_H
#define BATTAGLIA_NAVALE_GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <map>
#include <functional>
#include <cstdlib>
#include <unistd.h>

#include "../headers/coords.h"
#include "../headers/matrix.h"
#include "../headers/player.h"
#include "../headers/ship.h"

namespace game {
    /*class turn{
        private:
            int MAX_TURN;   //turni massimi
            std::map<coords, coords> history;   //storia delle mosse
        public:
            turn();
    };*/

    //FUNZIONI PER I TURNI
    std::pair<std::string, std::string> computerRound(player& pl, player& opponent);
    std::pair<std::string, std::string> humanRound(player& pl, player& opponent);

    //menu iniziale
    void start_menu();
    void start_game(bool human);
    void create_players(bool human, player &p1, player &p2);
    void turns();

    //void start_game(bool human);
    //std::tuple<bool, std::string, std::string> turn(bool human, bool roundP1, player p1, player p2, unsigned int i);      //funzione per un turno
    void print(player p1, player p2);

    //FUNZIONI DI SUPPORTO
    //void grid(std::vector<std::pair<coords, coords>>);

    std::vector<std::pair<coords, coords>> read_file();
    bool write_file();          //da vedere cosa prende in input
};


#endif //BATTAGLIA_NAVALE_GAME_H
