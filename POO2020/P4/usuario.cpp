//
// Created by Claudia Soriano Roldán on 24/04/2019.
//

#include <random>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include "usuario.hpp"

/**************** CLASE CLAVE *****************/

Clave::Clave(const char* c)
{
    const char* crypto = "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA9876543210/.";
    char* cifrar = new char [2];

    if(strlen(c) < 5)
    {
        throw Incorrecta(Razon::CORTA);
    }

    cifrar[0] = crypto[rand() % 64];
    cifrar[1] = crypto[rand() % 64];

    if(crypt(c,cifrar) == NULL)
    {
        throw Incorrecta(Razon::ERROR_CRYPT);
    }

    contrasena_ = crypt(c,cifrar);
}

bool Clave::verifica(const char* c) const
{
    return std::strcmp(crypt(c, contrasena_.c_str()), contrasena_.c_str()) == 0;
}


/*********************** CLASE USUARIO *************************/

Usuario::Usuarios Usuario::usuario_;

Usuario::Usuario(const Cadena &identificador, const Cadena &nom, const Cadena &apell, const Cadena &dir, const Clave &p):
identificador_(identificador), nombre_(nom), apellidos_(apell), direccion_(dir), password_(p)
{
    if(!usuario_.insert(identificador).second)
    {
        throw Id_duplicado(identificador_);
    }
}

void Usuario::compra(Articulo &a, unsigned cant)
{
    if(cant != 0)
    {
        articulos_[&a] = cant;
    }else{
        articulos_.erase(&a);
    }
}

void Usuario::es_titular_de(Tarjeta &t)
{
    if(this == t.titular())
    {
        tarjetas_.insert(std::make_pair(t.numero(), &t));
    }
}

void Usuario::no_es_titular_de(Tarjeta &t)
{
    t.anula_titular();
    tarjetas_.erase(t.numero());
}

std::ostream& mostrar_carro(std::ostream& output, const Usuario& u)
{
    output << "Carrito de compra de " << u.id() << " [Artículos: "<< u.n_articulos() << "]" << "\n"
       << "Cant.Artículo"<< std::endl
       << std::setw(95) << std::setfill('=') << '\n' << std::setfill(' ');

    int nart = u.n_articulos() ;

    while( nart > 0 )
    {
        for(auto i = u.compra().begin(); i != u.compra().end(); i++)
        {
            output << std::setw(4) << i->second << "    "
                   << " [" << (*i->first).referencia() << "] " << "\""
                   << (*i->first).titulo() << "\", "
                   << (*i->first).f_publi().anno()
                   << ". " << std::fixed << std::setprecision(2) << (*i->first).precio() << " €" << std::endl;

            --nart;
        }
    }

    return output;
}

std::ostream& operator <<(std::ostream& output, const Usuario& u)
{
    output << u.identificador_ << "[" << u.password_.clave().c_str() << "]" << u.nombre_ << u.apellidos_ << "\n"
       << u.direccion_ << std::endl;
    output <<"Tarjetas:" ;
    for(auto i = u.tarjetas().begin(); i != u.tarjetas().end(); i++)
    {
        output << *i->second << std::endl ;
    }

    return output ;
}

Usuario::~Usuario()
{
    for(auto i = tarjetas_.begin(); i != tarjetas_.end(); i++)
    {
        i->second->anula_titular();
    }

    usuario_.erase(identificador_);
}
