#ifndef BATTAGLIA_NAVALE_REPLAY_H
#define BATTAGLIA_NAVALE_REPLAY_H

#include <iostream>
#include <vector>
#include "headers/coords.h"
#include "headers/player.h"
#include <unistd.h>
using namespace std;

class replay{
    private:
    static vector<pair<coords, coords>>getSubVector(vector<pair<coords, coords>> inVector, int start, int end);

    public:
    //replay();
    static int replay_main();
        class FileNotValid : public exception{
            public:
            char * what(){
                return "File Not Valid Exception\n";
        }
    };

    //void writeFile(string file_in_name, string file_out_name, vector<pair<coords, coords>> moves, player p, int pl);

    vector<pair<coords, coords>> read_file(string file_in_name, vector<pair<coords, coords>> data);

    player* getPlayer(vector<pair<coords, coords>> player_ships);

    static void action(vector<pair<coords, coords>> moves);

    void startReplay(vector<pair<coords, coords>> moves, player p1, player p2);

    void print(player p);

};

#endif //BATTAGLIA_NAVALE_REPLAY_H