#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <map>
#include <set>

class Pedido;
class Usuario;
class Usuario_Pedido{

    public:

        typedef std::set<Pedido*> Pedidos;
        typedef std::map<Usuario*, Pedidos> User_Ped;
        typedef std::map<Pedido*, Usuario*> Ped_User;

        void asocia(Usuario &u, Pedido &ped) {
            user_ped_[&u].insert(&ped);
            ped_user_[&ped] = &u;
        }
        void asocia(Pedido &ped, Usuario &u) { asocia(u, ped); }

        Pedidos pedidos(Usuario &u){ return user_ped_.find(&u)->second;}
        Usuario *cliente(Pedido &ped){ return ped_user_.find(&ped)->second;}
    
    private:

        User_Ped user_ped_;
        Ped_User ped_user_;

};

#endif