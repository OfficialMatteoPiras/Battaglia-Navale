// Matteo Piras

#include "../headers/replayPlayer.h"

void replayPlayer::startReplayFleet(const std::vector<std::pair<coords, coords>>& _vector) {
    char ch;
    int dim;

    for (const auto & i : _vector) {
        dim = i.first - i.second + 1;       //trova la dimensione della nave letta
        if(dim < 0) dim *= (-1);
        if(dim == 5) ch = 'C';
        if(dim == 3) ch = 'S';
        if(dim == 1) ch = 'E';
        ship *s = newShip(i.first, i.second, ch);  //crea la nave e la inserisce
        insertShip(*s, ch);      //inserisce la nave nella griglia di difesa
    }
}

void replayPlayer::makeMove(player& pl, player& opponent, std::pair<coords, coords> move) {
    pl.action(move.first, move.second, opponent, true);      //coordinate random
}