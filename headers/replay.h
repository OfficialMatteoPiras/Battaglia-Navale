#ifndef BATTAGLIA_NAVALE_REPLAY_H
#define BATTAGLIA_NAVALE_REPLAY_H

#include <iostream>
#include <vector>
#include <unistd.h>
#include "../headers/coords.h"
#include "../headers/player.h"
#include "../headers/replayPlayer.h"

class replay{
    private:
        std::vector<std::pair<coords, coords>> vector;      //vettore per il salvataggio
        bool startPlayer;

        //MEMBRI PRIVATI
        std::vector<std::pair<coords, coords>>getSubVector(int start, int end);     //funzione per ottenere un sottovettore
        void read_file(const std::string& file_in_name);      //lettura del file txt
        void print(player p);       //!funzione per la stampa (usare visual di player?)
        void startReplay();

        //ECCEZIONI
        class FileNotValid : public std::exception{};

    public:
        replay() = default;
        void replay_main(char ch_, const std::string& nome_file_log, const std::string& output_replay = "");      //funzione che fa partire il replay (ancora di partenza)
        void write_file(const std::string& file_log, const std::string& out_file = "");      //scrittura del file txt

        //void writeFile(string file_in_name, string file_out_name, vector<pair<coords, coords>> moves, player p, int pl);

        //player* getPlayer(vector<pair<coords, coords>> player_ships);

        //static void action(vector<pair<coords, coords>> moves);



};

#endif //BATTAGLIA_NAVALE_REPLAY_H