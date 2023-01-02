// Created by Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_PLAYER_H
#define BATTAGLIA_NAVALE_PLAYER_H

#include "../headers/coords.h"
#include "../headers/game.h"
#include "../headers/ship.h"

#include <map>

class player{
    private:
        game::matrix defence;    //griglia difesa (navi)
        game::matrix attack;     //griglia attacco
        //ship *ships[8];
        //std::vector<ship*> fleet;
        std::map<coords, ship*> fleet;

        //exceptions
        class invalidCoords : std::exception {};

        //membri privati
        std::pair<coords, coords> getCoords(const std::string& message);

    public:
        //Constructors
        explicit player();       //costruttore che inizializza tutta la flotta

        //start flotta
        void startFleet();


        //Getters
        //ship getPlayerShip(coords coordsShip);     //getter di una nave date le sue coordinate
        //coords getShipCoords(ship playerShip);      //getter delle coordinate di una nave

        //Setters

        void visual(){
            game::grid(defence, attack);
        }

        //Distruttore
        ~player() = default;
    /*~player(){
       /* dete *ships;
        delete &fleet;
    }*/
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
