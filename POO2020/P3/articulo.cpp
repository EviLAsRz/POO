//
// Created by Claudia Soriano Roldán on 20/04/2019.
//

#include "articulo.hpp"
#include <ostream>

std::ostream& operator <<(std::ostream& output, const Articulo& art)
{
    output << "[" << art.referencia() << "] \""<< art.titulo() << "," << art.f_publi().anno() <<"." << art.precio() << "€" ;

    return output ;
}
