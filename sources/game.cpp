//Matteo Piras and Claudia De Carlo

#include "../headers/game.h"

void game::start_menu(){
    char ch;
    bool ok = true;
    while(ok){
        std::cout << "*** START MENU ***" << std::endl;
        std::cout << "s - inizia partita " << std::endl;
        std::cout << "i - info" << std::endl;
        //std::cout << "c - crediti" << std::endl;
        std::cin >> ch;
        switch (ch) {
            case 's':
                std::cout << "START GAME" << std::endl;
                ok = false;
                break;
            case 'i':
                std::cout << "\t** INFORMAZIONI UTILI **" << std::endl;
                std::cout << "Lettere che rappresentano le navi: " << std::endl;
                std::cout << "-> il carattere 'C' rappresenta una corazzata armata" << std::endl;
                std::cout << "-> il carattere 'S' rappresenta una nave di supporto " << std::endl;
                std::cout << "-> il carattere 'E' rappresenta un sottomarino di esplorazione" << std::endl;
                std::cout << "-> NB: le navi colpite sono rappresentate dalla rispettiva lettera minuscola" << std::endl;
                std::cout << "\nMosse delle navi: " << std::endl;
                std::cout << "-> dopo un movimento del sottomarino questo scannerizza in un'area 5x5, nella griglia di attacco comparirà una 'Y' che senga le navi individuate" << std::endl;
                std::cout << "-> dopo un movimento della nave di supporto questa cura totalmente le navi alleate in un'area 5x5" << std::endl;
                std::cout << "\nCaratteri speciali: " << std::endl;
                std::cout << "-> con il comando 'XX XX' puoi visualizzare le tue griglie " << std::endl;
                std::cout << "-> con il comando 'AA AA' puoi cancellare tutti gli avvistamenti sonar ('Y') dalla griglia di attacco " << std::endl;

                ok = false;
                break;
//            case 'c':
//                std::cout << "" << std::endl;
//                ok = false;
//                break;
            default:
                break;
        }
    }
}

//Array di pair
std::vector<std::pair<coords, coords>> game::read_file(){        //!DA TESTARE
    std::vector<std::pair<coords, coords>> read_coords;         //vettore per la lettura delle coordinate
    std::ifstream inFile("../file/log.txt");      //apertura del file ("../" serve per cercare in automatico il percorso del file)

    if (!inFile) {      //controllo corretta apertura
        std::cout << "Errore di apertura del file" << std::endl; // controllo
    } else {
        //lettura delle mosse dal file log
        std::string str, start;
        std::string delimiter = " ";

        while (std::getline(inFile, str)){
            //estraggo start
            start = str.substr(0, str.find(delimiter));     //estraggo dalla lettura la mossa di partenza
            str.erase(0, str.find(delimiter) + delimiter.length());     //cancello dalla string la mossa di partenza estrapolando la mossa di destinazione
            coords first (start);       //creo l'oggetto partendo dalla prima stringa
            coords second (str);        //creo l'oggetto partendo dalla seconda stringa
            read_coords.emplace_back(first, second);        //salvo la composizione degli oggetti nell'array
        }
    }

    inFile.close(); //chiusura del collegamento
    return read_coords;
}

bool game::write_file() {    //!DA FINIRE E VEDERE COSA PRENDE IN INPUT
    std::ofstream outFile; // Dichiarazione di tipo
    bool finish = false;
    //OutFile.open("file.txt", std::ios::app); // Apertura del file con sovrascrittura
    outFile.open("file.txt"); // Apertura del file senza sovrascrittura
    if (!outFile) {
        std::cout << "Errore di apertura del file" << std::endl; // controllo
    } else {
        //codice per la scrittura su file
        //! OutFile << std::endl;       //inserisco nel file (comando per inserimento outFile::)
        finish = true;
    }

    outFile.close();
    return finish;
}


