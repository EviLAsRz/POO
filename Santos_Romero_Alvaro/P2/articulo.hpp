#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo{

    public:
    Articulo(const Cadena refer, const Cadena tit, const Fecha f, double pr, unsigned stock): cod_refer_(refer), titulo_(tit), f_public_(f),precio_(pr), stock_(stock){
    };

    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double &precio();
    unsigned stock() const;
    unsigned &stock();


    private:

    Cadena cod_refer_;
    Cadena titulo_;
    Fecha f_public_;
    double precio_;
    unsigned stock_;
};

inline Cadena Articulo::referencia() const {
    return cod_refer_;
}

inline Cadena Articulo::titulo() const {
    return titulo_;
}

inline Fecha Articulo::f_publi() const {
    return f_public_;
}

inline double &Articulo::precio() {
    return precio_;
}

inline double Articulo::precio() const {
    return precio_;
}

inline unsigned &Articulo::stock() {
    return stock_;
}

inline unsigned Articulo::stock() const {
    return stock_;
}

std::ostream &operator << (std::ostream &os, const Articulo &art);

#endif  //ARTICULO_HPP_