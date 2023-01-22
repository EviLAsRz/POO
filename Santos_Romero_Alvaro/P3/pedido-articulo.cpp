#include <iostream>
#include "pedido-articulo.hpp"

std::ostream &operator <<(std::ostream &os, const LineaPedido &lped){

    os << std::fixed << std::setprecision(2) << lped.precio_venta() << ' ' << "€" << '\t' << lped.cantidad();

    return os;
}

void Pedido_Articulo::pedir(Pedido &ped, Articulo &art, double price, unsigned n){
    
    pedidos_articulos_[&ped].insert(std::make_pair(&art, LineaPedido(price, n)));
    articulos_pedidos_[&art].insert(std::make_pair(&ped, LineaPedido(price, n)));
}

void Pedido_Articulo::pedir(Articulo &art, Pedido &ped, double price, unsigned n){

    pedir(ped, art, price, n);
}

std::ostream &Pedido_Articulo::mostrarVentasArticulos(std::ostream &os){


    for(auto i : articulos_pedidos_){

        os << "Ventas de " << "[" << i.first->referencia() << "]";
        os << "\"" << i.first->titulo() << "\" \n";
        os << i.second << std::endl;
    }

    return os;
}

std::ostream &Pedido_Articulo::mostrarDetallePedidos(std::ostream &os){

    double price = 0;

    for(auto i : pedidos_articulos_){

        os << "Pedido núm." << i.first->numero() << "\t";
        os << "Cliente: " << i.first->tarjeta()->titular()->nombre() << "\t";
        os << "Fecha: " << i.first->fecha() << i.second;

        price += i.first->total();
    }

    os << std::fixed << "TOTAL VENTAS: " << std::setprecision(2) << price << " €" << std::endl;

    return os;
}

std::ostream &operator << (std::ostream &os, const Pedido_Articulo::ItemsPedido iped){

    double price = 0;
    Pedido_Articulo::ItemsPedido::const_iterator i;
    os << std::endl << "====================================================\n" << std::endl;
    os << " PVP \t Cant. \t Articulo \n"; 
    os << "====================================================\n" << std::endl; 

    for(auto i = iped.begin(); i!= iped.end(); i++){
        os << " " <<(i->second).precio_venta() << "€\t";
        os << (i->second).cantidad() << "\t";
        os << "[" << (i->first)->referencia() << "]\t";
        os << "\"" << (i->first)->titulo() << "\"" << std::endl;

        price += (i->second).cantidad() * (i->second).precio_venta();
    }

    os << "===================================================\n" << std::endl;
    os << std::fixed;
    os << std::setprecision(1) << price << " €" << std::endl; 

    return os;
}

std::ostream &operator << (std::ostream &os, const Pedido_Articulo::Pedidos &ped){

    double price = 0;
    unsigned total = 0;
    Pedido_Articulo::Pedidos::const_iterator i;

    os << "====================================================\n" << std::endl; 
    os << " PVP \t Cant. \t Fecha venta \n";
    os << "====================================================\n" << std::endl;

    for(auto i : ped){
        os << " " <<  i.second.precio_venta() << "€\t";
        os << i.second.cantidad() << "\t" << i.first->fecha() << std::endl;

        price += (i.second.cantidad() * i.second.precio_venta());
        total += i.second.cantidad();
    }

    os << "====================================================\n" << std::endl;
    os << std::fixed;
    os << std::setprecision(2) << price << " €\t" << total <<std::endl;  

    return os;
}

bool OrdenaPedidos::operator() (Pedido *p1, Pedido *p2) const { return (p1->numero() < p2->numero()); }
bool OrdenaArticulos::operator() (Articulo* a1, Articulo *a2) const { return (a1->referencia() < a2->referencia()); }
