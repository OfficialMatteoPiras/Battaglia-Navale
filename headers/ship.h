//Created by Andrea Nalin

#ifndef BATTAGLIA_NAVALE_SHIP_H
#define BATTAGLIA_NAVALE_SHIP_H

#include <iostream>
#include <utility>
#include "../headers/coords.h"
#include "../headers/game.h"


class ship{
protected:
    coords center {1,1};
    bool vertical = false;
    int dim = 1, life = 1;
    char c;

public:
    //COSTRUTTORI
    explicit ship(coords ctr): center{ctr} {};      //costruttore
    explicit ship(coords bow, coords stern){        //costrtuttore che ricava il centro da prua e poppa
        //VERTICAL
        vertical = bow.getY() == stern.getY();      //se le ordinate sono UGUALI = true altrimenti false
        //CENTER
        if(vertical) {      //se la nave è verticale
            if(bow.getY() < stern.getY()){  //se la poppa è sopra la prua
                coords temp = stern;
                stern = bow;
                bow = temp;
            }
            int x = (bow.getX() + stern.getX())/2;
            center = coords (x, bow.getY());    //dichiaro center
        }
        else{
            if(bow.getX() < stern.getX()){  //se la poppa è più a destra la prua
                coords temp = stern;
                stern = bow;
                bow = temp;
            }
            int y = (bow.getY() + stern.getY())/2;
            center = coords (bow.getX(), y);    //dichiaro center
        }
    };

    //GETTERS
    coords& getCenter(){ return center; }
    bool isVertical() const{ return vertical; }
    int getDimension() const { return dim; }
    int getLife() const { return life; }
    coords getStern() const;
    coords getBow() const;
    bool contains(coords c) const;

    char getC() const {return c;};

    //SETTERS
    void removeLife() { life--; }
    void restoreLife() { life = dim; }
    void moved(coords newCenter) { center = newCenter; }

    //todo: aggiungere DISTRUTTORE
};

std::ostream& operator<<(std::ostream& os, ship& s);

class battleship : public ship{

public:
    //COSTRUTTORI
    //chiamata ai costruttori della super e dichiarazione dei membri per battleship
    battleship(coords ctr, bool vtr) : ship(ctr) {
        ship::vertical = vtr;
        ship::dim = 5;
        ship::life = 5;

    }
    battleship(coords bow, coords stern) : ship(bow, stern) {
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 5;
        ship::life = 5;
        c = 'C';
    }


};

class support : public ship{
public:

    support(coords bow, coords stern) : ship(bow, stern) {
        ship::vertical = bow.getY() == stern.getY();
        ship::dim = 3;
        ship::life = 3;
        c = 'S';
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
        c = 'E';
    }
};

//OPERATOR << (stampa come centro, dimensione, vita, verticale )
std::ostream& operator<< (std::ostream& os, coords &ship);


#endif //BATTAGLIA_NAVALE_SHIP_H