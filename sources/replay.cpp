// Matteo Piras

#include "../headers/replay.h"

void replay::replay_main(char ch_, const std::string& nome_file_log, const std::string& output_replay) {
    //lettura del file -> fatta in ogni caso, sia trascrittura che replay
    try{
        read_file(nome_file_log);
        //funzione che fa partire il replay
        if(ch_ == 'v'){
            startReplay();
        }
        else{       //write file
            game::write_game(output_replay, startPlayer, name1, name2, vector);       //chiamo la funzione di scrittura in game
        }
    }catch(FileNotValid &){
        std::cout << "*** File non trovato ***" << std::endl;
    }
}

std::vector<std::pair<coords, coords>> replay::getSubVector(int start, int end) {
    std::vector<std::pair<coords, coords>> subVector;
    for (int i = start; i <= end; ++i) {
        subVector.emplace_back(vector[i].first, vector[i].second);
    }
    return subVector;
}

void replay::read_file(const std::string& file_in_name) {
    std::string path = "../file/" + file_in_name, str, s1, s2, delimiter = " ";
    std::ifstream inFile(path);

    if(path.find(".txt") == std::string::npos) path += ".txt";      //se non trova l'estensione la aggiunge

    if(!inFile){
        throw FileNotValid();
        //std::cout << "*** File non trovato ***" << std::endl;
    }
    else{
        getline(inFile, str);
        if(str[0] == '1')
            startPlayer = true;
        else
            startPlayer = false;

        getline(inFile, name1);
        getline(inFile, name2);

        if (startPlayer)
            std::cout << "Inizia " << name1 << std::endl;
        else
            std::cout << "Inizia " << name2 << std::endl;

        while (getline(inFile, str)){           //inserimento di logCC.txt nel vettore
            if(!str.empty() && str[0] != '0') {
                s1 = str.substr(0, str.find(delimiter));
                s2 = str.substr(str.find(delimiter)+1, str.length()-1);
                vector.emplace_back(s1, s2);           //salvataggio nell'array
            }
        }
        inFile.close();
    }
}

void replay::startReplay() {
    //creazione dei giocatori
    replayPlayer p1(name1), p2(name2);        //inizializzazione dei giocatori
    std::vector<std::pair<coords, coords>> moves = getSubVector(16, vector.size());     //vettore con solo le mosse da replicare
    const int maxRounds = moves.size() - 1;
    //INIZIALIZZAZIONE DELLA FLOTTA
    //Player 1
    try{
        p1.startReplayFleet(getSubVector(0, 7));
        p1.visual();
        p1.printFleet();
        std::cout << std::endl;
        std::cout << "**** " << player::funnyMessage() << " ****" << std::endl;       //chiamata statica
        std::cout << std::endl;
    }catch(player::invalidOrigin& e){
        std::cout << "Errore di caricamento del 1 giocatore" << std::endl;
    }
    //Player 2
    try{
        p2.startReplayFleet(getSubVector(8, 15));
        p2.visual();
        p2.printFleet();
        std::cout << std::endl;
        std::cout << "**** " << player::funnyMessage() << " ****" << std::endl;       //chiamata statica
    }catch(player::invalidOrigin& e){
        std::cout << "Errore di caricamento del 2 giocatore" << std::endl;
    }

    std::cout << std::endl;

    //partita (replay)
    bool roundP1 = startPlayer;
    for (int i = 0; i < maxRounds && p1.isAlive() && p2.isAlive(); ++i) {

        std::cout << std::endl;
        if(roundP1) {     //round P1
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p1.getName() << std::endl;
            p1.visual();
            replayPlayer::makeMove(p1, p2, moves[i]);
        }
        else{              //round P2
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p2.getName() << std::endl;
            p2.visual();
            replayPlayer::makeMove(p2, p1, moves[i]);
        }

        roundP1 = !roundP1; //cambio turno
        std::cout << std::endl;
        sleep(2);
    }

    //FINE PARTITA
    //if p1 è morto
    if(!p1.isAlive()){      //vincitore P2
        std::cout << "IL VINCITORE E': " + p2.getName() << std::endl;
    }
        //if p2 è morto
    else if(!p2.isAlive()){     //vincitore P1
        std::cout << "IL VINCITORE E': " + p1.getName() << std::endl;
    }
    //if mosse finite: confronto "punteggi" (unità vive)
    else{
        std::cout << "LA PARTITA E' FINITA IN PAREGGIO!" << std::endl;
    }

    //RIASSUNTO FINALE
    std::cout << std::endl;
    std::cout << "*** TOTALE DANNI INFLITTI ***" << std::endl;
    std::cout << ">> " + p1.getName() + ": " << p1.getPoints() << std::endl;
    std::cout << ">> " + p2.getName() + ": " << p2.getPoints() << std::endl;

}