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

        Pedidos pedidos(Usuario &u){ return uped_[&u];}
        Usuario *cliente(Pedido &ped){ return pedu_[&ped];}
    
    private:

        std::map<Pedido*, Usuario*> pedu_;
        std::map<Usuario*, Pedidos> uped_;

};

    inline void Usuario_Pedido::asocia(Pedido &ped, Usuario &u){
        
        uped_[&u].insert(&ped);
        pedu_[&ped] = &u;
    }

    inline void Usuario_Pedido::asocia(Usuario &u, Pedido &ped){

        return asocia(ped,u);
    }

#endif