#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"
#include <set>
#include <iostream>

using namespace std;
class Autor{

    public:
    Autor(const Cadena &nombre, const Cadena &apellidos, const Cadena & direccion): nombre_(nombre), apellidos_(apellidos), direccion_(direccion){}

    const Cadena &nombre() const{return nombre_;}
    const Cadena &apellidos() const {return apellidos_;}
    const Cadena &direccion() const {return direccion_;}

    private:
    
    Cadena nombre_, apellidos_, direccion_;
};
class Articulo{

    public:

    typedef std::set<Autor*> Autores;

    Articulo(const Autores &autor, const Cadena &refer, const Cadena &tit, const Fecha &f, double pr);

    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double &precio();
    const Autores &autores() const {return autor_;}

    virtual void impresion_especifica(ostream &os) const noexcept = 0;
    virtual ~Articulo() {}
    

    class Autores_vacios {};

    private:

    Autores autor_;
    Cadena cod_refer_;
    Cadena titulo_;
    Fecha f_public_;
    double precio_;
};

class ArticuloAlmacenable: public Articulo{

    public:

    ArticuloAlmacenable(const Autores &a, const Cadena &c, const Cadena &t, const Fecha &f, double p, unsigned stock): Articulo(a,c,t,f,p), stock_(stock){}
    unsigned stock() const noexcept{return stock_;}
    unsigned &stock() noexcept{return stock_;}

    protected:
    unsigned stock_;
};

class Libro: public ArticuloAlmacenable{

    public:

    Libro(const Autores &autores, const Cadena &refer, const Cadena &tit, const Fecha &f, double price, unsigned npag, unsigned stock = 0):
    ArticuloAlmacenable(autores,refer,tit,f,price,stock), n_pag_(npag){}
    unsigned n_pag() const noexcept {return n_pag_;}
    void impresion_especifica(ostream &os) const noexcept;

    private:

    const unsigned n_pag_;    
    
};

class Cederron :public ArticuloAlmacenable{

    public:

    Cederron(const Autores &a, const Cadena &c, const Cadena &t, const Fecha &f, double p, unsigned MB, unsigned stock):
    ArticuloAlmacenable(a,c,t,f,p,stock), tam_(MB){}

    unsigned tam() const noexcept {return tam_;}
    void impresion_especifica(ostream &os) const noexcept;

    private:

    const unsigned tam_;
};

class LibroDigital: public Articulo{

    public:

    LibroDigital(const Autores &a, const Cadena &c, const Cadena &t, const Fecha &fComp, double p, const Fecha& fExp):
    Articulo(a,c,t,fComp,p), f_expir_(fExp){}

    const Fecha &f_expir() const {return f_expir_;}
    void impresion_especifica(std::ostream &os) const noexcept;

    private:

    const Fecha f_expir_;
};

std::ostream &operator << (std::ostream &os, const Articulo &art);

inline void LibroDigital::impresion_especifica(ostream &os) const noexcept{

    os << "A la venta hasta el " << f_expir_ << '.';
}

inline void Libro::impresion_especifica(ostream &os) const noexcept{

    os << n_pag_ << " págs., "<< stock_ << " unidades.";
}

inline void Cederron::impresion_especifica(ostream &os) const noexcept{

    os << tam_ << " MB, "<< stock_ << " unidades.";
}

#endif
