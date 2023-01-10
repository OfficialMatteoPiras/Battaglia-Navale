//Created by Claudia De Carlo and Matteo Piras

#include "../headers/player.h"

player::player() {
    name = "Player";
    fleet = {};
}

std::pair<coords, coords> player::getCoords(const std::string& message){
    std::string origin, target, delimiter = " ";
    //input
    std::cout << message << ": ";
    std::cin >> origin >> target;

    return {{origin},{target}};
}

    std::vector<std::pair<std::string, std::string>> player::startFleet() {

    //todo: usare la funzione newShip();
    int dim = 5, cont = 1;
    unsigned int dif;
    char ch = 'C';

    std::pair<coords, coords> input = {{"A10"},{"B10"}};
    std::vector<std::pair<std::string, std::string>> log;

    //START CORAZZATA
    for (int i = 0; i < 8; i++) {
        try{
            visual();       //todo: vedere se va bene visualizzare la griglia ogni ciclo
            if(i >= 0 && i < 3)
                input = getCoords("Quali sono le coordinate per la corazzata " + std::to_string(cont));
            if(i >= 3 && i < 6)
                input = getCoords("Quali sono le coordinate per la nave di supporto " + std::to_string(cont));
            if(i >= 6)
                input = getCoords("Quali sono le coordinate per il sottomarino " + std::to_string(cont));

            dif = (input.first - input.second) + 1;

            if(dif != dim) throw coords::invalidCoords();

            //CHECK E MATRIX INPUT
            ship s(input.first, input.second, dim);
            checkSpace(&s, s.getCenter());
            insertShip(s, ch);

            //FLEET INPUT
            newShip(s.getStern(), s.getBow(), ch);
            log.emplace_back(input.first.toString(), input.second.toString());

            if(i + 1 == 3 || i + 1 == 6) dim -= 2;
            if(i + 1 == 3) { ch = 'S'; cont = 0; }
            if(i + 1 == 6) { ch = 'E'; cont = 0; }

            cont ++;
        }
        catch (coords::invalidCoords& c){
            std::cout << " ** invalid coordinates **" << std::endl;
            i--;
        }
        catch(notEnoughSpace& e){
            std::cout << " ** not enough space **" << std::endl;
            i--;
        }
        //visual();
    }

    std::cout << "\n\t ******* " << funnyMessage() << " *******" << std::endl;
    return log;
}

void player::printFleet() {
    for (auto & it : fleet) {
        std::cout << "center: " << it.first.getRow() << it.first.getCol() << "\t| ";
        std::cout << "bow: " <<it.second->getBow().getRow() << it.second->getBow().getCol() << "\t| ";
        std::cout << "stern: " <<it.second->getStern().getRow() << it.second->getStern().getCol() << std::endl;
    }
}

std::vector<std::pair<std::string, std::string>> player::startRandomFleet() {
    int dim = 5;
    char ch = 'C';

    std::vector<std::pair<std::string, std::string>> log;

    //START FLOTTA
    for (int i = 0; i < 8; ++i) {
        try{

            coords c1 = getRandomCoord();
            bool vtr = getRandomInt(99) % 2 == 0;
            coords c2 = getRandomCoord(c1, vtr, dim);
            //std::pair<coords, coords> input(c1, c2);
            //std::cout << c1 << " " << c2 << " " << vtr << " " << dim << std::endl;

            //CHECK E MATRIX INPUT
            ship s(c1,c2,dim);
            checkSpace(&s, s.getCenter());
            insertShip(s, ch);

            //FLEET INPUT
            newShip(s.getStern(), s.getBow(), ch);

            log.emplace_back(s.getBow().toString(), s.getStern().toString());

            if(i + 1 == 3 || i + 1 == 6) dim -= 2;
            if(i + 1 == 3) ch = 'S';
            if(i + 1 == 6) ch = 'E';

        }
        catch (coords::invalidCoords& c){
            std::cout << " ** invalid coordinates **" << std::endl;
            i--;
        }
        catch(notEnoughSpace& e){
            std::cout << " ** not enough space **" << std::endl;
            i--;
        }
        //std::cout << "-------------------" << std::endl;
        //visual();
    }
    std::cout << "\n******* " << funnyMessage() << " *******" << std::endl;
    return log;
}

