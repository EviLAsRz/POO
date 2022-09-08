//
// Created by Claudia Soriano Roldán on 20/04/2019.
//


#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo
{
public:

    Articulo(const Cadena& ref, const Cadena& tit, const Fecha& f, const double prec, const unsigned s):
    titulo_(tit), referencia_(ref), stock_(s), fecha_pub_(f), precio_(prec) {}

    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double& precio();
    unsigned stock() const;
    unsigned& stock();

private:
    Cadena titulo_;
    Cadena referencia_;
    Fecha fecha_pub_;
    double precio_;
    unsigned stock_;

};

inline Cadena Articulo::titulo() const {
    return titulo_;
}

inline Cadena Articulo::referencia() const {
    return referencia_;
}

inline Fecha Articulo::f_publi() const {
    return fecha_pub_;
}

inline double& Articulo::precio() {
    return precio_;
}

inline double Articulo::precio() const {
    return precio_;
}

inline unsigned& Articulo::stock() {
    return stock_;
}

inline unsigned Articulo::stock() const {
    return stock_;
}

std::ostream& operator <<(std::ostream& output, const Articulo& art);

#endif //SORIANO_ROLDAN_CLAUDIA_ARTICULO_H
