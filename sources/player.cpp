//Created by Claudia De Carlo

#include "../headers/player.h"

player::player() {
    player::getCoords("corazzata 1");

    /*
    fleet.push_back(new submarine({"A10"}));
    fleet.push_back(new submarine({"B10"}));
    fleet.push_back(new submarine({"C10"}));

    defence.insert({"A10"}, 'E');
    defence.insert({"C10"}, 'E');
    defence.insert({"E10"}, 'E');

    std::cout << "-------- PLAYER 1 --------\n" << std::endl;
    game::grid(defence, attack);

    submarine *s = dynamic_cast <submarine*> ( fleet[0] );
    s->move({"N6"}, &defence);

    std::cout << "-------- PLAYER 1 --------\n" << std::endl;
    game::grid(defence, attack);

    free(s);
*/
    //TODO: INSERIRE LA NUMERAZIONE NEI MESSAGGI E FARE LA SEPARAZIONE DELLA STRINGA: FUNZIONE CHE TORNA PAIR<STRING, STRING>

    //CORAZZATE
    /*for (int i = 0; i < 3; ++i) {
        const coords c = getInputCoords("la corazzata");
        ships[i] = new battleship(c);
        //TODO: ad ogni ciclo inserisce la nave
    }
    //NAVI SUPPORTO
    for (int i = 0; i < 3; ++i) {
        const coords c = getInputCoords("la nave di supporto");
        ships[i] = new support(c);
        //TODO: ad ogni ciclo inserisce la nave
    }
    //SOTTOMARINO
    for (int i = 0; i < 3; ++i) {
        const coords c = getInputCoords("il sottomarino");
        ships[i] = new submarine(c);
        //TODO: ad ogni ciclo inserisce la nave
    }*/
    /*ships[0] = new submarine({"A10"});
    ships[1] = new submarine({"C10"});
    ships[2] = new submarine({"E10"});

    for (int i = 0; i < 3; ++i) {
        std::cout << ships[i]->getCenter() << std::endl;
    }
    defence.insert({"A10"}, 'E');
    defence.insert({"C10"}, 'E');
    defence.insert({"E10"}, 'E');

    std::cout << "-------- PLAYER 1 --------\n" << std::endl;
    game::grid(defence, attack);

    submarine *s = dynamic_cast <submarine*> ( ships[0] );
    s->move({"N6"}, &defence);

    std::cout << "-------- PLAYER 1 --------\n" << std::endl;
    game::grid(defence, attack);

    free(s);*/
}



std::pair<coords, coords> player::getCoords(const std::string& message){
    std::string origin, target, delimiter = " ";
    //input
    std::cout << message << ": ";
    std::cin >> origin >> target;

    return {{origin},{target}};
}

void player::startFleet() {

    for (int i = 0; i < 3; ++i) {
        //restituisce prua e poppa
        std::pair<coords, coords> input = getCoords("Quali sono le coordinate per la corazzata " + std::to_string(i));
        //ricavo il centro della nave
        //todo: creare un oggetto ship, convertire prua / poppa con centro ed inserire nella mappa
        submarine s ();
    }
}


/*
std::string player::getInputCoords(const std::string& message) {
    std::string newCoords;.
    std::cout << "Inserire le coordinate per " << message << "(poppa prua): ";
    std::cin >> newCoords;
    return {newCoords};
}*/

/*
ship player::getPlayerShip(coords coordsShip) {
    //return ship();
}

coords player::getShipCoords(ship playerShip) {
    return coords(0, 0);
}
*/