//ACTIONS
//XX XX
void player::visual(){
    std::cout << std::endl;
    std::string name_ = "**** " + name + " ****";
    unsigned int rep = (106 - name.size()) / 2;      //(lunghezza della riga - nome.size()) / 2

    //52 + 4 + 52 = 108 -> caratteri della griglia in una riga 108 / 2 = 54 caratteri a metà
    //centro la scritta
    for (int i = 0; i < rep; i++) std::cout << " ";

    std::cout << name_ << std::endl;
    grid(defence, attack);
}

//AA AA
void player::deleteY(){
    coords c(0, 0);
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            c = coords(i, j);
            if(attack.getElement(c) == 'Y')
                attack.insert(c, ' ');
        }
    }
}

//XYorigin XYtarget
void player::action(coords origin, coords target, player& opponent){
    if (fleet.find(origin) == fleet.end())       //controlla che origin sia il centro di una delle sue navi
        throw invalidOrigin();
    ship* s = fleet.find(origin)->second;
    if (s->getDimension() == 5){             //azione corazzata
        fire(origin, target, opponent);
    }
    else if (s->getDimension() == 3){        //azione supporto
        moveAndRepair(origin, target);
    }
    else {                                   //azione sottomarino
        moveAndSearch(origin, target, opponent);
    }
    std::cout << "Mossa: " <<  origin << " -> " << target << std::endl;       //todo: RIMUOVERE MOSSA
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
                try {
                    if (s->isVertical())
                        c = target.add(i, j);
                    else
                        c = target.add(j, i);
                    if (wasHit(c)) {         //ogni volta che trova una lettera minuscola (NON appartenente al sottomarino)
                        repairFullShip(c);
                    }
                }
                catch (coords::invalidCoords& e){}
            }
        }
    }
}


//ripara l'intera nave a partire dalla coordinata di una delle sue unità
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


//restituisce un puntatore alla nave data UNA QUALSIASI delle sue coordinate    //TODO gestire c vuota
ship* player::getShipPointer(coords c){
    int dim = defence.getShipDim(c);        //dimensione della nave da riparare (in base alla lettera sulla griglia)
    //if(dim == 0)
    //    throw invalidOrigin();
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
            }
            catch (coords::invalidCoords &e) {}
        }
    }
    return s;
}


//azione del sottomarino
void player::moveAndSearch(coords origin, coords target, player& opponent){
    move(origin, target);  //lancia eccezione se non c'è spazio

    coords check = target;
    for (int i = -2; i <= 2; i++) {             //ciclo per le righe
        for (int j = -2; j <= 2; j++) {         //ciclo per le colonne
            try {
                check = target.add(i, j);
                if (opponent.isEmpty(check)) {        //se la cella dell'avversario è vuota
                    if (attack.getElement(check) != 'O')
                        attack.insert(check, ' ');              //rimuove eventuali X e Y precedenti non più valide
                } else {                                    //se la cella dell'avversario non è vuota
                    if (opponent.wasHit(check))
                        attack.insert(check, 'X');              //se trova una lettera minuscola mette X (segmento colpito)
                    else
                        attack.insert(check, 'Y');              //se trova una lettera maiuscola mette Y (segmento non colpito)
                }
            }
            catch (coords::invalidCoords& e){}
        }
    }
}


//CHECK SPACE
//controlla se c'è spazio per una nave
void player::checkSpace(ship* s, coords target){
    std::vector<char> v;
    int dim = s->getDimension();
    coords check;

    bool valid = true;
    try {
        for (int i = -dim/2; i <= dim/2 && valid; i++) {      //controllo spazio che serve
            if (s->isVertical())
                check = target.addRow(i);
            else
                check = target.addCol(i);

            if (!defence.isEmpty(check) && !s->contains(check))
                valid = false;
        }
    }catch(coords::invalidCoords& c){
        valid = false;
    }

    if (!valid)
        throw notEnoughSpace();     //eccezione non c'è spazio
}