//FUNZIONI TURNI
std::pair<std::string, std::string> game::computerRound(player& pl, player& opponent) {
    //nave random da p1.fleet e salva in origin
    coords origin = pl.getRandomOrigin();
    coords target = origin; //inizializzazione provvisoria
    //(AA AA ?)
    bool done = false;
    //finché non trova coords target valide per l'azione)
    while (!done) {
        if(pl.isABattleship(origin)) {
            std::string targ = pl.findY();
            if (targ != "")
                target = coords(targ);
        }
        else
            target = pl.getRandomCoord();
        try {       //try catch azione
            pl.action(origin, target, opponent);      //coordinate random
            done = true;
        }
        catch (coords::invalidCoords &e) {}
        catch (player::notEnoughSpace &e) {}
        catch (player::invalidOrigin &e) {}
    }
    std::pair<std::string, std::string> c = std::make_pair(origin.toString(), target.toString());
    return c;
}

std::pair<std::string, std::string> game::humanRound(player& pl, player& opponent) {
    std::string origin;
    std::string target;
    bool done = false;

    while (!done) {
        try {
            //legge la mossa come stringa e salva in origin e target
            std::cout << ">> ";
            std::cin >> origin >> target;

            //if AA AA  cancella le Y da attack e salva su log
            if (origin == "AA" && target == "AA") {
                //chiede e legge nuova mossa e salva in move
                pl.deleteY();
            }
            //if XX XX  stampa le griglie DI P2
            else if (origin == "XX" && target == "XX") {
               //stampa
                pl.visual();
                //chiede e legge nuova mossa e salva in move
            } else {

                if(origin == "YY" && target == "YY") opponent.visual();     //todo: RIMUOVERE ASSOLUTAMENTE if - else!!!!!!
                else{
                    //chiama l'azione (altrimenti propaga eccezione)
                    pl.action(origin, target, opponent);
                    //se non ha lanciato l'eccezione salvo la mossa su hystory
                    //todo: salvare su history le mosse
                    //salva roundFlag, origin, target su log
                    done = true;
                }
            }
        }
        catch (coords::invalidCoords& e) {
            //le coordinate non sono valide
            // chiede di riprovare (done = false)
            std::cout << ">> coordinate non valide!" << std::endl;
        }
        catch (player::invalidOrigin& e) {
            //l'origine non corrisponde a nessuna nave
            std::cout << ">> errore nella selezione della nave!" << std::endl;
        }
        catch (player::notEnoughSpace& e) {
            //non c'è spazio per spostare la nave
            std::cout << ">> non possiamo spostarci in quella direzione capitano!" << std::endl;
        }
    }
    std::pair<std::string, std::string> c = std::make_pair(origin, target);
    return c;
}

//TURNI
void game::create_players(bool human, player &p1, player &p2){
    //crea i giocatori
    if(human){
        std::cout << "Inserisci il tuo nome! \n>>";
        std::string name;           //todo: sistemare
        std::getline(std::cin, name);
        //std::cin >> name;
        p2.setName(name);
        p1.setName("Computer");
    }
    else{
        p1.setName("Giocatore 1");
        p2.setName("Giocatore 2");
    }
}

