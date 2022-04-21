#include "articulo.hpp"
#include <iostream>
#include <iomanip>

Articulo::Articulo(const Autores &autor, const Cadena &refer, const Cadena &tit, const Fecha &f, double pr):
autor_(autor), cod_refer_(refer), titulo_ (tit), precio_(pr){

    if(autor_.empty()){
        throw Autores_vacios();
    }
}


std::ostream &operator << (std::ostream &os, const Articulo& art){

    os << "[" << setw(3) << setfill('0') << art.referencia() << "] \"" << art.titulo() << "\", de ";

    auto autor = art.autores().begin();

    os << (*autor)->apellidos();

    for(++autor; autor != art.autores().end(); ++autor){
        os << ", " << (*autor)->apellidos();
    }
    os << ". ";

    int anio = art.f_publi().anno();

    os << anio << ". " << std::fixed << std::setprecision(2)
       << art.precio() << " €" << std::endl;
    os << "\t";

    art.impresion_especifica(os);

    return os;
}
