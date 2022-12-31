//Created by Andrea Nalin

#ifndef BATTAGLIA_NAVALE_SHIP_H
#define BATTAGLIA_NAVALE_SHIP_H

#include <iostream>
#include <utility>
#include "../headers/coords.h"
#include "../headers/backing.h"

#include "coords.h"

class ship{
    private:
        coords center;
        bool vertical;
        int dim, life;

    protected:
        //exceptions
        class invalidPosition : std::exception {};
        //check position
        bool checkPosition(coords target, backing::matrix checkMatrix);     //matrix to check if there's something on target

    public:
        //constructors
        ship(): center{{"A1"}}, vertical{false}, life{1}, dim{1} {};
        ship(coords c, bool v, int l, int d): center{c}, vertical{v}, life{l}, dim{d} {};

        //getters per prua e poppa
        virtual coords getBow() = 0;
        virtual coords getStern() = 0;

        //getters utili
        coords getCenter() {return center; };     //get coord center
        int getLife() {return life; };          //get life
        int getDimension() {return dim; };     //get ship dimension

        //setters
        void removeHealth() { life --; };       //life - 1

        //funzioni comuni alle navi
        virtual void action(coords target, backing::matrix* matrixShips, backing::matrix* matrixAttack, backing::matrix* opponentDefence) = 0;      //function for ship action
};

class battleship : ship{
    private:
        const int dim = 5;
        int life = 5;
        coords center;
        bool vertical;

    public:
        //constructor
        battleship() : center{{"A3"}}, vertical{false}{};   //default constructor           //! to remove if not used
        battleship(coords ctr, bool vert) : center{ctr}, vertical{vert}{};

        //getters per prua e poppa
        coords getBow() override;
        coords getStern() override;

        //action
        void action(coords target, backing::matrix* matrixShips, backing::matrix* matrixAttack, backing::matrix* opponentDefence) override;
};

class support : ship{
private:
    const int dim = 3;
    int life = 3;
    coords center;
    bool vertical;
public:
    //constructor
    support() : center{{"A3"}}, vertical{false}{};   //default constructor           //! to remove if not used
    support(coords ctr, bool vert) : center{ctr}, vertical{vert}{};

    //getters per prua e poppa
    coords getBow() override;
    coords getStern() override;

    //action
    void action(coords target, backing::matrix* matrixShips, backing::matrix* matrixAttack, backing::matrix* opponentDefence) override;
    bool move(coords target, backing::matrix* matrixDefence);
};


class submarine : ship{
private:
    const int dim = 3;
    int life = 3;
    coords center;
    bool vertical = false;
public:
    //constructor
    submarine() : center{{"A3"}}, vertical{false}{};   //default constructor           //! to remove if not used
    submarine(coords ctr) : center{ctr}{};

    //getters per prua e poppa
    coords getBow() override;
    coords getStern() override;

    //action
    void action(coords target, backing::matrix* matrixShips, backing::matrix* matrixAttack, backing::matrix* opponentDefence) override;
    bool move(coords target, backing::matrix* matrixDefence);
};



/*
class ship
{
private:
    coords pos;
    bool vertical;
    int life;
    int dim;

public:
    ship(): pos{{"A1"}}, vertical{false}, life{1}, dim{1} {};
    ship(coords c, bool v, int l, int d): pos{c}, vertical{v}, life{l}, dim{d} {};

    void setVertical(bool v) { vertical = v; }
    int Life() const { return life; }
    bool alive() const{ return life!=0; }
    bool getvertical() const { return vertical; }
    //virtual void action(coords, backing::matrix/*, backing::matrix/*, backing::matrix/*) = 0;
    //virtual bool move(coords target, backing::matrix defense);
    bool move(coords target, backing::matrix defense, char c);

    virtual void action(coords, backing::matrix*, backing::matrix*, backing::matrix*) = 0;
};

class battleship : public ship
{
private:
    const int dim = 5;
    int life = 5;

public:
    //shoot
    void action(coords target, backing::matrix* defense, backing::matrix* attack, backing::matrix* oppDef) override;
};

class support : public ship
{
private:
    const int dim = 3;
    int life = 3;

public:
    //move
    //repair
    void action(coords target, backing::matrix *defense, backing::matrix *attack, backing::matrix* oppDef) override;

};

class submarine : public ship
{
private:
    const int dim = 1;
    int life = 1;

public:
    //move
    //research
    void action(coords target, backing::matrix* defense, backing::matrix *attack, backing::matrix* oppDef) override;
};*/

#endif //BATTAGLIA_NAVALE_SHIP_H