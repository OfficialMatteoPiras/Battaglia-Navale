//Matteo Piras

#ifndef BATTAGLIA_NAVALE_REPLAY_H
#define BATTAGLIA_NAVALE_REPLAY_H

#include <iostream>
#include <vector>
#include <unistd.h>
#include "../headers/coords.h"
#include "../headers/player.h"
#include "../headers/replayPlayer.h"
#include "../headers/game.h"

class replay{
    private:
        std::vector<std::pair<coords, coords>> vector;      //vettore per il salvataggio
        bool startPlayer = false;
        std::string name1;
        std::string name2;

        //MEMBRI PRIVATI
        std::vector<std::pair<coords, coords>>getSubVector(int start, int end);     //funzione per ottenere un sottovettore
        void read_file(const std::string& file_in_name);      //lettura del file txt
        void startReplay();

        //ECCEZIONI
        class FileNotValid : public std::exception{};

    public:
        replay() = default;
        void replay_main(char ch_, const std::string& nome_file_log, const std::string& output_replay = "");      //funzione che fa partire il replay (ancora di partenza)

};

#endif //BATTAGLIA_NAVALE_REPLAY_H