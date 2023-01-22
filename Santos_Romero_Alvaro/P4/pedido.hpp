#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include "usuario.hpp" 
#include "tarjeta.hpp" 
#include "../P1/fecha.hpp" 
#include "../P1/cadena.hpp"
#include "articulo.hpp" 
#include "pedido-articulo.hpp" 
#include "usuario-pedido.hpp" 
#include<iomanip> 
#include<iostream> 
class Pedido_Articulo;
class Pedido {

    public:

        static unsigned n_total_pedidos(){ return n_ped_t_; }
        Pedido(Usuario_Pedido& , Pedido_Articulo&, Usuario& , const Tarjeta& , const Fecha& f= Fecha());//f= fecha actual
/* -------------------------- clases de excepciones ------------------------- */

        class Vacio{ 

            public: 
                Vacio(Usuario* us): us_(us){} 
                Usuario& usuario() const{ return *us_; } 
            
            private:
                Usuario* us_;
        };

        class Impostor{ 

            public: 
                Impostor(Usuario* us): us_(us){} 
                Usuario& usuario() const{return *us_;} 

            private:
                Usuario* us_;
        };

        class SinStock{ 

            public: 
                SinStock(Articulo* art): art_(art){} 
                Articulo& articulo() const{return *art_;}

            private:
                Articulo* art_; 
        };

/* -------------------------- metodos observadores -------------------------- */

    const int numero() const noexcept { return numero_ped_; } 
    const Tarjeta* tarjeta() const noexcept { return tarjeta_pago_; } 
    const Fecha fecha() const noexcept { return fecha_pedido_; } 
    const double total() const noexcept { return importe_total_; } 

    private: 
        int numero_ped_; 
        const Tarjeta* tarjeta_pago_;  
        double importe_total_; 
        Fecha fecha_pedido_;
        static unsigned n_ped_t_; 
};
std::ostream& operator<<(std::ostream& salida, const Pedido& p);

#endif