void game::start_game(bool human){
    //VARIABILI
    const int maxRounds = 40;       //bisogna farlo settare al giocatore?
    //vettore log per salvare tutte le mosse (bool, coords, coords) | (player1, origin, target)
    std::vector<std::pair<std::string, std::string>> log;
    //creare giocatori p1 e p2
    player p1, p2;      //p1 sempre computer
    std::pair<std::string, std::string> move;   //per le mosse decise


    //creazione dei giocatori
    create_players(human, p1, p2);

    p1.startRandomFleet();                          //todo: sistemare output a schermo

    //posizionare navi p2 (A random | B cout/cin)
    std::vector<std::pair<std::string, std::string>> logTemp;
    if(human){
        if(p2.getName() == "admin") logTemp = p2.startRandomFleet();        //todo: RIMUOVERE ASSOLUTAMENTE!!!!
        else logTemp = p2.startFleet();
    }
    else {
        logTemp = p2.startRandomFleet();
    }

    for(int i = 0; i < logTemp.size(); i++){
        log.push_back(logTemp[i]);
    }

    print(p1, p2);

    //sorteggio primo giocatore: p1: roundP1 = true, p2: roundP1 = false        //(p1 = 1, p2 = 0)
    bool roundP1 = false;
    if (rand()%2 == 1) {
        roundP1 = true;
        log.emplace_back("P", "1");
    }
    else
        log.emplace_back("P", "2");

    std::cout << "\nINIZIA IL GIOCATORE: ";
    if(roundP1)
        std::cout << p1.getName() << std::endl;
    else
        std::cout << p2.getName() << std::endl;


    for (int i = 0; i < maxRounds && p1.isAlive() && p2.isAlive(); ++i) {
        if(roundP1) {     //round P1 (computer)
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p1.getName() << std::endl;
            move =  game::computerRound(p1, p2);
        }
        else{              //round P2
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p2.getName() << std::endl;
            if(human){
                move = game::humanRound(p2, p1);
            }
            else {
                move = game::computerRound(p2, p1);
            }
        }

        std::string s = move.first;
        if(s != "AA" && s != "XX") {
            log.push_back(move);
            //cout << origin << " -> " << target << endl;
            //cout << std::get<0>(log[i]) << " " << std::get<1>(log[i]) << " " << std::get<2>(log[i]);

            roundP1 = !roundP1;
        }

        std::cout << std::endl;
        //sleep(1);
    }

    //FINE PARTITA

    for(auto& iter: log){       //stampa delle mosse fatte fino alla i-esima ripetizione
        std::cout << iter.first << " -> " << iter.second;
        std::cout << std::endl;
    }
    //if p1 è morto
    if(!p1.isAlive()){
        //P1 HA PERSO SFIGATO è MORTO
        std::cout << "IL VINCITORE E': " + p2.getName() << std::endl;
    }
        //if p2 è morto
    else if(!p2.isAlive()){
        //P2 HA PERSO SFIGATO è MORTO
        std::cout << "IL VINCITORE E': " + p1.getName() << std::endl;
    }
        //if mosse finite: confronto "punteggi" (unità vive)
    else{
        std::cout << "LA PARTITA E' FINITA IN PAREGGIO!" << std::endl;
        //PAREGGIO
        //punti?
    }

    std::cout << "*** TOTALE DANNI INFLITTI ***" << std::endl;
    std::cout << ">> " + p1.getName() + ": " << p1.getSumShipLife() << std::endl;
    std::cout << ">> " + p2.getName() + ": " << p2.getSumShipLife() << std::endl;

}


