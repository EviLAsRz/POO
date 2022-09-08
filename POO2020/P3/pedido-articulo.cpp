//
// Created by Claudia Soriano Roldán on 10/05/2019.
//

#include <iomanip>
#include <ostream>
#include "pedido-articulo.hpp"

/********************** LINEAPEDIDO **********************/

LineaPedido::LineaPedido(double price, unsigned int n): cantidad_(n), precio_venta_(price){}

std::ostream& operator <<(std::ostream& output, const LineaPedido& lp)
{
    output << std::fixed << std::setprecision(2) << lp.precio_venta() << ' ' << "€" << '\t' << lp.cantidad() ;

    return output ;
}

/******************* PEDIDO_ARTICULO ********************/

void Pedido_Articulo::pedir(Pedido& p, Articulo& a,double price, unsigned n)
{
    Art_Ped_[&a].insert(std::make_pair(&p,LineaPedido(price,n))) ;
    Ped_Art_[&p].insert(std::make_pair(&a,LineaPedido(price,n))) ;
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p,double price, unsigned n)
{
    pedir(p,a,price,n) ;
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p)
{
    return Ped_Art_[&p] ;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a)
{
    return Art_Ped_[&a] ;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& output)
{
    for(auto it = Art_Ped_.begin(); it != Art_Ped_.end(); it++)
    {
        output << "Ventas" << "[" << (it->first)->referencia() << "]" ;
        output << "\"" << it->first->titulo() << "\"" ;
        output << it->second << std::endl ;
    }

    return output ;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& output)
{
    double price = 0;

    for(auto it = Ped_Art_.begin(); it != Ped_Art_.end() ; it++)
    {

        output << "Pedido núm." << (it->first)->numero() << "\t" ;
        output << "Cliente: " << (it->first)->tarjeta()->titular()->nombre() << "\t";
        output << "Fecha: " << (it->first)->fecha() << (it->second) ;

        price = price + (it->first)->total() ;
    }

    output << std::fixed ;
    output << "TOTAL VENTAS: " << std::setprecision(2) << price << " €" << std::endl ;

    return output ;
}

std::ostream& operator <<(std::ostream& output,const Pedido_Articulo::ItemsPedido& ip)
{

    double price = 0;

    output << "\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << "PVP \t Cant.\t Articulo\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto it = ip.begin(); it != ip.end() ; it++)
    {

        output << (it->second).precio_venta() << "€\t" ;
        output << (it->second).cantidad() << "\t" ;
        output << "[ "<< (it->first)->referencia() << "]\t";
        output << "\"" << (it->first)->titulo() << "\"" << std::endl;

        price = price + (it->second).cantidad() * (it->second).precio_venta() ;
    }

    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << std::fixed ;
    output << std::setprecision(2) << price << " €" << std::endl ;

    return output ;
}

std::ostream& operator <<(std::ostream& output, const Pedido_Articulo::Pedidos& pa)
{

    double price = 0;
    unsigned t = 0  ;

    output << "\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << "PVP \t Cant.\t Fecha venta\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto it = pa.begin(); it != pa.end() ; it++)
    {

        output << " " << (it->second).precio_venta() << " €\t" ;
        output << (it->second).cantidad() << "\t" ;
        output << (it->first)->fecha() << std::endl ;

        price = price + (it->second).cantidad() * (it->second).precio_venta() ;
        t += (it->second).cantidad() ;
    }


    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << std::fixed ;
    output << std::setprecision(2) << price << " €\t" << t << std::endl ;

    return output ;

}