//MOVE
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
    char c = defence.getElement(target);    //controlla che sia un carattere maiuscolo (unità non colpita), altrimenti non esegue nulla
    if(c == 'C' || c == 'S' || c == 'E') {
        defence.hit(target);
        ship *s = getShipPointer(target);
        s->removeLife();
        if (!s->isAlive()) {
            removeShip(s->getCenter());
        }
    }
}

ship* player::newShip(coords stern, coords bow, char c){
    ship* s = nullptr;
    if(c == 'C')
        s = new battleship(bow, stern);
    if(c == 'S')
        s = new support(bow, stern);
    if(c == 'E')
        s = new submarine(bow, stern);
    //fleet.insert(std::make_pair(s->getCenter(), s));      //uguale!!!
    fleet[s->getCenter()] = s;
    return s;
}

void player::removeShip(coords center){
    ship* s = fleet.find(center)->second;
    fleet.erase(center);        //rimuovo dalla flotta
    int dim = s->getDimension();
    for(int i = -dim/2; i <= dim/2; i++) {       //riscrittura defense
        if (s->isVertical())
            defence.insert(center.addRow(i), ' ');
        else
            defence.insert(center.addCol(i), ' ');
    }
}


//FUNZIONI STUPIDE NON GUARDARE SIAMO BRUTTE
int player::getShipLife(coords origin){
    if (fleet.find(origin) == fleet.end())       //controlla che origin sia il centro di una delle sue navi
        throw invalidOrigin();
    ship* s = fleet.find(origin)->second;
    return s->getLife();
}


//SETTERS
void player::insertShip(ship s, char c){
    coords center = s.getCenter();
    coords n_c = center;
    int dim = s.getDimension();
    for (int i = -dim/2; i <= dim/2; i++) {
        //std::cout << "new: " << n_c << std::endl;
        if (s.isVertical())
            n_c = center.addRow(i);
        else
            n_c = center.addCol(i);
        defence.insert(n_c, c);
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
    return message[rand() % message.size()];
}

coords player::getRandomOrigin(){
    //srand(rand());
    std::vector<coords> v;
    for(auto& iter: fleet) {
        v.push_back(iter.first);
    }
    coords c = v[rand()%v.size()];
    return c;
}



int player::getPoints(){
    int points = 0;
    for(auto& iter: fleet){
        points += iter.second->getLife();
    }
    return points;
}


std::string player::findY(){
    std::string s;
    std::vector<coords> v;
    for(int i = 0; i < 12; i++){
        for (int  j = 0; j < 12; j++){
            coords c(i, j);
            if(attack.getElement(c) == 'Y')
                v.push_back(c);
        }
    }
    if(!v.empty()){
        coords randomY = v[getRandomInt(v.size())];
        s = randomY.toString();
    }
    return s;
}


bool player::isABattleship(coords origin){
    ship* s = fleet.find(origin)->second;
    if (s->getDimension() == 5)
        return true;
    return false;
}

//FUNZIONI RANDOM
coords player::getRandomCoord(){
    coords c = {getRandomInt(12), getRandomInt(12)};
    //std::cout << "estrazione-> " << c << std::endl;        //todo: remove
    return c;
}

coords player::getRandomCoord(coords bow, bool vertical, int distance){ //prende in input la PRUA!
    coords newCoord = coords(bow.getX(), bow.getY());
    distance--;

    //check se sommare o sottrarre
    if(bow.getX() - distance > 0 || bow.getY() - distance > 0) distance *= (-1);

    //mofica della nuova coordinata
    if (vertical) newCoord = newCoord.add(distance, 0);
    else newCoord = newCoord.add(0, distance);
    std::cout << "nuova nave-> " << newCoord << std::endl;       //todo: rimuovere

    return newCoord;
}

int player::getRandomInt(int range, int start){
    srand(rand());
    int random = start + (rand() % range);
    return random;
}

int player::getSumShipLife() {
    int tot_life = 0;
    for (auto& iter: fleet) {
        tot_life += iter.second->getLife();
    }
    return tot_life;
}




