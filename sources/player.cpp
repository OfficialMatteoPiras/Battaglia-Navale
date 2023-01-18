// Claudia De Carlo

#include "../headers/player.h"

//costruttori
player::player() {
    name = "Player";
    fleet = {};
}

player::player(const std::string& n){
    name = n;
    fleet = {};
}

//getters
int player::getPoints() const{
    int points = 0;
    for(auto& iter: fleet){
        points += iter.second->getLife();
    }
    return points;
}

bool player::isABattleship(const coords& origin) const{
    ship* s = fleet.find(origin)->second;
    if (s->getDimension() == 5)
        return true;
    return false;
}

coords player::getRandomOrigin() const{
    //srand(rand());
    std::vector<coords> v;
    for(auto& iter: fleet) {
        v.push_back(iter.first);
    }
    coords c = v[rand()%v.size()];
    return c;
}

std::string player::getRandomY() const{
    std::string s;
    std::vector<coords> v = attack.findLetter('Y');
    if(!v.empty()){
        coords randomY = v[random::getRandomInt(v.size())];
        s = randomY.toString();
    }
    return s;
}

//setters
void player::hit(const coords& target) {
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

//inizializzazione flotta
std::vector<std::pair<coords, coords>> player::startFleet() {

    //todo: usare la funzione newShip();
    int dim = 5, cont = 1;
    unsigned int dif;
    char ch = 'C';

    std::pair<coords, coords> input = {};
    std::vector<std::pair<coords, coords>> log;

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
            checkSpace(&s, s.getCenter(), false);
            insertShip(s, ch);

            //FLEET INPUT
            newShip(s.getStern(), s.getBow(), ch);
            log.emplace_back(input.first, input.second);

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

std::vector<std::pair<coords, coords>> player::startRandomFleet() {
    int dim = 5;
    char ch = 'C';
    std::vector<std::pair<coords, coords>> log;

    //START FLOTTA
    for (int i = 0; i < 8; ++i) {
        try{
            coords c1 = random::getRandomCoord();
            bool vtr = random::getRandomInt(99) % 2 == 0;
            coords c2 = random::getRandomCoord(c1, vtr, dim);

            //CHECK E MATRIX INPUT
            ship s(c1,c2,dim);
            checkSpace(&s, s.getCenter(), false);
            insertShip(s, ch);

            //FLEET INPUT
            newShip(s.getStern(), s.getBow(), ch);
            log.emplace_back(s.getBow(), s.getStern());

            if(i + 1 == 3 || i + 1 == 6) dim -= 2;
            if(i + 1 == 3) ch = 'S';
            if(i + 1 == 6) ch = 'E';

        }
        catch (coords::invalidCoords& c){
            i--;
        }
        catch(notEnoughSpace& e){
            i--;
        }
    }
    return log;
}

void player::printFleet() {
    std::string ship_name, tab;
    std::cout << "FLOTTA: " << std::endl;
    for (auto &iter: fleet) {
        if(iter.second->getDimension() == 5) ship_name = "Corazzata";
        if(iter.second->getDimension() == 3) ship_name = "Nave di supporto";
        if(iter.second->getDimension() == 1) ship_name = "Sottomarino";

        tab = ship_name.size() > 11 ? "\t" : "\t\t";
        std::cout << ship_name << ": " << tab << *iter.second << std::endl;
    }
}

//comandi
void player::action(const coords& origin, const coords& target, player& opponent, bool replay){
    if (fleet.find(origin) == fleet.end())       //controlla che origin sia il centro di una delle sue navi
        throw invalidOrigin();
    ship* s = fleet.find(origin)->second;
    if (s->getDimension() == 5){             //azione corazzata
        fire(target, opponent);
    }
    else if (s->getDimension() == 3){        //azione supporto
        moveAndRepair(origin, target);
    }
    else {                                   //azione sottomarino
        moveAndSearch(origin, target, opponent);
    }

    if(replay) std::cout << "Mossa: " <<  origin << " -> " << target << std::endl;          //se è in corso un replay fa vedere la mossa fatta
}

void player::visual(){
    //std::cout << std::endl;
    std::string name_ = "**** " + name + " ****";
    unsigned int rep = (102 - name.size()) / 2;      //(lunghezza della riga - nome.size()) / 2

    //centro la scritta
    for (int i = 0; i < rep; i++) std::cout << " ";

    std::cout << name_ << std::endl;
    grid(defence, attack);
}

void player::deleteY(){
    std::vector<coords> v = attack.findLetter('Y');
    for(int i = 0; i < v.size(); i++){
        attack.insert(v[i], ' ');
    }
}

void player::deleteX(){
    std::vector<coords> v = attack.findLetter('X');
    for(int i = 0; i < v.size(); i++){
        attack.insert(v[i], ' ');
    }
}

void player::deleteO(){
    std::vector<coords> v = attack.findLetter('O');
    for(int i = 0; i < v.size(); i++){
        attack.insert(v[i], ' ');
    }
}

//messaggi output
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


//FUNZIONI PROTECTED
//*azioni*
//azione della corazzata
void player::fire(const coords& target, player& opponent){
    if(opponent.isEmpty(target)){       // acqua
        attack.insert(target, 'O');
    }
    else{                               // fuoco
        opponent.hit(target);
        attack.insert(target, 'X');
    }
}

//azione della nave di supporto
void player::moveAndRepair(const coords& origin, const coords& target){
    move(origin, target);   //lancia eccezione se non c'è spazio

    ship* s = fleet.find(target)->second;
    coords c;
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

//azione del sottomarino di esplorazione
void player::moveAndSearch(const coords& origin, const coords& target, player& opponent){
    move(origin, target);  //lancia eccezione se non c'è spazio

    coords check;
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

//*funzioni di supporto alle azioni*
//controlla se c'è spazio per inserire una nave (se non c'è lancia notEnoughSpace())
void player::checkSpace(ship* s, const coords& target, bool alreadyExists){
    int dim = s->getDimension();
    coords check;

    bool valid = true;
    try {
        for (int i = -dim/2; i <= dim/2 && valid; i++) {      //controllo spazio che serve
            if (s->isVertical())
                check = target.addRow(i);
            else
                check = target.addCol(i);

            if(alreadyExists) {
                if (!defence.isEmpty(check) && !s->contains(check))
                    valid = false;
            } else {
                if (!defence.isEmpty(check))
                    valid = false;
            }
        }
    }catch(coords::invalidCoords& c){
        valid = false;
    }

    if (!valid)
        throw notEnoughSpace();     //eccezione non c'è spazio
}

//sposta una nave QUALSIASI da origin a target, lancia eccezione se non c'è spazio
void player::move(const coords& origin, const coords& target) {
    std::vector<char> v;
    ship* s = fleet.find(origin)->second;
    checkSpace(s, target, true);

    int dim = s->getDimension();
    //copia la nave in un vettore e la cancella da defence
    for(int i = -dim/2; i <= dim/2; i++){
        if(s->isVertical()) {
            v.push_back(defence.getElement(origin.addRow(i)));
            defence.insert(origin.addRow(i), ' ');
        } else {
            v.push_back(defence.getElement(origin.addCol(i)));
            defence.insert(origin.addCol(i), ' ');
        }
    }
    //inserisce la nave nella nuova posizione
    for(int i = -dim/2; i <= dim/2; i++){
        if(s->isVertical())
            defence.insert(target.addRow(i), v[i+dim/2]);
        else
            defence.insert(target.addCol(i), v[i+dim/2]);
    }

    s->moved(target);

    fleet.erase(origin);
    fleet.insert(std::make_pair(target, s));
}

//restituisce un puntatore alla nave data UNA QUALSIASI delle sue coordinate    //TODO gestire c vuota
ship* player::getShipPointer(const coords& c){
    int dim = defence.getShipDim(c);        //dimensione della nave da riparare (in base alla lettera sulla griglia)
    //if(dim == 0)
    //    throw invalidOrigin();
    coords center;
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
                    //verifica se quella cella appartiene alla nave
                    found = s->contains(c);
                }
            }
            catch (coords::invalidCoords& e) {}
        }
    }
    return s;
}

