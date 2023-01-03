// Created by Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_PLAYER_H
#define BATTAGLIA_NAVALE_PLAYER_H

#include "../headers/coords.h"
#include "../headers/game.h"
#include "../headers/ship.h"

#include <map>
#include <vector>


class player{
    private:
        game::matrix defence;    //griglia difesa (navi)
        game::matrix attack;     //griglia attacco
        //std::vector<std::pair<coords, ship*>> fleet;  //mappa per la flotta
        std::map<coords, ship*> fleet;  //mappa per la flotta

        //exceptions
        class invalidCoords : std::exception {};

        //istanze per ship
        battleship getIstanceBattleship(coords bow, coords stern) { return *new battleship(bow, stern); };
        support getIstanceSupport(coords bow, coords stern){ return *new support(bow, stern); };
        submarine getIstanceSubmarine(coords bow, coords stern){ return *new submarine(bow, stern); };

        //membri privati
        std::pair<coords, coords> getCoords(const std::string& message);

    public:
        //Constructors
        explicit player();       //costruttore che inizializza tutta la flotta

        //inizializzazione flotta flotta
        void startFleet();

        //Getters
        //ship getPlayerShip(coords coordsShip);     //getter di una nave date le sue coordinate
        //coords getShipCoords(ship playerShip);      //getter delle coordinate di una nave

        //Setters

        void visual(){
            game::grid(defence, attack);
        }
};


/*
class player {
    public:
        void placeShip(ship, coords, coords);   //aggiunge in defense, aggiorna myShips
        void actionAAAA();      //chiama una funzione di matrix che cancella tutte le Y da attack
        void action(coords origin, coords target, player opponent);      //check origin in fleet, chiama fleet[origin].value.action(target, attack, defense, p.defense), aggiorna fleet se è S o E

    private:
        game::matrix defense;
        game::matrix attack;
        std::map<ship, coords> fleet;   //mappa per le navi
        int aliveUnits = 8;
};*/

#endif //BATTAGLIA_NAVALE_PLAYER_H
