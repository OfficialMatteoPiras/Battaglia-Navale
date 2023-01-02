// Created by Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_PLAYER_H
#define BATTAGLIA_NAVALE_PLAYER_H

#include "../headers/coords.h"
#include "../headers/backing.h"
#include "../headers/ship.h"

#include <map>

class player{
    private:
        backing::matrix defence;    //griglia difesa (navi)
        backing::matrix attack;     //griglia attacco
        ship *ships[8];
        //vettori per le navi
        /*std::vector<submarine> battleship;
        std::vector<submarine> support;
        std::vector<submarine> submarine;
*/

        //std::vector<ship> fleet;    //vettore con tutte le navi

        static std::string getInputCoords(const std::string& ship);


        //exceptions
        class invalidCoords : std::exception {};

    public:
        //Constructors
        explicit player();       //costruttore che inizializza tutta la flotta

        //Getters
        //ship getPlayerShip(coords coordsShip);     //getter di una nave date le sue coordinate
        //coords getShipCoords(ship playerShip);      //getter delle coordinate di una nave

        //Setters
};


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
