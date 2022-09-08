//
// Created by Claudia Soriano Roldán on 08/05/2019.
//

#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iostream>
#include <iomanip>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

int Pedido::num_pedido_ = 0;

Pedido::Pedido(Usuario_Pedido &usuped, Pedido_Articulo &pedart, Usuario &u, const Tarjeta &t, const Fecha &f):
tarjeta_(&t), fecha_(f), num_(num_pedido_ + 1), total_(0)
{
    if(t.caducidad() < f)
    {
        throw Tarjeta::Caducada(t.caducidad());
    }

    if(u.n_articulos() == 0)
    {
        throw Vacio(u);
    }

    if(t.titular() != &u)
    {
        throw Impostor(u);
    }

    if(t.activa() != true )
    {
    	throw Tarjeta::Desactivada();
    }

	 auto carro = u.compra();

    for(auto i: carro)
    {
        if((i.first)->stock() < (i.second))
        {
            const_cast<Usuario::Articulos&>(u.compra()).clear();
            throw SinStock(i.first);
        }
    }

    /*Usuario::Articulos carrito = u.compra();*/
	 carro = u.compra();

    for(auto it : carro)
    {
        unsigned int cant = (it.second);
        Articulo* a = (it.first);
        double price = a->precio();
        a->stock() -= cant;

        pedart.pedir(*this, *a, price, cant);
        total_ += price * cant;
        u.compra(*a, 0);
    }

    usuped.asocia(u, *this);

    ++num_pedido_;

}

std::ostream& operator <<(std::ostream& output, const Pedido& p)
{
    output << "Núm. pedido:	" << p.numero() << std::endl ;
    output << "Fecha:		" << p.fecha() << std::endl;
    output << "Pagado con:	" << p.tarjeta()->tipo() << " n.º: "<< p.tarjeta()->numero() << std::endl ;
    output << "Importe:	" << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl ;


    return output ;
}
