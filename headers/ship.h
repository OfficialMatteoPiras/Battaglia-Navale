//Created by Andrea Nalin

#ifndef BATTAGLIA_NAVALE_SHIP_H
#define BATTAGLIA_NAVALE_SHIP_H

#include <iostream>
#include <utility>
#include "../headers/coords.h"
#include "../headers/game.h"


class ship{
   // private:

    protected:
        coords center;
        bool vertical;
        int dim, life;
        //exceptions
        class invalidPosition : std::exception {};
        //check position
        static bool checkPosition(coords target, game::matrix checkMatrix);     //matrix to check if there's something on target

    public:
        //constructors
        ship(): center{{"A1"}}, vertical{false}, life{1}, dim{1} {};
        ship(coords c, bool v, int l, int d): center{c}, vertical{v}, life{l}, dim{d} {};

        ship(const ship&) = delete;     // deactivate copy constructor
        //ship& operator=(const ship&) = delete;

        //getters per prua e poppa
        virtual coords getBow() = 0;
        virtual coords getStern() = 0;

        //getters utili
        coords getCenter() { return center; };     //get coord center
        static coords getCenter(coords bow, coords stern);
        const int getLife() { return life; };          //get life
        const int getDimension() { return dim; };     //get ship dimension

        //setters
        void removeHealth() { life --; };       //life - 1
        void removeShip(coords center, game::matrix *removeMatrix);      //todo: funzione per rimuovere una nave

        //funzioni comuni alle navi
        virtual void action(coords target, game::matrix* matrixShips, game::matrix* matrixAttack, game::matrix* opponentDefence) = 0;      //function for ship action

        //distruttore
        ~ship() = default;
};

class battleship : public ship{
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
        void action(coords target, game::matrix* matrixShips, game::matrix* matrixAttack, game::matrix* opponentDefence) override;
};

class support : public ship{
/*private:
    const int dim = 3;
    int life = 3;
    coords center;
    bool vertical;*/
public:
    //constructor
    //support() : center{{"A3"}}, vertical{false}{};   //default constructor           //! to remove if not used
    //support(coords ctr, bool vert) : center{ctr}, vertical{vert}{};
    support(){
        ship::center = coords ("A3");
        ship::vertical = false;
    }

    support(coords ctr, bool vert){
        ship::center = ctr;
        ship::vertical = vert;
    }


    //getters per prua e poppa
    coords getBow() override;
    coords getStern() override;

    //action
    void action(coords target, game::matrix* matrixShips, game::matrix* matrixAttack, game::matrix* opponentDefence) override;
    bool move(coords target, game::matrix* matrixDefence);
};

class submarine : public ship{
/*private:
    const int dim = 1;
      int life = 1;
      coords center;
      bool vertical = false;*/
public:
    //constructor
    //submarine() : center{{"A3"}}, vertical{false}{};   //default constructor           //! to remove if not used
    //submarine(coords ctr) : center{ctr}{};
    submarine(){
        ship::center = coords("A3");
        ship::life = 1;
        ship::vertical = false;
        ship::dim = 1;
    }
    submarine(coords ctr){
        ship::center = ctr;
        ship::life = 1;
        ship::vertical = false;
        ship::dim = 1;
    }
    //submarine(const submarine& sub);

    //getters per prua e poppa
    coords getBow() override;
    coords getStern() override;

    //action
    void action(coords target, game::matrix* matrixShips, game::matrix* matrixAttack, game::matrix* opponentDefence) override;
    bool move(coords target, game::matrix* matrixDefence);
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
    //virtual void action(coords, game::matrix/*, game::matrix/*, game::matrix/*) = 0;
    //virtual bool move(coords target, game::matrix defense);
    bool move(coords target, game::matrix defense, char c);

    virtual void action(coords, game::matrix*, game::matrix*, game::matrix*) = 0;
};

class battleship : public ship
{
private:
    const int dim = 5;
    int life = 5;

public:
    //shoot
    void action(coords target, game::matrix* defense, game::matrix* attack, game::matrix* oppDef) override;
};

class support : public ship
{
private:
    const int dim = 3;
    int life = 3;

public:
    //move
    //repair
    void action(coords target, game::matrix *defense, game::matrix *attack, game::matrix* oppDef) override;

};

class submarine : public ship
{
private:
    const int dim = 1;
    int life = 1;

public:
    //move
    //research
    void action(coords target, game::matrix* defense, game::matrix *attack, game::matrix* oppDef) override;
};*/

#endif //BATTAGLIA_NAVALE_SHIP_H