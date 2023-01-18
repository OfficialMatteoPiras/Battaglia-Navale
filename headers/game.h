// Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_GAME_H
#define BATTAGLIA_NAVALE_GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
//#include <functional>
//#include <cstdlib>
#include <unistd.h>
#include "../headers/coords.h"
#include "../headers/ship.h"
#include "../headers/matrix.h"
#include "../headers/random.h"
#include "../headers/player.h"

namespace game {
    //FUNZIONI PER I TURNI
    std::pair<std::string, std::string> computerRound(player& pl, player& opponent);
    std::pair<std::string, std::string> humanRound(player& pl, player& opponent);

    //menu iniziale
    void start_menu();
    void start_game(bool human);
    void create_players(bool human, player &p1, player &p2);


    //void start_game(bool human);
    void print(player& p1, player& p2, bool human);
    void write_game(const std::string &out_file, bool startPlayer, std::string name1, std::string name2, std::vector<std::pair<coords, coords>>& vector);      //funzione per la scrittura della partita
};


#endif //BATTAGLIA_NAVALE_GAME_H
