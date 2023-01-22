#include "usuario.hpp"
#include <iostream>
#include <random>
#include <iomanip>
#include <unistd.h>
#include <set>
#include <random>

Clave::Clave(const char* p){

    if(strlen(p) < 5){  //lanzamiento de excepcion corta: contraseña corta
    throw Incorrecta(Razon::CORTA);
    }

    char const lib[] = "0123456789qwertyuiopasdfghjklzxcvbnmOPASDFGHJKLZXCVBNM"; //cadena utilizada para encryptar
    std::random_device r_dev;
    char cifrar[2] = {lib[rand() % 64],lib[rand()% 64]};

    if(crypt(p,cifrar) == nullptr){    //lanzamiento de excepcion error_crypt: encryptado erroneo
    throw Clave::ERROR_CRYPT;
    }
    password = crypt(p,cifrar);     //funcion crypt para cifrar la contraseña
}

bool Clave::verifica(const char *p) const{

    return std::strcmp(crypt(p, password.c_str()), password.c_str()) == 0; //devuelve true si las contraseñas coinciden 
}

//apartado de usuario
Usuario::Usuarios Usuario::usuarios_;

Usuario::Usuario(const Cadena &identificador, const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion, const Clave &password):
identificador_(identificador), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), password_(password){

    if(!usuarios_.insert(identificador).second){    //si existe otro usuario con el mismo id, lanza excepcion
        throw Id_duplicado(identificador_);
    }
}

void Usuario::es_titular_de(Tarjeta &tarjeta){

    if(this == tarjeta.titular()){      //si el usuario coincide, se emparejan mediante make_pair y se introduce en el mapa
        tarjetas_.insert(std::make_pair(tarjeta.numero(), &tarjeta));
    }
}

void Usuario::no_es_titular_de(Tarjeta &tarjeta){

    tarjeta.anula_titular();            //puntero usuario a 0
    tarjetas_.erase(tarjeta.numero());  //se borra el numero
}

void Usuario::compra(Articulo &art, unsigned cant){

    auto encontrado = articulos_.find(&art);
    if (encontrado == articulos_.end()) {
        if(cant > 0)             //si la cantidad es distinta de 0, entonces a ese articulo se le asocia la cantidad comprada
            articulos_[const_cast<Articulo*>(&art)] = cant;
    }else {
        if(cant > 0)
            articulos_[const_cast<Articulo*>(&art)] = cant;
        else
            articulos_.erase(const_cast<Articulo*>(&art));
    }
}

Usuario::~Usuario(){

    for(auto i = tarjetas_.begin(); i != tarjetas_.end(); i++){ //se recorre el mapa, se llama a la funcion anula_titular y se borra en id

        i->second->anula_titular();
    }

    usuarios_.erase(identificador_);
}

void mostrar_carro(std::ostream &os, const Usuario& us){
    os << "Carrito de compra de "<< us.id() << " [Artículos: " << us.n_articulos() << "]" << std::endl
        << " Cant. Artículo" << std::endl;
    os << std::setw(95)<< std::setfill('=') << "\n";

        for(auto i = us.compra().begin(); i != us.compra().end(); i++){     //se recorre el unordered_map

            os << " " << i->second << "\t"                  //second = unsigned que nos imprime la cantidad
               << "[" << i->first->referencia() << "] \""   //i->first = puntero a articulo
                << i->first->titulo() << "\", ";
            os << i->first->f_publi().anno() << ". "
                << std::setprecision(2) << std::fixed << i->first->precio() << " €" << std::endl;
        }
}

std::ostream &operator << (std::ostream &os, const Usuario& usuario){

    os << usuario.identificador_ << " [" << usuario.password_.clave() << "] "   //formato especificado en la practica
        << usuario.nombre_ << " " << usuario.apellidos_ << "\n"                  //se introducen los atributos del usuario
        << usuario.direccion_ << std::endl;
    os << "Tarjetas:\n";

    for(auto i = usuario.tarjetas().begin(); i != usuario.tarjetas().end(); i++){   //se recorre el set y se imprime sus tarjetas asociadas
        os << *i->second << std::endl;
    }
    return os;
}