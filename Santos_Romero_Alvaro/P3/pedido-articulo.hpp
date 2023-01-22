#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iostream>
#include <iomanip>
#include "articulo.hpp"
#include "pedido.hpp"
#include <map>

class LineaPedido{

    public:

        explicit LineaPedido(double price, unsigned int n = 1) { precio_venta_ = price; }
        const unsigned cantidad() const noexcept { return cantidad_; }
        const double precio_venta() const noexcept { return precio_venta_; }

    private:

        unsigned cantidad_;
        double precio_venta_;
};

std::ostream &operator <<(std::ostream &os, const LineaPedido &lped);

class Pedido;
class Articulo;

class OrdenaPedidos{
    public:
        bool operator() ( Pedido *p1, Pedido *p2) const;
};

class OrdenaArticulos{
    public:
        bool operator() (Articulo *a1, Articulo *a2) const;
};

class Pedido_Articulo{

    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
        typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> Pedidos_Articulos;
        typedef std::map<Articulo*, Pedidos, OrdenaArticulos> Articulos_Pedidos;

        void pedir(Articulo &art, Pedido &ped, double price, unsigned n = 1);
        void pedir(Pedido &ped, Articulo &art, double price, unsigned n = 1);

        const ItemsPedido& detalle(Pedido &ped) { return pedidos_articulos_.find(&ped)->second; }
        Pedidos ventas(Articulo &art) {
            if (articulos_pedidos_.find(&art) != articulos_pedidos_.end())
                return articulos_pedidos_.find(&art)->second;
            else {
                Pedidos v;
                return v;
            }
        }
    
        std::ostream &mostrarDetallePedidos(std::ostream &os);
        std::ostream &mostrarVentasArticulos(std::ostream &os);

    private:

        Pedidos_Articulos pedidos_articulos_;
        Articulos_Pedidos articulos_pedidos_;
};

std::ostream &operator << (std::ostream &os, const Pedido_Articulo::ItemsPedido iped);
std::ostream &operator << (std::ostream &os, const Pedido_Articulo::Pedidos &ped);
#endif