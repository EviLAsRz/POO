#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include "usuario.hpp"
#include "pedido.hpp"
#include <utility>
#include <map>
#include <set>

class Usuario_Pedido{

    public:
        typedef std::set<Pedido*> Pedidos;

        void asocia(Pedido &ped, Usuario &u);
        void asocia(Usuario &u, Pedido &ped);

        Pedidos pedidos(Usuario &u);
        Usuario *cliente(Pedido &ped);
    
    private:

        std::map<Pedido*, Usuario*> pedu_;
        std::map<Usuario*, Pedidos> uped_;

};
    typedef std::set<Pedido*> Pedidos;
    inline void Usuario_Pedido::asocia(Pedido &ped, Usuario &u){
        
        uped_[&u].insert(&ped);
        pedu_[&ped] = &u;
    }

    inline void Usuario_Pedido::asocia(Usuario &u, Pedido &ped){

        return asocia(ped,u);
    }

    inline Pedidos Usuario_Pedido::pedidos(Usuario &u) {return uped_[&u];}
    inline Usuario* Usuario_Pedido::cliente(Pedido &p) {return pedu_[&p];}

#endif