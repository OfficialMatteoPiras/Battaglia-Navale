// Created by Claudia De Carlo and Matteo Piras

#ifndef BATTAGLIA_NAVALE_PLAYER_H
#define BATTAGLIA_NAVALE_PLAYER_H

#include "../headers/coords.h"
#include "../headers/ship.h"
#include "../headers/matrix.h"

#include <map>
#include <vector>

//todo: alleggerire il codice
//- unire startRandomFleet e startFleet

class player{
    public:
        //costruttori
        explicit player();
        explicit player(const std::string &n);

        //getters
        std::string getName() const{ return name; }
        bool isAlive() const {return getPoints() > 0; }
        int getPoints() const;
        bool isABattleship(coords origin) const;
        coords getRandomOrigin() const;
        static coords getRandomCoord();
        std::string getRandomY() const;
        std::map<coords, ship*> getFleet() { return fleet; }      //TODO OR NOT TODO??
        bool isEmpty(coords target) { return defence.isEmpty(target); }

        //setters
        void setName(std::string n) { name = n; }
        void hit(coords target);

        //inizializzazione flotta
        std::vector<std::pair<std::string, std::string>> startFleet();          //start della flotta con input del giocatore
        std::vector<std::pair<std::string, std::string>> startRandomFleet();    //start della flotta randomico
        void printFleet();  //todo: rimuovere

        //comandi
        void action(coords origin, coords target, player& opponent);    //XYorigin XYtarget -> azione giocatore
        void visual();      //XX XX - mostra griglie di attacco e difesa
        void deleteY();     //AA AA - cancella tutte le Y
        void deleteX();     //BB BB - cancella tutte le X
        void deleteO();     //CC CC - cancella tutte le O

        //eccezioni
        class invalidOrigin : std::exception {};
        class notEnoughSpace : std::exception {};

        //messaggi output
        static std::string funnyMessage();

    protected:
        matrix defence;    //griglia difesa (navi)
        matrix attack;     //griglia attacco
        std::string name;
        std::map<coords, ship*> fleet;  //mappa per la flotta

        //azioni
        void fire(coords target, player& opponent);  //azione della corazzata
        void moveAndRepair(coords origin, coords target);   //azione della nave di supporto
        void moveAndSearch(coords origin, coords target, player& opponent); //azione del sottomarino di esplorazione

        //funzioni di supporto alle azioni
        void checkSpace(ship* s, coords target, bool alreadyExists);
        void move(coords origin, coords target);
        ship* getShipPointer(coords c);
        void repairFullShip(coords target);    //(ripara l'intera nave da una sua componente)
        bool wasHit(coords target);
        void removeShip(coords c);
        void insertShip(ship origin, char c);
        ship* newShip(coords stern, coords bow, char c);

        //funzioni random
        static coords getRandomCoord(coords coord, bool vertical = false, int distance = 1); //prende in input la PRUA!
        static int getRandomInt(int range = 11, int start = 0);

        //input coordinate
        static std::pair<coords, coords> getCoords(const std::string& message);
};

#endif //BATTAGLIA_NAVALE_PLAYER_H