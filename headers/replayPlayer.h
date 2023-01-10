//Matteo Piras

#ifndef BATTAGLIA_NAVALE_REPLAYPLAYER_H
#define BATTAGLIA_NAVALE_REPLAYPLAYER_H

#include "player.h"

class replayPlayer : public player{
public:
    replayPlayer() = default;
    void startReplayFleet(const std::vector<std::pair<coords, coords>>& vector);    //inizializzazioned della flotta
};


#endif //BATTAGLIA_NAVALE_REPLAYPLAYER_H
