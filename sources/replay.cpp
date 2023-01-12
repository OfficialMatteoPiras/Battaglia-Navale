//Created by Matteo Piras

#include "../headers/replay.h"

void replay::replay_main(char ch_, const std::string& nome_file_log, const std::string& output_replay) {
    //lettura del file -> fatta in ogni caso, sia trascrittura che replay
    read_file(nome_file_log);
    //funzione che fa partire il replay
    if(ch_ == 'v'){
        startReplay();
    }
    else{       //write file
        game::write_game(output_replay, startPlayer, vector);       //chiamo la funzione di scrittura in game
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
    }
    else{
        getline(inFile, str);
        if(str[0] == '0'){
            std::cout << "Inizia player 1" << std::endl;
            startPlayer = false;
        }
        else{
            std::cout << "Inizia player 2" << std::endl;
            startPlayer = true;
        }
        while (getline(inFile, str)){           //inserimento di log.txt nel vettore
            if(!str.empty() && str[0] != '0') {
                s1 = str.substr(0, str.find(delimiter));
                s2 = str.substr(str.find(delimiter)+1, str.length()-1);
                vector.emplace_back(s1, s2);           //salvataggio nell'array
            }
        }
    }
    inFile.close();
}

void replay::startReplay() {
    //creazione dei giocatori
    replayPlayer p1("Player 1"), p2("Player 2");        //inizializzazione dei giocatori
    std::vector<std::pair<coords, coords>> moves = getSubVector(16, vector.size());     //vettore con solo le mosse da replicare
    const int maxRounds = moves.size() - 1;
    //INIZIALIZZAZIONE DELLA FLOTTA
    //Player 1
    try{
        p1.startReplayFleet(getSubVector(0, 7));
        p1.visual();
        p1.printFleet();
        std::cout << "**** " << player::funnyMessage() << " ****" << std::endl;       //chiamata statica
        std::cout << std::endl;
    }catch(player::invalidOrigin){
        std::cout << "player 1" << std::endl;
    }
    //Player 2
    try{
        p2.startReplayFleet(getSubVector(8, 15));
        p2.visual();
        p2.printFleet();
        std::cout << "**** " << player::funnyMessage() << " ****" << std::endl;       //chiamata statica
    }catch(player::invalidOrigin){
        std::cout << "player 2" << std::endl;
    }

    std::cout << std::endl;

    //partita (replay)
    for (int i = 0; i < maxRounds && p1.isAlive() && p2.isAlive(); ++i) {
        if(!startPlayer) {     //round P1
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p1.getName() << std::endl;
            p1.visual();
            replayPlayer::makeMove(p1, p2, moves[i]);
        }
        else{              //round P2
            std::cout << "** TURNO " << i+1 << ":  TOCCA A " << p2.getName() << std::endl;
            p2.visual();
            replayPlayer::makeMove(p2, p1, moves[i]);
        }
        //todo: aggiungere grafica e tempo del replay
        startPlayer = !startPlayer; //cambio turno
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

