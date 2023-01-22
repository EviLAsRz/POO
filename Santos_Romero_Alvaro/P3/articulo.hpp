#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <string>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <set>
#include <iomanip> 
#include <set> 
#include <stdlib.h> 
#include <iostream> 
#include <locale> 

class Autor{
    public:
        Autor(const Cadena &nom, const Cadena &ap, const Cadena &dir)
        :nom_(nom), ap_(ap), dir_(dir){}

        const Cadena &nombre() const noexcept { return nom_; }
        const Cadena &apellidos() const noexcept { return ap_; }
        const Cadena &direccion() const noexcept { return dir_; }

    private:
        Cadena nom_;
        Cadena ap_;
        Cadena dir_;
};

class Articulo{

    public:
        typedef std::set<Autor*> Autores;
        Articulo(const Autores & auts, const Cadena &refer, const Cadena &tit, const Fecha &f, const double &pr, const size_t exs = 0)
        : cod_refer_(Cadena(refer)), titulo_(Cadena(tit)), f_public_(f), ejemVentas_(exs), precio_(pr), autores_(auts){
        };

        inline const Cadena referencia() const {return cod_refer_;}
        inline Cadena titulo() const { return titulo_; }
        inline const Fecha &f_publi() const { return f_public_; }
        inline const double precio() const { return precio_; }
        inline double &precio() { return precio_; }
        inline const size_t stock() const { return ejemVentas_; }
        inline size_t &stock() { return ejemVentas_; }
        inline const Autores& autores() const noexcept{ return autores_; } 

        friend std::ostream& operator<<(std::ostream& salida,const Articulo& a) noexcept{
    	/* ------------------------------- VAR LOCALES Y LOCALE ------------------------------ */
            const auto autores = a.autores(); 
            auto i = autores.begin();
            std::locale::global( std::locale( "" ) ); 
    /* ------------------------------- INICIO FUN ------------------------------- */
            salida<<"["<<a.referencia()<<"] \""<<a.titulo()<<"\", de "<<(*i)->apellidos();
            i++;
            for (; i!=autores.end() ; ++i )
                salida << ", "<<(*i)->apellidos();
            
            salida << ". " << a.f_publi().anno() << ". " ;
            salida<<std::fixed<<std::setprecision(2)<<a.precio()<<" €\n\t"; 
            /* ----------- LLAMAMOS A LA IMPRESION ESPECIFICA DE CADA ARTICULO ---------- */
            a.impresion_especifica(salida); 
            return salida;
	}
    
    virtual void impresion_especifica(std::ostream& salida) const = 0; 
 	virtual ~Articulo(){} //destructor virtual para la eliminacion correcta de las herencias
	class Autores_vacios{};

    private:

        Cadena cod_refer_;
        Cadena titulo_;
        Fecha f_public_;
        size_t ejemVentas_;
        double precio_;
        const Autores autores_;
};

class LibroDigital: public Articulo {
    public:
        
        LibroDigital(const Autores &auts, const Cadena &ref, const Cadena &titulo, const Fecha &f_publi,
        const double precio, const Fecha &f_exp): Articulo(auts, ref, titulo, f_publi, precio), f_expir_(f_exp){};

        const Fecha f_expir() const noexcept { return f_expir_; }
        void impresion_especifica (std::ostream& salida) const {
            salida << "A la venta hasta el "<< f_expir_ << ".";
        }

    private:

        const Fecha f_expir_;
};

class ArticuloAlmacenable : public Articulo {

    public:

        ArticuloAlmacenable(const Autores &autores, const Cadena &ref, const Cadena &titulo, const Fecha &f_publi,
        const double precio, unsigned stock=0): Articulo(autores, ref, titulo, f_publi, precio), stock_(stock){}

        const unsigned stock() const noexcept { return stock_; }
        unsigned &stock() noexcept { return stock_; }
    
    protected:
        unsigned stock_;
};

class Libro : public ArticuloAlmacenable {

    public:

        Libro(const Autores &autores, const Cadena &ref, const Cadena &titulo, const Fecha &f_publi,
        const double precio, unsigned pgs, unsigned stock=0): ArticuloAlmacenable(autores, ref, titulo, f_publi, precio), paginas(pgs){}

        const unsigned n_pag() const noexcept {  return paginas; }
        void impresion_especifica(std::ostream &salida) const {
            salida << paginas << " págs., " << stock_ << " unidades.";
        }
    
    private:
        
        const unsigned paginas;
};

class Cederron : public ArticuloAlmacenable {

    public:
        Cederron(const Autores& auts, const Cadena& ref, const Cadena& titulo, const Fecha& f_publi, 
		const double precio, unsigned size, unsigned stock=0)
		:ArticuloAlmacenable(auts, ref, titulo, f_publi, precio, stock),size_(size){}

        const unsigned tam() const noexcept { return size_; }
        void impresion_especifica(std::ostream &salida) const {
            salida << size_ << " MB, " << stock_ << " unidades.";
        }

    private:
        
        const unsigned size_;
};

#endif  //ARTICULO_HPP_