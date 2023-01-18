// Matteo Piras

#include "../headers/ship.h"

//OVERLOAD OPERATORI
std::ostream& operator<< (std::ostream& os, ship& ship){
    return os << "Centro:" <<ship.getCenter() << "\t| Prua: " << ship.getBow().getRow() << ship.getBow().getCol() << "\t| Poppa: " <<ship.getStern().getRow() << ship.getStern().getCol();
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
    coords check;      //salvo in check le coordinate delle varie unità della nave
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
