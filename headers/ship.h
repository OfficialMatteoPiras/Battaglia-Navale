//Created by Andrea Nalin

#ifndef BATTAGLIA_NAVALE_SHIP_H
#define BATTAGLIA_NAVALE_SHIP_H

#include "../headers/coords.h"
#include "../headers/game.h"

class ship{
protected:
    coords center {1,1};
    bool vertical = false;
    int dim = 1, life = 1;

public:
    //COSTRUTTORI
    explicit ship(coords ctr): center{ctr} {};      //costruttore
    explicit ship(coords bow, coords stern){        //costrtuttore che ricava il centro da prua e poppa
        //VERTICAL
        vertical = bow.getY() == stern.getY();      //se le ordinate sono UGUALI = true altrimenti false
        //CENTER
        if(vertical) {      //se la nave è verticale
            int x = bow.getX() - stern.getX();
            if(x < 0) x*= (-1);             //se la differenza è >0 moltiplico per -1
            center = coords (x, bow.getY());    //dichiaro center
        }
        else{
            int y = bow.getY() - stern.getY();
            if(y < 0) y*= (-1);             //se la differenza è >0 moltiplico per -1
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

    //SETTERS
    void removeLife() { life--; }
    void restoreLife() { life = dim; }

};

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
    }


};

class support : public ship{
public:
    support(coords ctr, bool vtr) : ship(ctr) {
        ship::vertical = vtr;
        ship::dim = 3;
        ship::life = 3;
    }
    support(coords bow, coords stern) : ship(bow, stern) {
        ship::vertical = bow.getY() == stern.getY();
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
    }
};

//OPERATOR << (stampa come centro, dimensione, vita, verticale )
std::ostream& operator<< (std::ostream& os, coords ship);


#endif //BATTAGLIA_NAVALE_SHIP_H