//Matteo Piras

#ifndef BATTAGLIA_NAVALE_REPLAYPLAYER_H
#define BATTAGLIA_NAVALE_REPLAYPLAYER_H

#include "player.h"

class replayPlayer : public player{
public:
    replayPlayer() = default;
    explicit replayPlayer(const std::string& name) : player(name){};
    void startReplayFleet(const std::vector<std::pair<coords, coords>>& _vector);    //inizializzazioned della flotta
    static void makeMove(player& pl, player& opponent, std::pair<coords, coords> move);
};


#endif //BATTAGLIA_NAVALE_REPLAYPLAYER_H
