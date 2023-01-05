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

        //actions
        void fire(coords origin, coords target, player& opponent);
        void moveAndRepair(coords origin, coords target);
        void moveAndSearch(coords origin, coords target, player& opponent);

        //funzioni di supporto alle azioni non serve chiamarle per altro ciao
        void checkSpace(ship* s, coords center);
        void move(coords origin, coords target);
        ship* getShipPointer(coords c);
        void repairFullShip(coords target);    //(RIPARA INTERA NAVE DA UNA SUA COMPONENTE)
        bool wasHit(coords target);

        //exceptions
        class invalidOrigin : std::exception {};
        class notEnoughSpace : std::exception {};

        //istanze per ship
        static battleship * getIstanceBattleship(coords bow, coords stern) { return new battleship(bow, stern); };
        static support * getIstanceSupport(coords bow, coords stern){ return new support(bow, stern); };
        static submarine * getIstanceSubmarine(coords bow, coords stern){ return new submarine(bow, stern); };

        //membri privati
        std::pair<coords, coords> getCoords(const std::string& message);

    public:
        //Constructors
        explicit player();       //costruttore che inizializza tutta la flotta

        //inizializzazione flotta
        void startFleet();
        void startRandomFleet();
        void printFleet();  //todo: rimuovere

        //FUNZIONI STUPIDE E BRUTTE NON GUARDARE
        void insert(coords origin, char c);
        void newShip(coords stern, coords bow, char c);
        int getShipLife(coords c);
        std::map<coords, ship*> fleet;  //mappa per la flotta
        //Getters
        //ship getPlayerShip(coords coordsShip);     //getter di una nave date le sue coordinate
        //coords getShipCoords(ship playerShip);      //getter delle coordinate di una nave

        //Setters


        //robe che servono all'avversario cattivo (leggono/scrivono SOLO defence)
        bool isEmpty(coords target) { return defence.isEmpty(target); };
        void hit(coords target);

        //ACTIONS
        //XX XX
        void visual(){
            game::grid(defence, attack);
        }

        //AA AA

        //XYorigin XYtarget
        void action(coords origin, coords target, player& opponent);

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
