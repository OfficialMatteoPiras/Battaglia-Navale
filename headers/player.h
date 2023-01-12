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
    protected:
        matrix defence;    //griglia difesa (navi)
        matrix attack;     //griglia attacco
        std::string name;

        //actions
        void fire(coords origin, coords target, player& opponent);
        void moveAndRepair(coords origin, coords target);
        void moveAndSearch(coords origin, coords target, player& opponent);

        //funzioni di supporto alle azioni non serve chiamarle per altro ciao
        void checkSpace(ship* s, coords target, bool alreadyExists);
    //funzioni di supporto alle azioni non serve chiamarle per altro ciao
        void checkSpace(ship* s, coords target);
        void move(coords origin, coords target);
        ship* getShipPointer(coords c);
        void repairFullShip(coords target);    //(RIPARA INTERA NAVE DA UNA SUA COMPONENTE)
        bool wasHit(coords target);
        void removeShip(coords c);

        //FUNZIONI RANDOM
        static coords getRandomCoord(coords coord, bool vertical = false, int distance = 1); //prende in input la PRUA!
        static int getRandomInt(int range = 11, int start = 0);


        //istanze per ship
        //static battleship * getIstanceBattleship(coords bow, coords stern) { return new battleship(bow, stern); };
        //static support * getIstanceSupport(coords bow, coords stern){ return new support(bow, stern); };
        //static submarine * getIstanceSubmarine(coords bow, coords stern){ return new submarine(bow, stern); };

        //membri privati
        std::pair<coords, coords> getCoords(const std::string& message);

        std::map<coords, ship*> fleet;  //mappa per la flotta

    public:

        //Constructors
        explicit player();       //costruttore che inizializza tutta la flotta
        explicit player(const std::string &n){ name = n; };       //costruttore che inizializza tutta la flotta

        //getter
        std::string getName() const{ return name; }
        int getPoints();
        bool isAlive() {return getPoints() > 0; }
        std::string findY();
        bool isABattleship(coords origin);
        int getSumShipLife();
        std::map<coords, ship*> getFleet() { return fleet; };

        //inizializzazione flotta
        std::vector<std::pair<std::string, std::string>> startFleet();          //start della flotta con input del giocatore
        std::vector<std::pair<std::string, std::string>> startRandomFleet();    //start della flotta randomico
        void printFleet();  //todo: rimuovere
        coords getRandomOrigin();
        ship* newShip(coords stern, coords bow, char c);

        //FUNZIONI STUPIDE E BRUTTE NON GUARDARE            //todo: sistemare le funzioni stupide brutte da non guardare
        int getShipLife(coords c);

        //Setters
        void insertShip(ship origin, char c);
        void setName(std::string n) { name = n; }

        //robe che servono all'avversario cattivo (leggono/scrivono SOLO defence)
        bool isEmpty(coords target) { return defence.isEmpty(target); };
        void hit(coords target);

        static coords getRandomCoord();

        //ACTIONS
        //XX XX
        void visual();

        //AA AA
        void deleteY();

        //XYorigin XYtarget     -> azione giocatore umano
        void action(coords origin, coords target, player& opponent);

        //exceptions
        class invalidOrigin : std::exception {};
        class notEnoughSpace : std::exception {};

        //altro
        static std::string funnyMessage();
};



#endif //BATTAGLIA_NAVALE_PLAYER_H
