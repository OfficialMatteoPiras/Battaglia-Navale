//Created by Andrea Nalin

//Created by Andrea Nalin

#include "../headers/ship.h"
#include <utility>

//OVERLOAD OPERATORI
std::ostream& operator<< (std::ostream& os, ship& ship){
    return os << &ship.getCenter() << " " << ship.getDimension() << " " << ship.getLife() << " " << ship.isVertical();      //stampa come centro, dimensione, vita, verticale
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


