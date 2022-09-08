#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iostream>
#include <iomanip>

int Pedido::num_pedido_ = 0;        //inicializacion del atributo estático

Pedido::Pedido(Usuario_Pedido &upe, Pedido_Articulo &part, Usuario &u, const Tarjeta &t, const Fecha &f):num_(num_pedido_ + 1), tarjeta_(&t), total_(0){

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
        if((i.first)->stock() < (i.second)){
            const_cast<Usuario::Articulos&>(u.compra()).clear();
            throw SinStock(i.first);
        }
    }

    carro = u.compra();

    for(auto it: carro){

        unsigned int cant = (it.second);
        Articulo *a = (it.first);
        double price = a->precio();
        a->stock() -=cant;

        part.pedir(*this, *a, price, cant);
        total_ += price * cant;
        u.compra(*a, 0);
    }

    upe.asocia(u, *this);

    ++num_pedido_;
}

std::ostream &operator <<(std::ostream &os, const Pedido &ped){

    os << "Núm. pedido: " << ped.numero() << std::endl;
    os << "Fecha:       " << ped.fecha() << std::endl;
    os << "Pagado con:  " << ped.tarjeta()->tipo() << " n.º: " << ped.tarjeta()->numero() <<std::endl;
    os << "Importe:     " << std::fixed << std::setprecision(2) << ped.total() << " €" <<std::endl;

    return os;
}