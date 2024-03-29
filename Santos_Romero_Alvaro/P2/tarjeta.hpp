#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include <iostream>
#include <set>

class Usuario;

class Numero{

    public:

    enum Razon {LONGITUD, NO_VALIDO, DIGITOS};

    Numero(const Cadena &numero);
    operator const char* () const;
    const char* n()const{return numero_.c_str();}
    Cadena espacios(const Cadena &cadena);      //quitar los espacios
    Cadena longitud(const Cadena &cadena);      //longitud de la cadena
    friend bool operator <(const Numero& a, const Numero &b);
    
    class Incorrecto{

        public:

        Incorrecto(Razon r):error_(r){}
        const Razon& razon() const {return error_;};

        private:
        
        Razon error_;
    };

    private:

    Cadena numero_;

};


class Tarjeta{

    public:

    typedef std::set<Numero> num;
    enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

    Tarjeta(const Numero &numero, Usuario &usuario, const Fecha &fecha_cad);
    Tarjeta(const Tarjeta &tarjeta) = delete;
    Tarjeta &operator = (const Tarjeta &tarjeta) = delete;
    ~Tarjeta();

    Numero numero() const {return numero_;};
    Fecha caducidad() const {return fecha_cad_;};
    const Usuario *titular() const {return usuario_;};
    bool activa() const {return activa_;};
    Tipo tipo() const {return tipo_;};
    Tarjeta::Tipo selec_tipo()const;
    bool activa(bool valor);
    void anula_titular() {usuario_ = nullptr; activa_ = false;}
    //clase caducada
    class Caducada{

        public:

            Caducada(const Fecha &fecha):fecha_(fecha){};
            Fecha cuando() const {return fecha_;};

        private:

            Fecha fecha_;
    };

    class Desactivada{};

    //clase num_duplicado
    class Num_duplicado{
        
        public:

            Num_duplicado(const Numero &numero):num_(numero){};
            const Numero que() const {return num_;};

        private:

            Numero num_;
    };

    private:

    Numero numero_;
    const Usuario *usuario_;
    Fecha fecha_cad_;
    bool activa_;
    Tipo tipo_;
    static std::set<Numero> numeros;

};

std::ostream &operator <<(std::ostream &os, const Tarjeta::Tipo &tipo);
std::ostream &operator <<(std::ostream &os, const Tarjeta &tarjeta);
bool operator <(const Tarjeta &a, const Tarjeta &b);
bool operator <(const Tarjeta &a, const Numero&);

#endif