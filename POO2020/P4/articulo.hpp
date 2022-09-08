
#ifndef ARTICULOS_HPP
#define ARTICULOS_HPP

#include <iostream>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

class Autor{
public:
    Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept
    : nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}

    const Cadena& nombre() const noexcept { return nombre_; }
    const Cadena& apellidos() const noexcept { return apellidos_; }
    const Cadena& direccion() const noexcept { return direccion_; }

private:
    Cadena nombre_, apellidos_, direccion_;
};

class Articulo{
public:

    typedef set<Autor*> Autores;

    

	Articulo(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f,  double precio);

	const Cadena& referencia() const noexcept { return referencia_; }
	const Cadena& titulo() const noexcept { return titulo_; }
	const Fecha& f_publi() const noexcept { return fecha_pub_; }

	double precio() const noexcept { return precio_; }
	double& precio() noexcept { return precio_; }

    const Autores& autores() const noexcept { return autor_; }

    virtual ~Articulo() {}
    virtual void impresion_especifica(ostream& os) const noexcept = 0;

    class Autores_vacios {};

private:
    Autores autor_;
	Cadena referencia_;
	Cadena titulo_;
	Fecha fecha_pub_;
	double precio_;
};

class ArticuloAlmacenable : public Articulo{
public:

    ArticuloAlmacenable(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p,unsigned stock)
        : Articulo(a, c, t, f, p), stock_(stock) {}

    unsigned stock() const noexcept { return stock_; }
	unsigned& stock() noexcept { return stock_;}

protected:
    unsigned stock_;
};

class Libro : public ArticuloAlmacenable{
public:
   Libro(const Autores& autores, const Cadena& ref, const Cadena& tit,const Fecha& fp,
		   double price, unsigned npag, unsigned stock = 0):
			 ArticuloAlmacenable(autores,ref,tit,fp,price,stock),n_pag_(npag) {}

    unsigned n_pag() const noexcept { return n_pag_; }
    void impresion_especifica(ostream& os) const noexcept;

private:
    const unsigned n_pag_;

    
};

class Cederron : public ArticuloAlmacenable{
public:
  Cederron(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p, unsigned MB, unsigned stock)
    : ArticuloAlmacenable(a, c, t, f, p, stock), tam_(MB) {}
  
  unsigned tam() const noexcept { return tam_; }
  void impresion_especifica(ostream& os) const noexcept;

private:
  const unsigned tam_;
  
  
};

class LibroDigital : public Articulo{
public:
    LibroDigital(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& fComp, double p, const Fecha& fExp)
        : Articulo(a, c, t, fComp, p), f_expir_(fExp) {}

    const Fecha& f_expir() const noexcept { return f_expir_; }
    void impresion_especifica(ostream& os) const noexcept;

private:
    const Fecha f_expir_;

    
};

ostream& operator<<(ostream& os, const Articulo& a) noexcept;

inline void LibroDigital::impresion_especifica(ostream& os) const noexcept
{
    os << "A la venta hasta el " << f_expir_ << '.';
}

inline void Libro::impresion_especifica(ostream& os) const noexcept
{
    os << n_pag_ << " págs., " << stock_ << " unidades.";
}

inline void Cederron::impresion_especifica(ostream& os) const noexcept
{
    os << tam_ << " MB, " << stock_ << " unidades.";
}




#endif
