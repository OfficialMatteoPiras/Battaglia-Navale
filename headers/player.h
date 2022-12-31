// Created by Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_PLAYER_H
#define BATTAGLIA_NAVALE_PLAYER_H

#include "../headers/coords.h"
#include "../headers/backing.h"
#include "../headers/ship.h"

#include <map>




/*
class player {
    public:
        void placeShip(ship, coords, coords);   //aggiunge in defense, aggiorna myShips
        void actionAAAA();      //chiama una funzione di matrix che cancella tutte le Y da attack
        void action(coords origin, coords target, player opponent);      //check origin in fleet, chiama fleet[origin].value.action(target, attack, defense, p.defense), aggiorna fleet se è S o E

    private:
        backing::matrix defense;
        backing::matrix attack;
        std::map<ship, coords> fleet;   //mappa per le navi
        int aliveUnits = 8;
};*/

#endif //BATTAGLIA_NAVALE_PLAYER_H
