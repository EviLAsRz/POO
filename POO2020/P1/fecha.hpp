//
// Created by Claudia Soriano Roldán on 04/03/2019.
//

#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>
#include <cstring>

class Fecha {
public:
    explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
    Fecha(const char* cadena);


    static const int AnnoMaximo = 2037;
    static const int AnnoMinimo = 1902;

    class Invalida {  //Clase de excepcion
    public:
        Invalida(const char* razon) : razon_{razon} {}
        const char* por_que() const noexcept { return razon_; }
    private:
        const char* razon_;
    };

    int dia() const noexcept { return dia_; }
    int mes() const noexcept { return mes_; }
    int anno() const noexcept { return anno_; }

    Fecha operator ++(int); //Postincremento
    Fecha operator --(int); //Postdecremento
    Fecha operator +(int n) const;
    Fecha operator -(int n) const;
    Fecha& operator +=(int n);
    Fecha& operator -=(int n);
    Fecha& operator ++(); //Preincremento
    Fecha& operator --(); //Predecremento

    const char* cadena() const noexcept;

private:
    int dia_, mes_, anno_;
    void fechaEsValida();
    void fSistema(int d, int m, int a);
};


bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);

std::ostream& operator << (std::ostream& os, const Fecha& f);
std::istream& operator >> (std::istream& is, Fecha& f);

#endif