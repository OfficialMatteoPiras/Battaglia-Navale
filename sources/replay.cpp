//Created by Andrea Nalin

#include "../headers/replay.h"

void replay::replay_main(char ch_, const std::string& nome_file_log, const std::string& output_replay) {
    //lettura del file -> fatta in ogni caso, sia trascrittura che replay
    read_file(nome_file_log);
    //funzione che fa partire il replay
    if(ch_ == 'v'){
        startReplay();
    }
    else{
        //write file
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
    if(!inFile){
        throw FileNotValid();
    }
    else{
        getline(inFile, str);
        if(str[0] == '0'){
            std::cout << "Inizia player 1" << std::endl;
        }
        else{
            std::cout << "Inizia player 2" << std::endl;
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
    //replayPlayer p1, p2;
    //inizializzazione della flotta
    //p1.startReplayFleet(getSubVector(1,8));
    //p2.startReplayFleet(getSubVector(8,16));
    //todo: vettore con mosse
    //partita (replay)



    //chiusura partita

}
