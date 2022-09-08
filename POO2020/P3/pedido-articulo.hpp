//
// Created by Claudia Soriano Roldán on 10/05/2019.
//

#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "articulo.hpp"
#include "pedido.hpp"
#include <utility>
#include <map>


struct OrdenaArticulos: public std::binary_function <Articulo*, Articulo*, bool>
{
    bool operator()(const Articulo* a1, const Articulo* a2) const { return a1->referencia() < a2->referencia() ; }
};


struct OrdenaPedidos: public std::binary_function <Pedido*, Pedido*, bool>
{
    bool operator()(const Pedido* p1, const Pedido* p2) const {return p1->numero() < p2->numero();}
};

/******************* CLASE LINEAPEDIDO ********************/

class LineaPedido{
public:
    explicit  LineaPedido(double price, unsigned int n = 1);
    unsigned cantidad() const { return cantidad_; };
    double precio_venta() const {return precio_venta_; };

private:
    unsigned cantidad_;
    double precio_venta_;
};

std::ostream& operator << (std::ostream& output, const LineaPedido& lp) ;


/******************* CLASE PEDIDO_ARTICULO ********************/

class Pedido_Articulo{
public:

    typedef std::map <Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido ;
    typedef std::map <Pedido*, LineaPedido, OrdenaPedidos > Pedidos ;

    void pedir(Articulo& a, Pedido& p,double price, unsigned n = 1) ;
    void pedir(Pedido& p, Articulo& a,double price, unsigned n = 1) ;

    ItemsPedido& detalle(Pedido& p);
    Pedidos ventas(Articulo& a);

    std::ostream& mostrarDetallePedidos(std::ostream& output);
    std::ostream& mostrarVentasArticulos(std::ostream& output);

private:
    std::map <Articulo*, Pedidos, OrdenaArticulos> Art_Ped_ ;
    std::map <Pedido*, ItemsPedido, OrdenaPedidos> Ped_Art_ ;
};

std::ostream& operator <<(std::ostream& output, const Pedido_Articulo::ItemsPedido& ip) ;
std::ostream& operator <<(std::ostream& output, const Pedido_Articulo::Pedidos& p) ;

#endif //P3_PEDIDO_ARTICULO_H
