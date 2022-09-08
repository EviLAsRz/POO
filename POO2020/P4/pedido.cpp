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

    if(!t.activa())
    {
    	throw Tarjeta::Desactivada();
    }

    auto carro = u.compra();
    for(auto i : carro)
    {

        if(ArticuloAlmacenable* aa = dynamic_cast<ArticuloAlmacenable*>(i.first))
        {
            if(aa->stock() < i.second)
            {
                const_cast<Usuario::Articulos&>(u.compra()).clear();
                throw Pedido::SinStock(i.first);
            }
        } else if(LibroDigital* ld = dynamic_cast<LibroDigital*>(i.first))
        {
            if(ld->f_expir() < Fecha()){
                u.compra(*i.first, 0);
                if(u.n_articulos() == 0)
                {
                    throw Vacio(u);
                }
            }

        }
    }

    usuped.asocia(u, *this);

    carro = u.compra();
    for(auto i : carro)
        {
            pedart.pedir(*this, *i.first, (i.first)->precio(), i.second);
            u.compra(*i.first, 0);
            total_ +=  (i.first)->precio() * i.second;

            if(ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(i.first))
                aa->stock() -= i.second;
        }

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
