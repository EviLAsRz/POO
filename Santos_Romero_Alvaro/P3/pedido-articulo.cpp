#include <ostream>
#include <iomanip>
#include "pedido-articulo.hpp"

LineaPedido::LineaPedido(double price, unsigned int n): cantidad_(n), precio_venta_(price){}

std::ostream &operator <<(std::ostream &os, const LineaPedido &lped){

    os << std::fixed << std::setprecision(2) << lped.precio_venta() << ' ' << "€" << '\t' << lped.cantidad();

    return os;
}

void Pedido_Articulo::pedir(Pedido &ped, Articulo &art, double price, unsigned n){
    
    Art_ped_[&art].insert(std::make_pair(&ped,LineaPedido(price,n)));
    Ped_art_[&ped].insert(std::make_pair(&art, LineaPedido(price,n)));
}

void Pedido_Articulo::pedir(Articulo &art, Pedido &ped, double price, unsigned n){

    pedir(ped, art, price, n);
}

Pedido_Articulo::ItemsPedido &Pedido_Articulo::detalle(Pedido &ped){
    
    return Ped_art_[&ped];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo &art){

    return Art_ped_[&art];
}

std::ostream &Pedido_Articulo::mostrarVentasArticulos(std::ostream &os){


    for(auto i = Art_ped_.begin(); i != Art_ped_.end(); i++){

        os << "Ventas" << "[" << (i->first)->referencia() << "]";
        os << "\"" << i->first->titulo() << "\"";
        os << i->second << std::endl;
    }

    return os;
}

std::ostream &Pedido_Articulo::mostrarDetallePedidos(std::ostream &os){

    double price = 0;

    for(auto i = Ped_art_.begin(); i != Ped_art_.end(); i++){

        os << "Pedido núm." << (i->first)->numero() << "\t";
        os << "Cliente: " << (i->first)->tarjeta()->titular()->nombre() << "\t";
        os << "Fecha: " << (i->first)->fecha() << (i->second);

        price += (i->first)->total();
    }

    os << std::fixed << "TOTAL VENTAS: " << std::setprecision(2) << price << " €" << std::endl;

    return os;
}

std::ostream &operator << (std::ostream &os, const Pedido_Articulo::ItemsPedido &iped){

    double price = 0;

    os << "\n";
    os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl;
    os << "PVP \t Cant. \t Articulo\n";
    os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl;

    for(auto i = iped.begin(); i!= iped.end(); i++){
        os << (i->second).precio_venta() << "€\t";
        os << (i->second).cantidad() << "\t";
        os << "[" << (i->first)->referencia() << "]\t";
        os << "\"" << (i->first)->titulo() << "\"" << std::endl;

        price += (i->second).cantidad() * (i->second).precio_venta();
    }

    os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl;
    os << std::fixed << std::setprecision(2) << price << " €" << std::endl;

    return os;
}

std::ostream &operator << (std::ostream &os, const Pedido_Articulo::Pedidos &ped){

    double price = 0;

    os << "\n";
    os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl;
    os << "PVP \t Cant. \t Fecha venta\n";
    os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl;

    for(auto i = ped.begin(); i!= ped.end(); i++){
        os << " " <<  (i->second).precio_venta() << "€\t";
        os << (i->second).cantidad() << "\t";
        os << (i->first)->fecha() << std::endl;

        price += (i->second).cantidad() * (i->second).precio_venta();
    }

    os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl;
    os << std::fixed << std::setprecision(2) << price << " €" << std::endl;

    return os;
}
