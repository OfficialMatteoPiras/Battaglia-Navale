// Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_PLAYER_H
#define BATTAGLIA_NAVALE_PLAYER_H

#include <map>
#include <vector>
#include "../headers/coords.h"
#include "../headers/ship.h"
#include "../headers/matrix.h"
#include "../headers/random.h"

class player{
    public:
        //costruttori
        explicit player();
        explicit player(const std::string& n);

        //getters
        std::string getName() const{ return name; }
        bool isAlive() const {return getPoints() > 0; }
        int getPoints() const;
        bool isABattleship(const coords& origin) const;
        coords getRandomOrigin() const;
        std::string getRandomY() const;
        bool isEmpty(const coords& target) { return defence.isEmpty(target); }

        //setters
        void setName(std::string n) { name = n; }
        void hit(const coords& target);

        //inizializzazione flotta
        std::vector<std::pair<coords, coords>> startFleet();          //start della flotta con input del giocatore
        std::vector<std::pair<coords, coords>> startRandomFleet();    //start della flotta randomico
        void printFleet();

        //comandi
        void action(const coords& origin, const coords& target, player& opponent, bool replay = false);    //XYorigin XYtarget -> azione giocatore
        void visual();      //XX XX - mostra griglie di attacco e difesa
        void deleteY();     //AA AA - cancella tutte le Y
        void deleteX();     //BB BB - cancella tutte le X
        void deleteO();     //CC CC - cancella tutte le O

        //eccezioni
        class invalidOrigin : std::exception {};
        class notEnoughSpace : std::exception {};

        //messaggi output
        static std::string funnyMessage();
        static std::string funnyComputerMessage();

    protected:
        matrix defence;    //griglia difesa (navi)
        matrix attack;     //griglia attacco
        std::string name;
        std::map<coords, ship*> fleet;  //mappa per la flotta

        //azioni
        void fire(const coords& target, player& opponent);  //azione della corazzata
        void moveAndRepair(const coords& origin, const coords& target);   //azione della nave di supporto
        void moveAndSearch(const coords& origin, const coords& target, player& opponent); //azione del sottomarino di esplorazione

        //funzioni di supporto alle azioni
        void checkSpace(ship* s, const coords& target, bool alreadyExists);
        void move(const coords& origin, const coords& target);
        ship* getShipPointer(const coords& c);
        void repairFullShip(const coords& target);    //(ripara l'intera nave da una sua componente)
        bool wasHit(const coords& target);
        void removeShip(const coords& c);
        void insertShip(ship& origin, char c);
        ship* newShip(const coords& stern, const coords& bow, char c);


        //*input coordinate*
        static std::pair<coords, coords> getCoords(const std::string& message);
};

#endif //BATTAGLIA_NAVALE_PLAYER_H