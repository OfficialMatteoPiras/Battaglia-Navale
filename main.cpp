//#include "headers/backing.h"
#include "headers/ship.h"
#include "headers/player.h"
#include <iostream>
/*
int main(int argc, char **argv){
    /*backing::matrix ships1, attack1;
    backing::matrix ships2, attack2;

    //PLAYER 1
    //ships
    ships1.insert({"B8"}, 'C');
    ships1.insert({"B9"}, 'C');
    ships1.insert({"B10"}, 'C');
    ships1.insert({"B11"}, 'C');
    ships1.insert({"B12"}, 'C');
    ships1.insert({"F8"}, 'S');
    ships1.insert({"G8"}, 'S');
    ships1.insert({"H8"}, 'S');
    ships1.insert({"N6"}, 'E');
    //attack
    attack1.insert({"E7"}, 'X');
    attack1.insert({"E8"}, 'X');
    attack1.insert({"E9"}, 'X');
    attack1.insert({"L1"}, '0');
    attack1.insert({"L2"}, '0');

    //PLAYER 2
    //ships
    ships2.insert({"A8"}, 'C');
    ships2.insert({"B8"}, 'C');
    ships2.insert({"C8"}, 'C');
    ships2.insert({"D8"}, 'C');
    ships2.insert({"E8"}, 'C');
    ships2.insert({"G8"}, 'S');
    ships2.insert({"G9"}, 'S');
    ships2.insert({"G10"}, 'S');
    ships2.insert({"M2"}, 'E');
    //attack
    attack2.insert({"L7"}, 'X');
    attack2.insert({"L8"}, 'X');
    attack2.insert({"L9"}, 'X');
    attack2.insert({"A1"}, '0');
    attack2.insert({"A2"}, '0');

    //stampa griglia "iniziale"
    std::cout << "-------- PLAYER 1 --------\n" << std::endl;
    backing::grid(ships1, attack1);

    std::cout << "\n\n-------- PLAYER 2 --------\n" << std::endl;
    backing::grid(ships2, attack2);

    //scannerizzazione (sottomarino)
    submarine s({"N6"});
    s.action({"D7"}, &ships1, &attack1, &ships2);


    std::cout << "\n\n\n\n\n" << std::endl;

    //stampa griglia "iniziale"
    std::cout << "-------- PLAYER 1 --------\n" << std::endl;
    backing::grid(ships1, attack1);

    std::cout << "\n\n-------- PLAYER 2 --------\n" << std::endl;
    backing::grid(ships2, attack2);


    std::cout << "\n\n\n\n\n" << std::endl;
    std::cout << "-------- PLAYER 1 --------\n" << std::endl;
    //muovi sottomomarino
    s.move({"A10"}, &ships1);
    backing::grid(ships1, attack1);



    player player1;

}
*/
