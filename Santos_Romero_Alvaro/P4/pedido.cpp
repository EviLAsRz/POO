#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iostream>
#include <iomanip>

int Pedido::num_pedido_ = 0;        //inicializacion del atributo estático

Pedido::Pedido(Usuario_Pedido &upe, Pedido_Articulo &part, Usuario &u, const Tarjeta &t, const Fecha &f):tarjeta_(&t), fecha_(f), num_(num_pedido_ + 1), total_(0){

    if(t.caducidad() < f){
        throw Tarjeta::Caducada(t.caducidad()); //si la tarjeta está caducada.
    }

    if(u.n_articulos() == 0){   //si no tiene articulos
        throw Vacio(u);
    }

    if(t.titular() != &u){      //si el titular es distinto al usuario introducido
        throw Impostor(u);
    }

    if(t.activa() != true){     //si la tarjeta está desactivada
        throw Tarjeta::Desactivada();
    }

    auto carro = u.compra();

    for(auto i: carro){
        if(ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(i.first)){
            if(aa->stock() < i.second){
            const_cast<Usuario::Articulos&>(u.compra()).clear();
            throw SinStock(i.first);
            }
        }else if(LibroDigital *ld = dynamic_cast<LibroDigital*>(i.first)){
            if(ld->f_expir() < Fecha()){
                u.compra(*i.first,0);
                if(u.n_articulos() == 0){
                    throw Vacio(u);
                }
            }
        }
    }
    upe.asocia(u, *this);
    carro = u.compra();

    for(auto i: carro){

        part.pedir(*this, *i.first, (i.first)->precio(), i.second);
        u.compra(*i.first,0);
        total_ += (i.first)->precio() * i.second;

        if(ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(i.first))
        aa->stock() -= i.second;
    }

    ++num_pedido_;
}

std::ostream &operator <<(std::ostream &os, const Pedido &ped){

    os << "Núm. pedido: " << ped.numero() << std::endl;
    os << "Fecha:       " << ped.fecha() << std::endl;
    os << "Pagado con:  " << ped.tarjeta()->tipo() << " n.º: " << ped.tarjeta()->numero() <<std::endl;
    os << "Importe:     " << std::fixed << std::setprecision(2) << ped.total() << " €" <<std::endl;

    return os;
}