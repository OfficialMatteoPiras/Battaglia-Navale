//Claudia De Carlo

#include "../headers/game.h"

void game::start_menu(){
    char ch;
    bool done = false;
    while(!done){
        std::cout << "\n*** START MENU ***" << std::endl;
        std::cout << "s - inizia partita " << std::endl;
        std::cout << "i - info" << std::endl;
        std::cout << "e - esci" << std::endl;
        std::cout << ">>";
        std::cin >> ch;
        switch (ch) {
            case 's':       //inizia la partita
                std::cout << "START GAME" << std::endl;
                std::cin.ignore();
                game::start_game(true);
                done = true;
                break;
            case 'i':   //info sul gioco
                std::cout << "\n*** INFORMAZIONI UTILI ***" << std::endl;
                std::cout << "Regole del gioco:" << std::endl;
                std::cout << "-> Ogni giocatore, a turno, compie un'azione usando una delle sue otto navi \n   (identificata dalla coordinata del suo centro) e fornendo le coordinate di target." << std::endl;
                std::cout << "-> I tre tipi di navi compiono azioni diverse:" << std::endl;
                std::cout << "\t- la corazzata fa fuoco sulle coordinate di target nel campo avversario; nella griglia di attacco compare \n\t  una X se il colpo va a buon fine, altrimenti una O;" << std::endl;
                std::cout << "\t- la nave di supporto si sposta sulle coordinate ricevute e cura interamente tutte le navi alleate avvistate \n\t  in un'area 3x3 di cui e' il centro;" << std::endl;
                std::cout << "\t- il sottomarino si sposta sulle coordinate ricevute e lancia un impulso sonar che rileva le navi nemiche \n\t  in un'area 5x5; nella griglia di attacco compare una Y per segnare le unita' individuate;" << std::endl;
                std::cout << "\nComandi speciali:" << std::endl;
                std::cout << "- con il comando XX XX puoi visualizzare le tue griglie" << std::endl;
                std::cout << "- con il comando AA AA puoi cancellare tutti gli avvistamenti sonar (Y) dalla griglia di attacco" << std::endl;
                std::cout << "- con il comando BB BB puoi cancellare tutti i colpi andati a segno (X) dalla griglia di attacco" << std::endl;
                std::cout << "- con il comando CC CC puoi cancellare tutti i colpi a vuoto (O) dalla griglia di attacco" << std::endl;
                std::cout << "\nVisualizzazione:" << std::endl;
                std::cout << "-> Griglia di difesa (a sinistra) :" << std::endl;
                std::cout << "\t- il carattere C rappresenta una corazzata armata" << std::endl;
                std::cout << "\t- il carattere S rappresenta una nave di supporto" << std::endl;
                std::cout << "\t- il carattere E rappresenta un sottomarino di esplorazione" << std::endl;
                std::cout << "\tNB: le navi colpite sono rappresentate dalla rispettiva lettera minuscola" << std::endl;
                std::cout << "-> Griglia di attacco (a destra):" << std::endl;
                std::cout << "\t- il carattere X rappresenta un colpo andato a segno" << std::endl;
                std::cout << "\t- il carattere O rappresenta un colpo a vuoto" << std::endl;
                std::cout << "\t- il carattere Y rappresenta una nave individuata dal sonar" << std::endl;
                break;
            case 'e':
                done = true;
                break;
            default:
                std::cout << "** Impossibile eseguire la richiesta, errore nell'inserimento! **" << std::endl;
                break;
        }
    }
}


std::pair<std::string, std::string> game::computerRound(player& pl, player& opponent) {
    coords origin = pl.getRandomOrigin();
    coords target;
    bool done = false;
    //ripete il ciclo finché non trova coords target valide per l'azione
    while (!done) {
        if(pl.isABattleship(origin) && !pl.getRandomY().empty())
            target = coords(pl.getRandomY());
        else
            target = randomFunction::getRandomCoord();
        try {       //try catch azione
            pl.action(origin, target, opponent);
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

            //if AA AA: cancella le Y da attack
            if (origin == "AA" && target == "AA") {
                pl.deleteY();
            }
            //if BB BB: cancella le X da attack
            else if (origin == "BB" && target == "BB") {
                pl.deleteX();
            }
            //if CC CC: cancella le O da attack
            else if (origin == "CC" && target == "CC") {
                pl.deleteO();
            }
            //if XX XX: stampa le griglie di pl
            else if (origin == "XX" && target == "XX") {
               //stampa
                pl.visual();
            }
            //if QQ QQ: torna al chiamante (start_game) che interrompe la partita
            else if (origin == "QQ" && target == "QQ") {
                done = true;
            }
            else {
                if(origin == "YY" && target == "YY" && pl.getName() == "#admin")
                    opponent.visual();      //nella modalità amministratore è possibile visualizzare le griglie dell'avversario
                else{
                    pl.action(origin, target, opponent);        //chiama l'azione (propaga eccezione)
                    done = true;
                }
            }
        }
        catch (coords::invalidCoords& e) {
            std::cout << ">> coordinate non valide!" << std::endl;
        }
        catch (player::invalidOrigin& e) {
            std::cout << ">> errore nella selezione della nave!" << std::endl;
        }
        catch (player::notEnoughSpace& e) {
            std::cout << ">> non possiamo spostarci in quella direzione, capitano!" << std::endl;
        }
    }
    std::pair<std::string, std::string> c = std::make_pair(origin, target);
    return c;
}


