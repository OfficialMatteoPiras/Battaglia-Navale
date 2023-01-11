//Created by Andrea Nalin

//Created by Andrea Nalin

#include "../headers/ship.h"
#include <utility>

//OVERLOAD OPERATORI
std::ostream& operator<< (std::ostream& os, ship& ship){
    return os << "Center:" <<ship.getCenter() << "\t| Bow: " << ship.getBow().getRow() << ship.getBow().getCol() << "\t| Stern: " <<ship.getStern().getRow() << ship.getStern().getCol();
    //return os << ship.getC() << " " << ship.getCenter() << " " << ship.getDimension() << " " << ship.getLife() << " " << ship.isVertical();      //stampa come centro, dimensione, vita, verticale
}

// -------------------- SHIP -------------------- //
coords ship::getBow() const{        //prua
    if(vertical) return center.add(-(dim/2), 0);
    return center.add(0, -(dim/2));
}

coords ship::getStern() const {     //poppa
    if(vertical) return center.add((dim/2), 0);
    return center.add(0, (dim/2));
}


bool ship::contains(coords c) const{
    coords check = center;      //salvo in check le coordinate delle varie unità della nave
    for(int i = -dim/2; i <= dim/2; i++){
        if(vertical)
            check = center.addRow(i);
        else
            check = center.addCol(i);
        if(check == c)
            return true;
    }
    return false;
}

void ship::removeLife(){
    if(isAlive())
        life--;
}
