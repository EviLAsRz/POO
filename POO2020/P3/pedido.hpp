//
// Created by Claudia Soriano Roldán on 08/05/2019.
//

#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>
#include <utility>
#include <iomanip>
#include "../P1/fecha.hpp"
#include "usuario.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido {
public:
    Pedido(Usuario_Pedido& usuped, Pedido_Articulo& pedart, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha() );

    int numero() const { return num_ ; }
    double total() const { return total_;}
    Fecha fecha() const  {return fecha_;}
    static int n_total_pedidos() {return num_pedido_;}
    const Tarjeta* tarjeta() const {return tarjeta_ ;}

    class Impostor{
    public:
        Impostor(Usuario& u): usu_(&u) {}
        Usuario& usuario() const {return *usu_;};
    private:
        Usuario* usu_;
    };

    class SinStock{
    public:
        SinStock(Articulo* a):articulo_(a) {}
        Articulo& articulo() const { return *articulo_ ;} ;
    private:
        Articulo* articulo_ ;
    };

    class Vacio{
    public:
        Vacio(Usuario& u): usu_(&u) {}
        Usuario& usuario() const {return *usu_;};
    private:
        Usuario* usu_;
    };

private:
    int num_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static int num_pedido_;
};

std::ostream& operator <<(std::ostream& output, const Pedido& p);

#endif //P3_PEDIDO_H
