//Matteo Piras and Claudia De Carlo

#include "../headers/game.h"


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

            //if AA AA  cancella le Y da attack e salva su log
            if (origin.compare("AA") == 0 && target.compare("AA") == 0) {
                //chiede e legge nuova mossa e salva in move
            }

                //if XX XX  stampa le griglie DI P2
            else if (origin.compare("XX") == 0 && target.compare("XX") == 0) {
                //chiede e legge nuova mossa e salva in move
            } else {
                //chiama l'azione (altrimenti propaga eccezione)
                pl.action(origin, target, opponent);
                //salva roundFlag, origin, target su log
                done = true;
            }
        }
        catch (coords::invalidCoords e) {
            //le coordinate non sono valide
            // chiede di riprovare (done = false)
        }
        catch (player::invalidOrigin e) {
            //l'origine non corrisponde a nessuna nave
        }
        catch (player::notEnoughSpace e) {
            //non c'è spazio per spostare la nave
        }
    }
    std::pair<std::string, std::string> c = std::make_pair(origin, target);
    return c;
}

//TURNI
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
}
