//
// Created by Claudia Soriano Roldán on 04/03/2019.
//

#include "fecha.hpp"
#include <stdexcept>
#include <ios>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstring>



Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno}
{
   fSistema(dia, mes, anno);
   fechaEsValida();

}

Fecha::Fecha(const char* cadena)
{
    int dia, mes, anno;
     
    if(sscanf(cadena, "%d/%d/%d", &dia, &mes, &anno) != 3)
        throw Invalida("fecha incorrecta");
    else{
        
        dia_ = dia;
        mes_ = mes;
        anno_ = anno;

        fSistema(dia, mes, anno);
        fechaEsValida();
    }
}

void Fecha::fSistema(int d, int m, int a)
{
    std::time_t tc = std::time(nullptr);
    std::tm* td = std::localtime(&tc);

    if(a == 0)
    {
        anno_ = td->tm_year + 1900;
    }

    if(m == 0)
    {
        mes_ = td->tm_mon + 1;
    }

    if(d == 0)
    {
        dia_ = td->tm_mday;
    }
}

void Fecha::fechaEsValida()
{
    static const int dias [] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int esBisiesto = static_cast<int>(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0));

    if(anno_ > Fecha::AnnoMaximo || anno_ < Fecha::AnnoMinimo)
    {
        throw Invalida("Anno invalido");
    }

    if(mes_ > 12 || mes_ < 1)
    {
        throw Invalida("Mes invalido");
    }

    if(mes_ == 2){
        if(dia_ > dias[mes_] + esBisiesto || dia_ < 1)
        {
            throw Invalida("Dia invalido");
        }
    }
    else{
        if(dia_ > dias[mes_] || dia_ < 1)
        {
            throw Invalida("Dia invalido");
        }
    }

}


const char* Fecha::cadena() const noexcept
{
    const char* dias[] = {"domingo","lunes","martes","miércoles","jueves","viernes","sábado"};

    const char* meses[] = {"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};

    static char fecha[40];

    tm f = {0};

    f.tm_mday = dia();
    f.tm_mon = mes() - 1;
    f.tm_year = anno() - 1900;

    mktime(&f);
    sprintf(fecha,"%s %d de %s de %d", dias[f.tm_wday], f.tm_mday, meses[f.tm_mon], f.tm_year + 1900);

    return fecha;

}


//OPERADORES DE COMPARACION

bool operator ==(const Fecha& f1, const Fecha& f2)
{
    return (f1.anno() == f2.anno()) && (f1.mes() == f2.mes()) && (f1.dia() == f2.dia());
    
}

bool operator >(const Fecha& f1, const Fecha& f2)
{
    if(f1.anno() > f2.anno())
    {return true;}
    else if(f1.anno() == f2.anno() && f1.mes() > f2.mes()) {return true;}
    else if(f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() > f2.dia()) {return true;}
    else return false;

}

bool operator <(const Fecha& f1, const Fecha& f2)
{
    return (f2 > f1);
}

bool operator >=(const Fecha& f1, const Fecha& f2)
{
    return (f1 > f2 || f1 == f2);
}

bool operator <=(const Fecha& f1, const Fecha& f2)
{
    return (f1 < f2 || f1 == f2);
}

bool operator !=(const Fecha& f1, const Fecha& f2)
{
    return !(f1 == f2);
}



//OPERADORES ARITMETICOS

Fecha& Fecha::operator +=(int n)
{
    if(n!=0){
        tm faux = {};
        faux.tm_mday = dia_ + n;
        faux.tm_mon = mes_ - 1;
        faux.tm_year = anno_ - 1900;

        mktime(&faux);

        anno_ = faux.tm_year + 1900;
        mes_ = faux.tm_mon + 1;
        dia_ = faux.tm_mday;
        fechaEsValida();
    }

    return *this;
}

Fecha& Fecha::operator -=(int n)
{
    return *this += -n;
}

Fecha Fecha::operator +(int n) const
{
    Fecha f = *this;
    f += n;
    return f;
}

Fecha Fecha::operator -(int n) const
{
    Fecha f = *this;
    f += -n;
    return f;
}

Fecha& Fecha::operator --()
{
    return *this += -1;
}

Fecha& Fecha::operator ++()
{
    return *this += 1;
}

Fecha Fecha::operator --(int)
{
    Fecha f = *this;
    *this += -1;
    return f;
}

Fecha Fecha::operator ++(int)
{
    Fecha f = *this;
    *this += 1;
    return f;
}


//OPERADORES DE ENTRADA Y SALIDA

std::istream& operator >> (std::istream& is, Fecha& f)
{
    char* cadena = new char[11];
    is.getline(cadena,11);

    try
    {
        f = Fecha(cadena);
    } catch(Fecha::Invalida e)
    {
        is.setstate(std::ios_base::failbit);
        throw e;
    }

    return is;

}

std::ostream& operator << (std::ostream& output, const Fecha& f)
{
    output << f.cadena();
    return output;
}
