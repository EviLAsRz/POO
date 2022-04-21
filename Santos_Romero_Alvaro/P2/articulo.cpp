#include "articulo.hpp"
#include <iostream>
#include <iomanip>

std::ostream &operator << (std::ostream &os, const Articulo& art){

    os << "[" << art.referencia() << "] \"" << art.titulo() << "," << art.f_publi().anno() << "." << art.precio() << "€"; //formato especificado en la practica
    return os;
}
