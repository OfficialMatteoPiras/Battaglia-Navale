//Matteo Piras and Claudia De Carlo

#include "../headers/game.h"

void game::grid(matrix ships, matrix attack) {
    std::string letters = "ABCDEFGHILMN";
    std::string token;

    for (int i = 0; i < 13; i++) {
        for (int k = 0; k < 2; ++k) {
            for (int j = 0; j < 13; j++) {
                token = "";
                if(i == 0){                     // prima riga stampa i numeri
                    if(j == 0) token = "  |";       //se è la prima riga e la prima ripetizione deve stampare uno spazio
                    else{
                        if(j < 10) token = " " + std::to_string(j ) + " |";  //se il numero occupa un solo carattere
                        else token = std::to_string(j ) + " |";         //se il numero occupa 2 caratteri
                    }
                }
                else{
                    if (j == 0) std::cout << letters[i - 1] << " |";        //stampa della lettera
                    else{
                        token = " ";
                        if(k == 0) {    //! griglia 1
                            token += ships.getElement(i - 1, j - 1);
                        }
                        else { //! griglia 2
                            token += attack.getElement(i - 1, j - 1);
                        }
                        token += " |";
                    }
                }
                std::cout << token;
            }
            std::cout << "\t";
        }
        std::cout << std::endl;
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

//FUNZIONI RANDOM
coords game::getRandomCoord(){
    std::string letters = "ABCDEFGHILMN";
    coords c = {letters[getRandomInt(letters.size() - 1)] + std::to_string(getRandomInt(letters.size() - 1))};
    //std::cout << "estrazione-> " << c << std::endl;        //todo: remove
    return c;
}

coords game::getRandomCoord(coords bow, bool vertical, int distance){ //prende in input la PRUA!
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

int game::getRandomInt(int range, int start){
    srand(rand());
    int random = start + (rand() % range);
    return random;
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
