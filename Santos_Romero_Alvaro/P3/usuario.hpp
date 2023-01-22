#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "tarjeta.hpp"
#include "articulo.hpp"
#include "../P1/cadena.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>

class Clave{

    public:
    Clave(const char* p);
    const Cadena& clave() const { return password; }
    enum Razon{CORTA, ERROR_CRYPT};
    bool verifica( const char* p) const;
    class Incorrecta{

        public:

        Incorrecta(const Razon r): error_(r){};
        Razon razon() const{ return error_; }
        private:
            Razon error_;
    };

    private:
    Cadena password;

};

class Numero;
class Tarjeta; 

class Usuario{

    public:

    Usuario(const Cadena &identificador, const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion, const Clave &password);
    Usuario &operator = (const Usuario &u) = delete;        //borro tanto operador de asignacion (enunciado)
    Usuario(const Usuario &u) = delete;                     //como el constructor de copia (enunciado)
    ~Usuario();

    typedef std::unordered_set<Cadena> Usuarios;
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    void es_titular_de(Tarjeta& tarjeta);
    void no_es_titular_de(Tarjeta& tarjeta);
    void compra(Articulo &art, unsigned cant = 1);
    unsigned n_articulos() const {return articulos_.size();};

    Cadena id() const {return identificador_;};
    Cadena nombre() const {return nombre_;};
    Cadena apellidos() const {return apellidos_;};
    Cadena direccion() const {return direccion_;};
    const Tarjetas& tarjetas() const {return tarjetas_;};
    const Articulos& compra() const {return articulos_;};

    friend std::ostream & operator << (std::ostream &os, const Usuario& usuario);

    class Id_duplicado{

    public:

    Id_duplicado(const Cadena &id):id_(id){};
    const Cadena idd() const {return id_;};

    private:

    Cadena id_;
    };

    private:

    Cadena identificador_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave password_;
    Articulos articulos_;
    Tarjetas tarjetas_;
    static Usuarios usuarios_;

};

void mostrar_carro(std::ostream &os, const Usuario& us);

#endif