//ripara l'intera nave a partire dalla coordinata di una delle sue unità
void player::repairFullShip(const coords& c){
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

//controlla se l'unità in target è stata colpita
bool player::wasHit(const coords& target){
    char c = defence.getElement(target);
    return c == 'c' || c == 's' || c == 'e';
}

//rimuove una nave dalla flotta e dalla griglia di difesa
void player::removeShip(const coords& center){
    ship* s = fleet.find(center)->second;
    int dim = s->getDimension();
    for(int i = -dim/2; i <= dim/2; i++) {       //riscrittura defense
        if (s->isVertical())
            defence.insert(center.addRow(i), ' ');
        else
            defence.insert(center.addCol(i), ' ');
    }
    fleet.erase(center);        //rimozione dalla flotta
    delete s;
}

//inserisce la nave s nella griglia di difesa
void player::insertShip(ship& s, char c){
    coords center = s.getCenter();
    coords n_c;
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

//crea una nave e la inserisce nella flotta
ship* player::newShip(const coords& stern, const coords& bow, char c){
    ship* s = nullptr;
    if(c == 'C')
        s = new battleship(bow, stern);
    if(c == 'S')
        s = new support(bow, stern);
    if(c == 'E')
        s = new submarine(bow, stern);
    if(s != nullptr)
        fleet[s->getCenter()] = s;
    return s;
}



//*input coordinate*
std::pair<coords, coords> player::getCoords(const std::string& message){
    std::string origin, target, delimiter = " ";
    //input
    std::cout << message << ": ";
    std::cin >> origin >> target;

    return {{origin},{target}};
}

std::string player::funnyComputerMessage() {
    srand(rand());
    std::vector<std::string> message = {        //NB: gli spazi vuoti sono voluti, servono a non far stampare ad ogni turno un messaggio
            "COLPITO OPPURE NO? CHI LO SA...",
            "",
            "ATTENTO! IL MARE E' DALLA NOSTRA PARTE!",
            "",
            "I MIEI CANNONI SONO PUNTATI SULLE TUE NAVI, STAI ATTENTO!",
            "*RISATA MALVAGIA*",
            "",
            "*SOFFIO DI VENTO*",
            "SO CHE SEI LI DA QUALCHE PARTE!",
            "POSSO SENTIRE LA TUA PAURA!",
            "",
            "LE MIE NAVI POSSONO CONTINUARE COSI' TUTTO IL GIORNO!",
    };
    return message[rand() % message.size()];
}