//Created by Claudia De Carlo and Matteo Piras

#include "../headers/player.h"

player::player(std::string n) {
    name = n;
    fleet = {};
}

std::pair<coords, coords> player::getCoords(const std::string& message){
    std::string origin, target, delimiter = " ";
    //input
    std::cout << message << ": ";
    std::cin >> origin >> target;

    return {{origin},{target}};
}

void player::startFleet() {

    //todo: usare la funzione newShip();
    int dim = 5, cont = 1;
    char ch = 'C';

    std::pair<coords, coords> input = {{"A10"},{"B10"}};

    //START CORAZZATA
    for (int i = 0; i < 8; i++) {
        try{
            if(i >= 0 && i < 3)
                input = getCoords("Quali sono le coordinate per la corazzata " + std::to_string(cont));
            if(i >= 3 && i < 6)
                input = getCoords("Quali sono le coordinate per la nave di supporto " + std::to_string(cont));
            if(i >= 6)
                input = getCoords("Quali sono le coordinate per il sottomarino " + std::to_string(cont));

            if((input.first - input.second) + 1 != dim) throw coords::invalidCoords();

            //CHECK E MATRIX INPUT
            ship s(input.first, input.second, dim);
            checkSpace(&s, s.getCenter());
            insertShip(s, ch);

            //FLEET INPUT
            newShip(s.getStern(), s.getBow(), ch);

            if(i + 1 == 3 || i + 1 == 6) dim -= 2;
            if(i + 1 == 3) { ch = 'S'; cont = 0; }
            if(i + 1 == 6) { ch = 'E'; cont = 0; }

            cont ++;
        }
        catch (coords::invalidCoords c){
            std::cout << " ** invalid coordinates **" << std::endl;
            i--;
        }
        catch(notEnoughSpace e){
            std::cout << " ** not enough space **" << std::endl;
            i--;
        }
        std::cout << "-------------------" << std::endl;
        //visual();
    }


    /*  for (int i = 0; i < 3; ++i) {
        std::pair<coords, coords> input = getCoords("Quali sono le coordinate per la corazzata " + std::to_string(i + 1));
        battleship *newShip = getIstanceBattleship(input.first, input.second);
        fleet[newShip->getCenter()] = newShip;
        std::cout << std::endl;
    }

    //START SUPPORTO
  for (int i = 0; i < 3; ++i) {
        std::pair<coords, coords> input = getCoords("Quali sono le coordinate per la nave di supporto " + std::to_string(i + 1));
        support *newShip = getIstanceSupport(input.first, input.second);
        fleet[newShip->getCenter()] = newShip;
        std::cout << std::endl;
    }

    //START SOTTOMARINO
    for (int i = 0; i < 2; ++i) {
        std::pair<coords, coords> input = getCoords("Quali sono le coordinate per il sottomarino " + std::to_string(i + 1));
        submarine *newShip = getIstanceSubmarine(input.first, input.second);
        fleet[newShip->getCenter()] = newShip;
        std::cout << std::endl;
    }*/

    std::cout << "\n\t ******* " << funnyMessage() << " *******" << std::endl;

}

void player::printFleet() {
    for (auto & it : fleet) {
        std::cout << "center: " << it.first.getRow() << it.first.getCol() << "\t| ";
        std::cout << "bow: " <<it.second->getBow().getRow() << it.second->getBow().getCol() << "\t| ";
        std::cout << "stern: " <<it.second->getStern().getRow() << it.second->getStern().getCol() << std::endl;
    }
}

void player::startRandomFleet() {
    int dim = 5;
    char ch = 'C';

    //START FLOTTA
    for (int i = 0; i < 8; ++i) {
        try{

            coords c1 = game::getRandomCoord();
            bool vtr = game::getRandomInt(99) % 2 == 0;
            coords c2 = game::getRandomCoord(c1, vtr, dim);
            //std::pair<coords, coords> input(c1, c2);
            std::cout << c1 << " " << c2 << " " << vtr << " " << dim << std::endl;

            //CHECK E MATRIX INPUT
            ship s(c1,c2,dim);
            checkSpace(&s, s.getCenter());
            insertShip(s, ch);

            //FLEET INPUT
            newShip(s.getStern(), s.getBow(), ch);

            if(i + 1 == 3 || i + 1 == 6) dim -= 2;
            if(i + 1 == 3) ch = 'S';
            if(i + 1 == 6) ch = 'E';

        }
        catch (coords::invalidCoords c){
            std::cout << " ** invalid coordinates **" << std::endl;
            i--;
        }
        catch(notEnoughSpace e){
            std::cout << " ** not enough space **" << std::endl;
            i--;
        }
        std::cout << "-------------------" << std::endl;
        //visual();
    }
    std::cout << "\n\t ******* " << funnyMessage() << " *******" << std::endl;
}

//ACTIONS
//XYorigin XYtarget
void player::action(coords origin, coords target, player& opponent){
    if (fleet.find(origin) == fleet.end())       //controlla che origin sia il centro di una delle sue navi
        throw invalidOrigin();
    ship* s = fleet.find(origin)->second;
    char c = defence.getElement(origin);
    if (c == 'C' || c == 'c'){
        fire(origin, target, opponent);
    }
    else if (c == 'S' || c == 's'){
        moveAndRepair(origin, target);
    }
    else {
        moveAndSearch(origin, target, opponent);
    }
}

//ACTIONS - FUNZIONI DI SUPPORTO (PRIVATE)
//azione della corazzata
void player::fire(coords origin, coords target, player& opponent){
    if(opponent.isEmpty(target)){       // acqua
        attack.insert(target, 'O');
    }
    else{                               // fuoco
        opponent.hit(target);
        attack.insert(target, 'X');
    }
}

