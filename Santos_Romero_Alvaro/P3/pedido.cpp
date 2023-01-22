#include "pedido.hpp"

unsigned Pedido::num_pedido_ = 0;        //inicializacion del atributo estático

Pedido::Pedido(Usuario_Pedido &upe, Pedido_Articulo &part, Usuario &u, const Tarjeta &t, const Fecha &f)
:num_(num_pedido_ + 1), tarjeta_(&t), fecha_(f), total_(0.00) {

    if(u.compra().empty() == true){   //si no tiene articulos
        throw Vacio(&u);
    }

    if(t.titular() != &u){      //si el titular es distinto al usuario introducido
        throw Impostor(&u);
    }

    if(t.activa() != true){     //si la tarjeta está desactivada
        throw Tarjeta::Desactivada();
    }

    if(t.caducidad() < f){
        throw Tarjeta::Caducada(t.caducidad()); //si la tarjeta está caducada.
    }

    auto carro = u.compra();

    for(Usuario::Articulos::iterator i = carro.begin(); i != carro.end(); ++i){
        
        if(ArticuloAlmacenable* art_almacenable = dynamic_cast<ArticuloAlmacenable*>(i->first)) {
            if (i->second > art_almacenable->stock()) {
                const_cast<Usuario::Articulos&>(u.compra()).clear();
                throw SinStock(i->first);
            }
        } else {
            if(LibroDigital* libro_digital = dynamic_cast<LibroDigital*>(i->first)) {
                if(libro_digital->f_expir() < f)
                    u.compra(*i->first, 0);
            }
            if (u.compra().empty()) {
                throw Vacio(&u);
            }
        }
    }

    upe.asocia(*this, u);

    auto temp = u.compra();

    for(auto it: temp){
        
        total_ += it.first->precio()*it.second;
        part.pedir(*this, *it.first ,it.first->precio(), it.second);
        if(ArticuloAlmacenable * art_almacenable = dynamic_cast<ArticuloAlmacenable*>(it.first)) {
            art_almacenable->stock() -= it.second;
        }
    u.compra(*it.first,0);
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