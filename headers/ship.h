//Matteo Piras

#ifndef BATTAGLIA_NAVALE_SHIP_H
#define BATTAGLIA_NAVALE_SHIP_H

#include <iostream>
#include "../headers/coords.h"


class ship{
protected:
    coords center {0,0};
    bool vertical = false;
    int dim = 0, life = 0;

public:
    //COSTRUTTORI
    explicit ship(coords ctr): center{ctr} {};                //costruttore
    explicit ship(coords bow, coords stern, unsigned int d = 0){        //costruttore che ricava il centro da prua e poppa
        dim = d;
        life = dim;
        vertical = bow.getY() == stern.getY();      //se la colonna delle ordinate è la stessa restituisce true
        //CENTER
        if(bow.getY() < stern.getY() || bow.getX() < stern.getX()){  //se la poppa è sopra la prua
            coords temp = stern;
            stern = bow;
            bow = temp;
        }
        if(vertical) {      //se la nave è verticale
            int x = (bow.getX() + stern.getX()) / 2;
            center = coords (x, bow.getY());    //dichiaro center
        }
        else{
            int y = (bow.getY() + stern.getY())/2;
            center = coords (bow.getX(), y);    //dichiaro center
        }
    };

    //GETTERS
    coords& getCenter(){ return center; }           //ritorna il centro di una nave
    bool isVertical() const{ return vertical; }     //ritorna se è verticale o meno la nave
    int getDimension() const { return dim; }        //ritorna la dimensione della nave
    int getLife() const { return life; }            //ritorna la vita della nave
    coords getBow() const;                          //restituisce la prua
    coords getStern() const;                        //restituisce la poppa

    bool contains(coords c) const;              //verifica se la coordinata trovata appartenga ad una nave
    bool isAlive() const { return life>0; }     //verifica che la nave sia viva

    //SETTERS
    void removeLife();          //rimuove la vita di una nave
    void restoreLife() { life = dim; }      //rigenera la vita di una nave
    void moved(coords newCenter) { center = newCenter; }        //cambia il centro do una nave a seguito di uno spostamento

};


std::ostream& operator<<(std::ostream& os, ship& s);        //overload dell'operatore di output

// ---------- NAVE DA BATTAGLIA --------- //
class battleship : public ship{
public:
    battleship(coords bow, coords stern) : ship(bow, stern) {           //costruttore che inizializza una nave da battaglia chiamando il costruttore della super classe
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 5;
        ship::life = 5;
    }

};

// ---------- NAVE DI SUPPORTO ---------- //
class support : public ship{
public:

    support(coords bow, coords stern) : ship(bow, stern) {           //costruttore che inizializza una nave di supporto chiamando il costruttore della super classe
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 3;
        ship::life = 3;
    }

};

//---------- SOTTOMARINO DI RICERCA ----------//
class submarine : public ship{
public:
    submarine(coords bow, coords stern) : ship(bow, stern) {           //costruttore che inizializza un sottomarino il costruttore della super classe
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 1;
        ship::life = 1;
    }
};


#endif //BATTAGLIA_NAVALE_SHIP_H