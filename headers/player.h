// Claudia De Carlo

#ifndef BATTAGLIA_NAVALE_PLAYER_H
#define BATTAGLIA_NAVALE_PLAYER_H

#include <map>
#include <utility>
#include <vector>
#include "../headers/coords.h"
#include "../headers/ship.h"
#include "../headers/matrix.h"
#include "../headers/random.h"

class player{
    public:
    //COSTRUTTORI
        //Costruttore di default
        explicit player(): name{"Player"}, fleet{} {}

        //Costruttore con nome del giocatore
        explicit player(std::string  n): name{std::move(n)}, fleet{} {}

    //GETTERS: restituiscono informazioni sul giocatore
        //Restituisce una stringa contenente il nome del giocatore
        std::string getName() const{ return name; }

        //Restituisce il numero totale di unità non colpite
        int getPoints() const;

        //Verifica se il giocatore ha ancora unità non colpite
        bool isAlive() const {return getPoints() > 0; }

        //Verifica se la nave nelle coordinate origin è una corazzata
        bool isABattleship(const coords& origin) const;

        //Restituisce la coordinata (centrale) di una nave casuale della flotta
        coords getRandomOrigin() const;

        //Restituisce (come stringa) una coordinata casuale tra le Y sulla griglia d'attacco;
        //se non ci sono Y restituisce una stringa vuota
        std::string getRandomY() const;

        //verifica che non ci siano navi nelle coordinate di target (sulla griglia di difesa)
        bool isEmpty(const coords& target) const { return defence.isEmpty(target); }

        //stampa a schermo l'elenco della flotta
        void printFleet() const;

    //SETTERS
        //modifica il nome del giocatore
        void setName(std::string n) { name = n; }

        //colpisce la nave nelle coordinate di target:
        //modifica il carattere sulla griglia di difesa e sottrae una "vita" alla nave corrispondente
        void hit(const coords& target);

        //inizializza la flotta di un giocatore umano tramite input e output
        std::vector<std::pair<coords, coords>> startFleet();          //start della flotta con input del giocatore

        //inizializza la flotta in modo casuale
        std::vector<std::pair<coords, coords>> startRandomFleet();    //start della flotta randomico

    //COMANDI
        //esegue l'azione sulle coordinate di target (è diversificata in base al tipo di nave indicata da origin)
        void action(const coords& origin, const coords& target, player& opponent, bool replay = false);

        //XX XX - mostra griglie di attacco e difesa
        void visual();

        //AA AA - cancella tutte le Y dalla griglia di attacco
        void deleteY();

        //BB BB - cancella tutte le X dalla griglia di attacco
        void deleteX();

        //CC CC - cancella tutte le O dalla griglia di attacco
        void deleteO();

    //ECCEZIONI
        //Lanciata quando la coordinata di origine non corrisponde al centro di nessuna delle navi della flotta
        class invalidOrigin : std::exception {};

        //Lanciata quando si cerca di inserire una nave in una posizione che non può contenerla interamente
        class notEnoughSpace : std::exception {};

    //MESSAGGI DI OUTPUT
        //Genera un messaggio random (per la conclusione dell'inizializzazione della flotta)
        static std::string funnyMessage();
        //Genera un messaggio random (per i vari turni della partita)
        static std::string funnyComputerMessage();

    protected:
        matrix defence;     //griglia di difesa
        matrix attack;      //griglia di attacco
        std::string name;   //nome del giocatore
        std::map<coords, ship*> fleet;  //mappa per la flotta

    //AZIONI DELLE TRE NAVI
        //Azione della corazzata
        void fire(const coords& target, player& opponent);  //azione della corazzata

        //Azione della nave di supporto
        void moveAndRepair(const coords& origin, const coords& target);   //azione della nave di supporto

        //Azione del sottomarino di esplorazione
        void moveAndSearch(const coords& origin, const coords& target, player& opponent); //azione del sottomarino di esplorazione

    //FUNZIONI DI SUPPORTO ALLE AZIONI
        //Controlla se c'è spazio per inserire una nave in target (se non c'è lancia notEnoughSpace())
        void checkSpace(ship* s, const coords& target, bool alreadyExists);

        //Sposta una nave QUALSIASI da origin a target, propaga eccezione se non c'è spazio
        void move(const coords& origin, const coords& target);

        //Restituisce un puntatore alla nave data UNA QUALSIASI delle sue coordinate
        ship* getShipPointer(const coords& c);

        //Ripara l'intera nave data una qualsiasi delle sue coordinate
        void repairFullShip(const coords& target);

        //Verifica se l'unità in target è già stata colpita
        bool wasHit(const coords& target);

        //Rimuove una nave dalla flotta e dalla griglia di difesa
        void removeShip(const coords& c);

        //Crea una nave, la inserisce nella flotta e ne restituisce un puntatore
        ship* newShip(const coords& stern, const coords& bow, char c);

        //Inserisce la nave s nella griglia di difesa
        void insertShip(ship& s, char c);

    //INPUT COORDINATE
        //Scrive il messaggio in output, poi prende in input e restituisce una coppia di coordinate di tipo XY-origin, XY-target
        static std::pair<coords, coords> getCoords(const std::string& message);
};

#endif //BATTAGLIA_NAVALE_PLAYER_H