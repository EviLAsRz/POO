#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>
#include "../P1/fecha.hpp"
#include <iomanip>
#include <utility>
#include "usuario.hpp"


class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
    
public:

    Pedido(Usuario_Pedido &upe, Pedido_Articulo &part, Usuario &u, const Tarjeta &t, const Fecha &f = Fecha());

    int numero() const {return num_;}
    double total() const {return total_;}
    Fecha fecha() const {return fecha_;}
    static int n_total_pedidos() {return num_pedido_;}
    const Tarjeta* tarjeta() const {return tarjeta_;}
    
    
    class Impostor{

    public:

        Impostor(Usuario &u): us(&u){}
        Usuario &usuario() const {return *us;};
    private:

        Usuario *us;
    };

    class SinStock{
    public:

        SinStock(Articulo *a): art(a){}
        Articulo &articulo() const {return *art;};
    private:

        Articulo *art;
    };

    class Vacio{
    
    public:
        Vacio(Usuario &u):us(&u){}
        Usuario &usuario() const {return *us;};

    private:

        Usuario *us;
    };

private:

    int num_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static int num_pedido_;
    
};

std::ostream &operator << (std::ostream &os, const Pedido &ped);
#endif