//azione della nave di supporto
void player::moveAndRepair(coords origin, coords target){
    move(origin, target);   //lancia eccezione se non c'è spazio

    ship* s = fleet.find(target)->second;
    coords c = target;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j<= 1; j++){
            if(j != 0) {        //non controlla nelle posizioni occupate dal sottomarino! (verticale = colonna centrale, orizzontale = riga centrale)
                if (s->isVertical())
                    c = target.add(i, j);
                else
                    c = target.add(j, i);
                if (wasHit(c)) {         //ogni volta che trova una lettera minuscola (NON appartenente al sottomarino)
                    repairFullShip(c);
                }
            }
        }
    }
}

//restituisce un puntatore alla nave data UNA QUALSIASI delle sue coordinate    //TODO gestire c vuota
ship* player::getShipPointer(coords c){
    int dim = defence.getShipDim(c);
    //if(dim == 0)
    //    throw invalidOrigin;
    coords center = c;
    ship* s = nullptr;
    bool found = false;
    for (int i = -dim/2; i <= dim/2 && !found; i++) {
        for (int k = 0; k <= 1 && !found; k++) {
            try{
                if (k == 0)
                    center = c.addCol(i);
                else
                    center = c.addRow(i);

                if (fleet.find(center) != fleet.end()) {   //esiste una nave con quel centro?
                    s = fleet.find(center)->second;
                    //chiede se quella cella appartiene (funzione della nave)
                    found = s->contains(c);
                }
            }catch (coords::invalidCoords &e) {}

        }
    }
    return s;
}


//repairfullship
void player::repairFullShip(coords c){
    ship* s = getShipPointer(c);
    s->restoreLife();
    int dim = s->getDimension();
    coords center = s->getCenter();
    for (int n = -dim/2; n <= dim/2; n++) {
        if (s->isVertical())
            defence.restore(center.addRow(n));
        else
            defence.restore(center.addCol(n));
    }
}



//azione del sottomarino
void player::moveAndSearch(coords origin, coords target, player& opponent){
    move(origin, target);  //lancia eccezione se non c'è spazio

    for (int i = -2; i <= 2; i++) {             //ciclo per le righe
        for (int j = -2; j <= 2; j++) {         //ciclo per le colonne
            if (!opponent.isEmpty(target.add(i, j))) {        //se la cella non è vuota
                attack.insert(target.add(i, j), 'Y');
            }
        }
    }
}



//MOVE
//controlla se c'è spazio per una nave
void player::checkSpace(ship* s, coords center){
    int dim = s->getDimension();
    bool valid = true;
    try {
        for (int i = -dim / 2; i <= dim / 2 && valid; i++) {      //controllo spazio
            if (s->isVertical()) {
                if (!defence.isEmpty(center.addRow(i)))
                    valid = false;
            } else {
                if (!defence.isEmpty(center.addCol(i)))
                    valid = false;
            }
        }
    }catch(coords::invalidCoords c){
        std::cout << "** invalid coordinates **" << std::endl;
    }
    if (!valid)
        throw notEnoughSpace();     //eccezione non c'è spazio
}

//sposta una nave QUALSIASI da origin a target, lancia eccezione se non c'è spazio
void player::move(coords origin, coords target) {
    ship* s = fleet.find(origin)->second;
    checkSpace(s, target);
    int dim = s->getDimension();
    for(int i = -dim/2; i <= dim/2; i++){       //riscrittura defense
        if(s->isVertical()) {
            defence.insert(target.addRow(i), defence.getElement(origin.addRow(i)));
            defence.insert(origin.addRow(i), ' ');
        } else {
            defence.insert(target.addCol(i), defence.getElement(origin.addCol(i)));
            defence.insert(origin.addCol(i), ' ');
        }
    }
    s->moved(target);
    fleet.erase(origin);
    fleet.insert(std::make_pair(target, s));
}

bool player::wasHit(coords target){
    char c = defence.getElement(target);
    return c == 'c' || c == 's' || c == 'e';
}

void player::hit(coords target) {
    defence.hit(target);
    ship* s = getShipPointer(target);
    s->removeLife();
}

//FUNZIONI STUPIDE NON GUARDARE SIAMO BRUTTE
void player::newShip(coords stern, coords bow, char c){
    ship* s = nullptr;
    if(c == 'C')
        s = new battleship(bow, stern);
    if(c == 'S')
        s = new support(bow, stern);
    if(c == 'E')
        s = new submarine(bow, stern);
    //fleet.insert(std::make_pair(s->getCenter(), s));      //uguale!!!
    fleet[s->getCenter()] = s;
}

int player::getShipLife(coords origin){
    if (fleet.find(origin) == fleet.end())       //controlla che origin sia il centro di una delle sue navi
        throw invalidOrigin();
    ship* s = fleet.find(origin)->second;
    return s->getLife();
}

//SETTERS
void player::insertShip(ship s, char c){
    coords n_c = s.getBow();
    for (int i = 0; i < s.getDimension(); i++) {
        defence.insert(n_c, c);
        //std::cout << "new: " << n_c << std::endl;
        if(s.isVertical())
            n_c = n_c.add(1,0);
        else
            n_c = n_c.add(0,1);
    }
}

std::string player::funnyMessage() {
    srand(rand());
    std::vector<std::string> message = {
            "NAVI SALPATE!",
            "LA FLOTTA STA SALPANDO CAPITANO!",
            "LA BATTAGLIA E' GIA' VINTA!",
            "LE VELE SONO SPIEGATE!",
            "SIAMO SALPATI CAPITANO!",
            "CAPITANO, ATTENDIAMO ORDINI!",
            "TUTTE LE NAVI SONO IN POSIZIONE!"
    };
    int pos = message.size() - 1;
    return message[rand() % pos];
}













