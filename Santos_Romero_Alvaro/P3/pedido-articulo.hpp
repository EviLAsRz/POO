#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "articulo.hpp"
#include "pedido.hpp"
#include <utility>
#include <map>

struct OrdenaArticulos: public std::binary_function <Articulo *, Articulo *, bool>{

    bool operator()(const Articulo *art1, const Articulo *art2) const {return art1->referencia() < art2->referencia();}
};

struct OrdenaPedidos: public std::binary_function <Pedido *, Pedido *, bool>{

    bool operator()(const Pedido *ped1, const Pedido *ped2) const {return ped1->numero() < ped2->numero();}
};


class LineaPedido{

    public:

        explicit LineaPedido(double price, unsigned int n = 1);
        unsigned cantidad() const {return cantidad_;};
        double precio_venta() const {return precio_venta_;};

    private:

        unsigned cantidad_;
        double precio_venta_;
};

std::ostream &operator <<(std::ostream &os, const LineaPedido &lped);

class Pedido_Articulo{

    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

        void pedir(Articulo &art, Pedido &ped, double price, unsigned n = 1);
        void pedir(Pedido &ped, Articulo &art, double price, unsigned n = 1);

        ItemsPedido& detalle(Pedido &ped);
        Pedidos ventas(Articulo &art);
    
        std::ostream &mostrarDetallePedidos(std::ostream &os);
        std::ostream &mostrarVentasArticulos(std::ostream &os);

    private:

        std::map<Articulo*, Pedidos, OrdenaArticulos> Art_ped_;
        std::map<Pedido*, ItemsPedido, OrdenaPedidos> Ped_art_;
};

std::ostream &operator << (std::ostream &os, const Pedido_Articulo::ItemsPedido &iped);
std::ostream &operator << (std::ostream &os, const Pedido_Articulo::Pedidos &ped);
#endif