void game::create_players(bool human, player &p1, player &p2){
    if(human){
        std::cout << "Inserisci il tuo nome! \n>>";
        std::string name;
        getline(std::cin, name);
        p2.setName(name);
        p1.setName("Computer");
    }
    else{
        p1.setName("Giocatore 1");
        p2.setName("Giocatore 2");
    }
}

void game::start_game(bool human){
    const int MAX_ROUNDS = 100;       //numero massimo round per la partita CC
    std::vector<std::pair<coords, coords>> log;   //vettore log per salvare tutte le mosse (player1, origin, target)
    std::pair<std::string, std::string> move;   //per salvare le mosse effettuate

    //crea i giocatori p1 e p2
    player p1, p2;      //p1 sempre computer
    create_players(human, p1, p2);

    //posiziona le navi
    std::vector<std::pair<coords, coords>> logMovesOne, logMovesTwo;
    logMovesOne = p1.startRandomFleet();
    if(human){
        if(p2.getName() == "#admin") logMovesTwo = p2.startRandomFleet();
        else logMovesTwo = p2.startFleet();
        std::cout << player::funnyMessage() << std::endl;
    }
    else {
        logMovesTwo = p2.startRandomFleet();
    }

    //salva le navi del giocatore 1
    for(const auto & i : logMovesOne){
        log.push_back(i);
    }
    //salva le navi del giocatore 2
    for(const auto & i : logMovesTwo){
        log.push_back(i);
    }
    print(p1, p2, human);

    //sorteggio del primo giocatore (p1: roundP1 = true, p2: roundP1 = false)
    bool roundP1 = false;
    if (rand()%2 == 1)
        roundP1 = true;
    const bool firstPlayer = roundP1;
    std::cout << "\nINIZIA IL GIOCATORE: ";
    std::cout << (roundP1 ? p1.getName() : p2.getName()) << std::endl;

    bool done = false;
    for (int i = 0; i < MAX_ROUNDS && !done && p1.isAlive() && p2.isAlive(); ++i) {
        std::cout << std::endl;
        //round P1 (computer)
        if(roundP1) {
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p1.getName() << std::endl;
            move = game::computerRound(p1, p2);
            if(human) std::cout << player::funnyComputerMessage() << std::endl;        //stampa un messaggio divertente randomicamente
            else p1.visual();
        }
        //round P2
        else{
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p2.getName() << std::endl;
            if(human)
                move = game::humanRound(p2, p1);
            else {
                move = game::computerRound(p2, p1);
                p2.visual();
            }
        }
        std::string s = move.first;
        if(s == "QQ")
            done = true;
        if(s != "XX" && s != "AA" && s != "BB" && s != "CC" && s != "QQ") {
            log.emplace_back(move);
            roundP1 = !roundP1;
        }

        if(!human)
            std::cout << "Mossa: " << log[i+16].first << " -> " << log[i+16].second << std::endl;        //stampa la mossa se è una partita CC

        std::cout << std::endl;

        sleep(1);         //timer
    }

    //FINE PARTITA
    //if p1 ha perso
    if(!p1.isAlive()){
        std::cout << "IL VINCITORE E': " + p2.getName() << std::endl;
    }
    //if p2 ha perso
    else if(!p2.isAlive()){
        std::cout << "IL VINCITORE E': " + p1.getName() << std::endl;
    }
    //if p2 si è arreso
    else if(done){
        std::cout << p2.getName() << " SI E' ARRESO!" << std::endl;
    }
    //if mosse finite: pareggio
    else{
        std::cout << "LA PARTITA E' FINITA IN PAREGGIO!" << std::endl;
    }

    std::cout << "*** UNITA' SOPRAVVISSUTE AI DANNI INFLITTI ***" << std::endl;
    std::cout << ">> " + p1.getName() + ": " << p1.getPoints() << std::endl;
    std::cout << ">> " + p2.getName() + ": " << p2.getPoints() << std::endl;

    //salvataggio della partita
    std::string file_name = human ? "logPC" : "logCC";
    game::write_game(file_name, firstPlayer, p1.getName(), p2.getName(), log);
}


void game::print(player& p1, player& p2, bool human){
    std::string n1 = p1.getName();
    //stampa la flotta di P1 solo nella partita CC
    if(!human){
        p1.visual();        //P1 sempre computer
        p1.printFleet();
        std::cout << std::endl;
        sleep(1);
    }
    //stampa la flotta di P2
    std::string n2 = p2.getName();
    p2.visual();
    p2.printFleet();
    std::cout << std::endl;
    sleep(1);
}

void game::write_game(const std::string &out_file, bool firstPlayer, std::string name1, std::string name2, std::vector<std::pair<coords, coords>>& vector) {
    std::ofstream outFile;              // Dichiarazione di tipo
    std::string path = "../file/" + out_file;      //creazione del percorso per il salvataggio

    if(path.find(".txt") == std::string::npos)
        path += ".txt";      //se non trova l'estensione la aggiunge

    outFile.open(path);             // Apertura del file senza sovrascrittura
    if (!outFile) {
        std::cout << "Errore di apertura del file" << std::endl;         // controllo
    } else {
        outFile << (firstPlayer ? 1 : 0) << std::endl;
        outFile << name1 << std::endl;
        outFile << name2 << std::endl;
        for (auto & i : vector) {       //scorro il vettore per scrivere nel nuovo file
            outFile << i.first << " " << i.second << std::endl;
        }
    }
    outFile.close();
}