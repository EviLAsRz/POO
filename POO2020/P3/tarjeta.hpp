//
// Created by Claudia Soriano Roldán on 26/04/2019.
//

#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include <ostream>
#include <functional>

class Usuario;

struct EsDigito: public std::unary_function<char,bool>
{
    bool operator() (char x) const {return isdigit(x); };
};

/******+********* CLASE NUMERO **********************/

class Numero{
public:
    enum Razon {LONGITUD, NO_VALIDO, DIGITOS};

    Numero(const Cadena& n);

    friend bool operator <(const Numero& x, const Numero& y);

    operator const char*() const;

    class Incorrecto{
    public:
        Incorrecto(Razon r): fallo_(r) {}
        const Razon& razon() const {return fallo_;};
    private:
        Razon fallo_;
    };

private:
    Cadena num_;

    Cadena elimina_espacio(const Cadena& cad);
    Cadena longitud_cadena(const Cadena& cad);
};


/***************** CLASE TARJETA **************************/

class Tarjeta{
public:
    enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
    Tarjeta(const Numero& n, Usuario& user, const Fecha& f);
    Tarjeta(const Tarjeta& t) = delete;

    void anula_titular();
    Tarjeta& operator =(const Tarjeta& t) = delete;

    Tipo tipo() const {return tipo_;};
    Numero numero() const {return numero_;};
    const Usuario* titular() const {return usr_;};
    Fecha caducidad() const {return caducidad_;};
    bool activa() const {return actividad_;};
    bool activa(bool valor = true);

    ~Tarjeta();

    class Caducada{
    public:
        Caducada(const Fecha& f):fc_(f){}
        Fecha cuando() const {return fc_;}
    private:
        Fecha fc_;
    };

    class Desactivada{
    
    };

    class Num_duplicado
    {
    public:
        Num_duplicado(const Numero& n): n_(n){}
        const Numero que() const {return n_;};
    private:
        Numero n_;
    };

private:
    Tipo tipo_;
    Numero numero_;
    const Usuario* usr_;
    Fecha caducidad_;
    bool actividad_;
};

std::ostream& operator << (std::ostream& output, const Tarjeta::Tipo& t) ;
std::ostream& operator << (std::ostream& output, const Tarjeta& t) ;
bool operator <(const Tarjeta& a, const Tarjeta& b);


#endif //SORIANO_ROLDAN_CLAUDIA_TARJETA_H
