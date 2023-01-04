//Created by Claudia De Carlo

#include "../headers/player.h"

player::player() {

}

std::pair<coords, coords> player::getCoords(const std::string& message){
    std::string origin, target, delimiter = " ";
    //input
    std::cout << message << ": ";
    std::cin >> origin >> target;

    return {{origin},{target}};
}

void player::startFleet() {

    //START CORAZZATA
    for (int i = 0; i < 3; ++i) {
        std::pair<coords, coords> input = getCoords("Quali sono le coordinate per la corazzata " + std::to_string(i + 1));
        battleship newShip = getIstanceBattleship(input.first, input.second);
        fleet[newShip.getCenter()] = &newShip;
        std::cout << std::endl;
    }

    //START SUPPORTO
    for (int i = 0; i < 3; ++i) {
        std::pair<coords, coords> input = getCoords("Quali sono le coordinate per la nave di supporto " + std::to_string(i + 1));
        support newShip = getIstanceSupport(input.first, input.second);
        fleet[newShip.getCenter()] = &newShip;
        std::cout << std::endl;
    }

    //START SOTTOMARINO
    for (int i = 0; i < 2; ++i) {
        std::pair<coords, coords> input = getCoords("Quali sono le coordinate per il sottomarino " + std::to_string(i + 1));
        submarine newShip = getIstanceSubmarine(input.first, input.second);
        fleet[newShip.getCenter()] = &newShip;
        std::cout << std::endl;
    }

    std::cout << "\n\t ******* LA FLOTTA STA SALPANDO CAPITANO! *******" << std::endl;

}

void player::printFleet() {
    for(auto it = fleet.cbegin(); it != fleet.cend(); ++it){
        std::cout << it->first.getRow() << it->first.getCol() << " " << it->second->getCenter() << std::endl;
    }
}

void player::startRandomFleet() {
    //todo: sovrapposizione delle navi!
    int dim = 5;
    //START FLOTTA
    for (int i = 0; i < 8; ++i) {
        try{
            coords c1 = game::getRandomCoord();
            bool vtr = game::getRandomInt(100) % 2 == 0;
            coords c2 = game::getRandomCoord(c1, vtr, dim);
            std::pair<coords, coords> input(c1, c2);

            if(i == 3 || i == 6) dim -= 2;

            if (i >= 0 && i < 3) {   //CORAZZATA
                battleship newShip = getIstanceBattleship(input.first, input.second);
                fleet[newShip.getCenter()] = &newShip;
            }
            if (i >= 3 && i < 6) {   //SUPPORTO
                support newShip = getIstanceSupport(input.first, input.second);
                fleet[newShip.getCenter()] = &newShip;
            }
            if (i >= 6) {   //SOTTOMARINO
                submarine newShip = getIstanceSubmarine(input.first, input.second);
                fleet[newShip.getCenter()] = &newShip;
            }
            std::cout << c1 << " " << c2 << " " << vtr << " " << dim << std::endl;
        }
        catch (coords::invalidCoords c){
            std::cout << " ** invalid coordinates **" << std::endl;
            i--;
        }
    }
}










