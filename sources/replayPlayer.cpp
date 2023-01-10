//Matteo Piras

#include "headers/replayPlayer.h"

void replayPlayer::startReplayFleet(const std::vector<std::pair<coords, coords>>& vector) {

    for (const auto & i : vector) {
        ship s {i.first, i.second};
        fleet[s.getCenter()] = &s;
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
