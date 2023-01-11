//Matteo Piras

#include "headers/replayPlayer.h"

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
        //std::cout << s << std::endl;        //todo: rimuovere
        //std::cout << fleet.find(s.getCenter())->first.getRow()<< fleet.find(s.getCenter())->first.getCol() << "\t " << fleet.find(s.getCenter())->second << std::endl;        //todo: rimuovere
    }

    /*unsigned int dim = 0;
    char ch = 'C';
    coords bow{}, stern{} , temp{};

    /*for (const auto & i : ship_vector) {
        bow = i.first;
        stern = i.second;
        if(bow < stern){
            temp = bow;
            bow = stern;
            stern = temp;
        }

        dim = stern - bow + 1;

        if(dim < 0) dim*= (-1);

        if(dim == 5) ch = 'C';
        if(dim == 3) ch = 'S';
        if(dim == 1) ch = 'E';



        try{
            ship *s = newShip(stern, bow, ch);
            insertShip(*s, ch);
        }catch(coords::invalidCoords){
            std::cout << "** invalid coords **" << std::endl;
        }

    }
    for (int i = 0; i < ship_vector.size(); i++) {
        bow = ship_vector[i].first;
        stern = ship_vector[i].second;

        dim = stern - bow + 1;

        if(dim < 0) dim*= (-1);

        if(dim == 5) ch = 'C';
        if(dim == 3) ch = 'S';
        if(dim == 1) ch = 'E';

        try{
            ship *s = newShip(stern, bow, ch);
            insertShip(*s, ch);
        }catch(coords::invalidCoords){
            std::cout << "** invalid coords **" << std::endl;
        }
        if(i < ship_vector.size())
            dim = ship_vector[i + 1].second - ship_vector[i + 1].first + 1;

        if(dim < 0) dim*= (-1);

        if(dim == 5) ch = 'C';
        if(dim == 3) ch = 'S';
        if(dim == 1) ch = 'E';


    }*/
}

void replayPlayer::makeMove(player& pl, player& opponent, std::pair<coords, coords> move) {
    pl.action(move.first, move.second, opponent);      //coordinate random
}

