// Andrea Nalin

#ifndef BATTAGLIA_NAVALE_REPLAYPLAYER_H
#define BATTAGLIA_NAVALE_REPLAYPLAYER_H

#include "../headers/player.h"

class replayPlayer : public player{
public:
    replayPlayer() = default;               //costruttore di default
    explicit replayPlayer(const std::string& name) : player(name){};        //costruttore di della classe che chiama quello di player
    void startReplayFleet(const std::vector<std::pair<coords, coords>>& _vector);    //inizializzazione della flotta
    static void makeMove(player& pl, player& opponent, std::pair<coords, coords> move);     //funzione che fa una mossa di un giocatore
};

#endif //BATTAGLIA_NAVALE_REPLAYPLAYER_H
