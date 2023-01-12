//Created by Matteo Piras

#ifndef BATTAGLIA_NAVALE_SHIP_H
#define BATTAGLIA_NAVALE_SHIP_H

#include <iostream>
#include "../headers/coords.h"


class ship{
protected:
    coords center {0,0};
    bool vertical = false;
    int dim = 1, life = 1;

public:
    //COSTRUTTORI
    explicit ship(coords ctr): center{ctr} {};      //costruttore
    explicit ship(coords bow, coords stern, unsigned int d){        //costruttore che ricava il centro da prua e poppa
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
    coords& getCenter(){ return center; }
    bool isVertical() const{ return vertical; }
    int getDimension() const { return dim; }
    int getLife() const { return life; }
    coords getBow() const;          //prua
    coords getStern() const;        //poppa

    bool contains(coords c) const;
    bool isAlive() const { return life>0; }

    //SETTERS
    void removeLife();
    void restoreLife() { life = dim; }
    void moved(coords newCenter) { center = newCenter; }

    //TODO: aggiungere DISTRUTTORE
};


std::ostream& operator<<(std::ostream& os, ship& s);


class battleship : public ship{
public:
    //COSTRUTTORI
    //chiamata ai costruttori della classe base e dichiarazione dei membri per battleship
    battleship(coords ctr, bool vtr) : ship(ctr) {
        ship::vertical = vtr;
        ship::dim = 5;
        ship::life = 5;
    }
    battleship(coords bow, coords stern) : ship(bow, stern) {
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 5;
        ship::life = 5;
    }

};


class support : public ship{
public:

    support(coords bow, coords stern) : ship(bow, stern) {
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 3;
        ship::life = 3;
    }
    support(coords ctr, bool vtr) : ship(ctr) {
        ship::vertical = vtr;
        ship::dim = 3;
        ship::life = 3;
    }

};


class submarine : public ship{
public:
    submarine(coords ctr, bool vtr) : ship(ctr) {
        ship::vertical = vtr;
    }
    submarine(coords bow, coords stern) : ship(bow, stern) {
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 1;
        ship::life = 1;
    }
};


#endif //BATTAGLIA_NAVALE_SHIP_H