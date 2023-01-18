// Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_GAME_H
#define BATTAGLIA_NAVALE_GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <unistd.h>
#include "../headers/coords.h"
#include "../headers/ship.h"
#include "../headers/matrix.h"
#include "../headers/random.h"
#include "../headers/player.h"

namespace game {
    //menu iniziale per scegliere se iniziare una partita, leggere le regole del gioco o uscire
    void start_menu();

    //esegue un turno di un giocatore non umano scegliendo coordinate casuali per origine e target, poi restituite
    std::pair<std::string, std::string> computerRound(player& pl, player& opponent);

    //esegue un turno di un giocatore umano tramite input e output delle coordinate di origine e target, poi restituite
    std::pair<std::string, std::string> humanRound(player& pl, player& opponent);

    //inizializza i giocatori
    void create_players(bool human, player &p1, player &p2);

    //esegue una partita inizializzando i giocatori, le loro flotte e alternando i turni
    void start_game(bool human);

    //stampa le griglie di entrambi i giocatori (chiamata dopo aver posizionato tutte le navi)
    void print(player& p1, player& p2, bool human);

    //scrive su file i dati necessari per eseguire il replay della partita
    void write_game(const std::string &out_file, bool startPlayer, std::string name1, std::string name2, std::vector<std::pair<coords, coords>>& vector);      //funzione per la scrittura della partita
};


#endif //BATTAGLIA_NAVALE_GAME_H
