//
// Created by Claudia Soriano Roldán on 26/04/2019.
//

#include "tarjeta.hpp"
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iostream>

bool luhn(const Cadena& num);

/********* CLASE NUMERO *****************/

Numero::Numero(const Cadena& n): num_(longitud_cadena(n))
{

    if( std::count_if(num_.begin(), num_.end(), static_cast<int(*)(int)>(std::isdigit)) != num_.length() )
    {
        throw Incorrecto(Razon::DIGITOS) ;
    }

    if(!luhn(num_))
    {
        throw Incorrecto(Razon::NO_VALIDO);
    }
}

Cadena Numero::elimina_espacio(const Cadena &cad)
{
    Cadena aux (cad) ;

    std::remove_if(aux.begin(),aux.end()+1,[](char c){return isspace(c);});

    return Cadena(aux.c_str()) ;

}

Cadena Numero::longitud_cadena(const Cadena &cad)
{


    Cadena aux = elimina_espacio(cad) ;

    if(aux.length() > 19 || aux.length() == 0 || aux.length() < 13 )
    {
        throw Incorrecto(Razon::LONGITUD) ;
    }

    return aux ;
}

Numero::operator const char*() const
{
    return num_.c_str();
}

bool operator <(const Numero& x, const Numero& y)
{
    return strcmp(x,y) < 0;
}


/******************** CLASE TARJETA *********************/

Tarjeta::Tarjeta(const Numero &n, Usuario& user, const Fecha &f): numero_(n), usr_(&user), caducidad_(f)
{
    if (caducidad_ < Fecha())
    {
        throw Caducada(caducidad_);
    }

    const char* aux = n;

    tipo_ = Tipo::Otro;

    if((aux[0] == '3' && aux[1] == '4') || (aux[0] == '3' && aux[1] == '7'))
    {
        tipo_ = Tipo::AmericanExpress;
    }

    if((aux[0] == '3' && aux[1] != '4') || (aux[0] == '3' && aux[1] != '7'))
    {
        tipo_ = Tipo::JCB;
    }

    if((aux[0] == '4'))
    {
        tipo_ = Tipo::VISA;
    }

    if((aux[0] == '5'))
    {
        tipo_ = Tipo::Mastercard;
    }

    if((aux[0] == '6'))
    {
        tipo_ = Tipo::Maestro;
    }

    
    actividad_ = true;

    user.es_titular_de(*this);
}

bool Tarjeta::activa(bool valor)
{
	actividad_ = valor;
	return actividad_;
}

void Tarjeta::anula_titular()
{
    usr_= nullptr;
}

Tarjeta::~Tarjeta()
{
    if(Usuario* usu = const_cast<Usuario*>(usr_)){
        usu->no_es_titular_de(*this);
    }
}

bool operator <(const Tarjeta& t1, const Tarjeta& t2)
{
    return t1.numero() < t2.numero();
}

std::ostream& operator << (std::ostream& output ,const Tarjeta::Tipo& t)
{

    switch(t)
    {
        case 0: output << "Otro" ; break;
        case 1: output << "VISA" ; break ;
        case 2: output << "Mastercard"; break ;
        case 3: output << "Maestro"; break ;
        case 4: output << "JCB" ; break ;
        case 5: output << "AmericanExpress" ; break ;

        default: output << "Otra"; break ;
    }

    return output ;

}

std::ostream& operator << (std::ostream& output, const Tarjeta& t)
{
	Cadena aux1 = t.titular()->nombre();
	Cadena aux2 = t.titular()->apellidos();


	for(size_t i=0; i< aux1.length(); i++)
	{
		aux1[i] = toupper(aux1[i]);
	}

	for(size_t j=0; j< aux2.length(); j++)
	{
		aux2[j] = toupper(aux2[j]);
	}

	



    output << t.tipo() << "\n"
       << t.numero() << "\n"
       << aux1 << " " << aux2 << "\n"
       << "Caduca: "
       << std::setfill('0') << std::setw(2) << t.caducidad().mes()
       << "/"
       << std::setw(2) << (t.caducidad().anno() % 100 ) << "\n" << std::endl;

    return output ;

}
