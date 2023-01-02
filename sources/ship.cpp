//Created by Andrea Nalin

#include "../headers/ship.h"
#include <utility>
// ------------------- SHIP ------------------- //
bool ship::checkPosition(coords target, game::matrix checkMatrix) {
    if(checkMatrix.getElement(target) != ' '){
        //throw invalidPosition();
        return false;
    }
    return true;
}

// ------------------- BATTLESHIP ------------------- //
coords battleship::getBow() {   //getter prua
    if(vertical) return {center.getX(), center.getY() - 2};
    return {center.getX() - 2, center.getY()};
}

coords battleship::getStern() {   //getter poppa
    if(vertical) return {center.getX(), center.getY() + 2};
    return {center.getX() + 2, center.getY()};
}

void battleship::action(coords target, game::matrix *matrixShips, game::matrix *matrixAttack, game::matrix *opponentDefence) {
    char c;
    if(opponentDefence->isEmpty(target)){
        std::cout << "Miss";
        c = '0';
    }
    else{
        opponentDefence->hit(target);
        std::cout << "Hit";
        c = 'X';
    }
    matrixAttack->setElement(c, target.getX(), target.getY());     //matrix attack update
}

// ------------------- SUPPORT ------------------- //
coords support::getBow() {   //getter prua
    if(vertical) return {center.getX(), center.getY() - 1};
    return {center.getX() - 1, center.getY()};
}

coords support::getStern() {   //getter poppa
    if(vertical) return {center.getX(), center.getY() + 1};
    return {center.getX() + 1, center.getY()};
}

void support::action(coords target, game::matrix *matrixShips, game::matrix *matrixAttack, game::matrix *opponentDefence) {

}

// ------------------- SUBMARINE ------------------- //
coords submarine::getBow() {   //getter prua
    return {center.getX(), center.getY()};
}

coords submarine::getStern() {   //getter poppa
    return {center.getX(), center.getY()};
}

void submarine::action(coords target, game::matrix *matrixShips, game::matrix *matrixAttack, game::matrix *opponentDefence) {
    int startX = target.getY() - 2;     //due celle sopra
    int startY = target.getX() - 2;     //due celle indietro
    for (int i = startX; i < startX + 5; ++i) {             //ciclo per le righe -> da inizio a inizio + 5
        for (int j = startY; j < startY + 5; ++j) {         //ciclo per le colonne
            if (!opponentDefence->isEmpty({i, j})) {        //se la cella non è vuota
                matrixAttack->insert({i, j}, 'Y');
            }
        }
    }
}

bool submarine::move(coords target, game::matrix* matrixDefence) {
    if(!checkPosition(target, *matrixDefence)){
        throw invalidPosition();
    }
    matrixDefence->setElement(' ', center.getX(), center.getY());
    matrixDefence->setElement('E', target.getX(), target.getY());
    return true;
}

/*
//class battleship
//SHOOT
void battleship::action(coords target, game::matrix* defense, game::matrix *attack, game::matrix *oppDef) {
    if(oppDef->isEmpty(target)){
        std::cout << "Miss";
    }
    oppDef->hit(target);
    std::cout << "Hit";
}


//MOVE FUNCTION

bool ship::move(coords target, game::matrix defense, char c){
    if(defense.isEmpty(target)){
        if(c=='E'){
            defense.insert(target, 'E');
            defense.insert(pos, ' ');
            pos = target;
            return true;
        }
        else{
            if(vertical && defense.isEmpty(target.addCol(+1)) && defense.isEmpty(target.addCol(-1))) {
                defense.insert(target, 'C');
                defense.insert(target.addCol(+1), 'C');
                defense.insert(target.addCol(-1), 'C');
                defense.insert(pos, ' ');
                defense.insert(pos.addCol(+1), ' ');
                defense.insert(pos.addCol(-1), ' ');
                return true;
            }
            else if(defense.isEmpty(target.addRow(+1)) && defense.isEmpty(target.addRow(-1))) {
                defense.insert(target, 'C');
                defense.insert(target.addRow(+1), ' ');
                defense.insert(target.addRow(-1), ' ');
                defense.insert(pos, ' ');
                defense.insert(pos.addRow(+1), ' ');
                defense.insert(pos.addRow(-1), ' ');
                return true;
            }
        }
    }
    return false;
};

//classe submarine
void submarine::action(coords target, game::matrix *defense, game::matrix *attack, game::matrix *oppDef) {
    int startX = target.getY() - 2;     //due celle sopra
    int startY = target.getX() - 2;     //due celle indietro
    for (int i = startX; i < startX + 5; ++i) {             //ciclo per le righe -> da inizio a inizio + 5
        for (int j = startY; j < startY + 5; ++j) {         //ciclo per le colonne
            if (!oppDef->isEmpty({i, j})) {        //se la cella non è vuota
                attack->insert({i, j}, 'Y');
            }
        }
    }
}

//class support
void support::action(coords target, game::matrix* defense, game::matrix *attack, game::matrix* oppDef) {
    if(move(target, *defense, 'S')){
        for(int i = -1; i <= 1; i++){
            for(int j = -1; i<= 1; i++){
                coords c = target.add(i, j);
                defense->restore(c);
            }
        }
    }
    else
        //throw eccezione spazio occupato

}

//MOVEMENT OF THE SUPPORT SHIP
/*bool support::move(coords target, game::matrix defense){
    if(defense.isEmpty(target)){
        switch
    }
    return false;
}

//class submarine
//MOVEMENT OF THE SUBMARINE
bool submarine::move(coords target, game::matrix defense){
    if(defense.isEmpty(target)){
        defense.insert(target, 'E');
        defense.insert(target, ' ');
        return true;
    }
    return false;
}*/