#include "articulo.hpp"
#include <iomanip>
#include <iostream>

Articulo::Articulo(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f,  double precio) : autor_(autor), referencia_(referencia),titulo_(titulo), fecha_pub_(f),precio_(precio)
{
    if(autor_.empty())
        throw Autores_vacios();
}

ostream& operator<<(ostream& os, const Articulo& a) noexcept
{
	os << "[" << setw(3) << setfill('0') << a.referencia() << "] \"" << a.titulo()
       << "\", de ";

    auto autor = a.autores().begin();

    os << (*autor)->apellidos();

    for(++autor; autor != a.autores().end(); ++autor)
        os << ", " << (*autor)->apellidos();

    os << ". ";

    int anio = a.f_publi().anno();

    os << anio << ". " << fixed << setprecision(2)
       << a.precio() << " €" << endl;
       os << "\t";
	a.impresion_especifica(os);

    return os;
}