/*
std::tuple<bool, std::string, std::string> game::turn(bool human, bool roundP1, player p1, player p2, unsigned int i) {           //funzione per un turno
    std::tuple<bool, std::string, std::string> tuple;
    std::pair<std::string, std::string> move;   //per le mosse decise

    std::string origin, target;

    if(roundP1) {     //round P1 (computer)
        std::cout << " ** TURNO " << i+1 << ":  TOCCA A " << p1.getName() << std::endl;
        move =  game::computerRound(p1, p2);
    }
    else{              //round P2
        std::cout << "TURNO " << i+1 << ":  TOCCA A " << p2.getName() << std::endl;
        if(human){
            move = game::humanRound(p2, p1);
        }
        else {
            move = game::computerRound(p2, p1);
        }
    }

    origin = move.first;
    target = move.second;

    if(origin != "AA" && origin != "XX") {
        origin = move.first;
        target = move.second;
        tuple = std::make_tuple(roundP1,origin, target);        //inserisco nella tupla
        //log.emplace_back(roundP1, origin, target);
        //cout << origin << " -> " << target << endl;
        //cout << std::get<0>(log[i]) << " " << std::get<1>(log[i]) << " " << std::get<2>(log[i]);

        roundP1 = !roundP1;
    }
    //print(p1, p2);

    return tuple;

}
void game::start_game(bool human) {
    //settare human

    const int maxRounds = 40;       //bisogna farlo settare al giocatore?
    std::string origin;
    std::string target;

    //creare giocatori p1 e p2
    player p1, p2;      //p1 sempre computer
    if(human){
        std::cout << "Inserisci il tuo nome!" << std::endl;
        std::string name;
        std::cin >> name;
        p2.setName(name);
        p1.setName("Computer");
    }
    else{
        p1.setName("Giocatore 1");
        p2.setName("Giocatore 2");
    }

    //vettore log per salvare tutte le mosse (bool, coords, coords) | (player1, origin, target)
    std::vector<std::tuple<bool, std::string, std::string>> log;

    //posizionare navi p1 random
    log = p1.startRandomFleet();

    //posizionare navi p2 (A random | B cout/cin)
    if(human){
        p2.startFleet();
    }
    else {
        p2.startRandomFleet();
    }

    //print(p1, p2);

    //sorteggio primo giocatore: p1: roundP1 = true, p2: roundP1 = false        //(p1 = 1, p2 = 0)
    bool roundP1 = false;
    if (rand()%2 == 1)
        roundP1 = true;
    std::cout << "\nINIZIA IL GIOCATORE: ";
    if(roundP1)
        std::cout << p1.getName() << std::endl;
    else
        std::cout << p2.getName() << std::endl;

    std::string prova = "Ciao";

    //turni
    for (int i = 0; i < maxRounds && p1.isAlive() && p2.isAlive(); i++){        //ciclo per i turni -> chiamo la funzione turn
        log.emplace_back(game::turn(human, roundP1, p1, p2, i));
    }

    std::cout << " ***********" << std::endl;

    for(auto& iter: log){
        std::cout << std::get<0>(iter) << " " << std::get<1>(iter) << " " << std::get<2>(iter);
        std::cout << std::endl;
    }

    //FINE PARTITA
    //if p1 è morto
    if(!p1.isAlive()){
        //P1 HA PERSO SFIGATO è MORTO
        std::cout << "IL VINCITORE E': " + p2.getName();
    }
        //if p2 è morto
    else if(!p2.isAlive()){
        //P2 HA PERSO SFIGATO è MORTO
        std::cout << "IL VINCITORE E': " + p1.getName();
    }
        //if mosse finite: confronto "punteggi" (unità vive)
    else{
        //PAREGGIO
        //punti?
    }
}*/

void game::print(player p1, player p2){
    std::string n1 = p1.getName();
    std::string n2 = p2.getName();
    p1.visual();
    std::cout << "FLOTTA: " << std::endl;
    for(auto& iter: p1.fleet) {
        coords c = iter.first;
        std::cout << c << ": " << *iter.second << std::endl;
    }

    sleep(1);
    p2.visual();
    std::cout << "FLOTTA: " << std::endl;
    for(auto& iter: p2.fleet) {
        coords c = iter.first;
        std::cout << c << ": " << *iter.second << std::endl;
    }
    std::cout << std::endl;
    sleep(1);
}


/*
game::turn::turn() {
    char input;
    bool ok = true;
    while(ok) {
        std::cout << "** SELEZIONA LA DIFFICOLTA' ** \n";
        std::cout << "1 - Facile (100 turni)\n";
        std::cout << "2 - Medio (60 turni)\n";
        std::cout << "3 - Difficile (30 turni)\n";
        std::cout << "-> ";
        std::cin >> input;
        switch (input) {
            case '1': {
                MAX_TURN = 100;
                ok = false;
                break;
            }
            case '2': {
                MAX_TURN = 60;
                ok = false;
                break;
            }
            case '3': {
                MAX_TURN = 30;
                ok = false;
                break;
            }
            default: {
                std::cout << "\n** input non valido! **" << std::endl;
                break;
            }
        }
    }
    std::cout << MAX_TURN << std::endl;
}*/
