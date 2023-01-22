#include "tarjeta.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cctype>

bool luhn(const Cadena &numero);    //se declara la funcion luhn de luhn.cpp
std::set<Numero>Tarjeta::numeros;
//CLASE NUMERO

Numero::Numero(const Cadena &numero): numero_(longitud(numero)){

    if (std::count_if(numero_.begin(), numero_.end(), static_cast<int(*)(int)>(std::isdigit)) != numero_.length())

        throw Incorrecto(Razon::DIGITOS);
    
    if (numero_.length() < 13 || numero_.length() > 19)

        throw Incorrecto(Razon::LONGITUD);

    if(!luhn(numero_))
        throw Incorrecto(Razon::NO_VALIDO); //se comprueba que el ultimo digito es de control
    
}

Cadena Numero::espacios(const Cadena &numero){

    Cadena cad(numero);

    std::remove_if(cad.begin(), cad.end()+1,[](char c){return isspace(c);});    //si se cumple que el caracter c es un espacio, se borra
    return Cadena(cad.c_str());
}

Cadena Numero::longitud(const Cadena &numero){

    Cadena cad = espacios(numero);  //cadena sin espacios

    if(cad.length() < 13 || cad.length() == 0 || cad.length() > 19){        //si es mayor que 19, menor que 13 o 0

        throw Incorrecto(Razon::LONGITUD);
    }

    return cad; 
}

Numero::operator const char*() const{

    return numero_.c_str();         //convierte Numero en cadena de bajo nivel
}

bool operator <(const Numero &a, const Numero &b){

    return strcmp(a,b) < 0;     //si es > o =, devuelve falso
}

//CLASE TARJETA

Tarjeta::Tarjeta(const Numero &numero, Usuario &usuario, const Fecha &fecha_cad):numero_(numero), usuario_(&usuario),
fecha_cad_(fecha_cad), activa_(true), tipo_(selec_tipo()){

    if (fecha_cad_ < Fecha()) {

        throw Caducada(fecha_cad_);
    }

    if (numeros.insert(numero_).second == false){

        throw Num_duplicado(numero_);
    }

    auto usu_ = const_cast<Usuario*>(usuario_);

    usu_->es_titular_de(*this); //usuario al que pertenece la tarjeta es el usuario con que se crea el objeto tarjeta
}

Tarjeta::Tipo Tarjeta::selec_tipo()const{
    Cadena aux_tipo =numero_.n();
    if (aux_tipo[0]=='3')
    {
        if (aux_tipo[1]=='4'||aux_tipo[1]=='7')
        {
            return AmericanExpress;
        }
        else{
            return JCB;
        } 
    }
    else if(aux_tipo[0]=='4'){
        return VISA;
    }
    else if(aux_tipo[0]=='5'){
        return Mastercard;
    }
    else if (aux_tipo[0]=='6')
    {
        return Maestro;
    }
    else
        return Otro;
}

Tarjeta::~Tarjeta(){

    if(Usuario *u = const_cast<Usuario*>(usuario_)){    //si el usuario coincide, se desvincula de la tarjeta
        u->no_es_titular_de(*this);
    }
    numeros.erase(numero_);
}

bool Tarjeta::activa(bool valor){   //cambiar el estado de la tarjeta
    activa_ = valor;
    return activa_;
}

bool operator <(const Tarjeta &a, const Tarjeta &b){
    return a.numero() < b.numero(); //devuelve true si es menor a que b
}

std::ostream &operator <<(std::ostream &os, const Tarjeta::Tipo& tipo){

    switch(tipo){ //dependiendo del tipo, se introduce uno y otro
        
        case Tarjeta::VISA: os << "VISA";break;
        case Tarjeta::Mastercard: os << "Mastercard";break;
        case Tarjeta::Maestro: os << "Maestro";break;
        case Tarjeta::JCB: os << "JCB";break;
        case Tarjeta::AmericanExpress: os << "AmericanExpress";break;
        case Tarjeta::Otro: os << "OTRO";break;
    }
    return os;
}

std::ostream &operator << (std::ostream &os, const Tarjeta &tarjeta){

    Cadena nomTemp = tarjeta.titular()->nombre();          //guardo nombre y apellido en auxiliares para poder convertirlos en mayusculas
    Cadena apelTemp = tarjeta.titular()->apellidos();

    for(unsigned i = 0; i < nomTemp.length(); i++){

        nomTemp[i] = toupper(nomTemp[i]);           //funcion toupper para convertir cada elemento en mayusculas 
    }

    for(unsigned i = 0; i < apelTemp.length(); i++){

        apelTemp[i] = toupper(apelTemp[i]);           //idem para el apellido
    }

    //sobrecarga de inserccion para introducir directamente el tipo de la tarjeta
    os << tarjeta.tipo() << "\n" << tarjeta.numero() << "\n"
        << nomTemp << " " << apelTemp << "\n"
        << "Caduca: " << std::setfill('0') << std::setw(2) << tarjeta.caducidad().mes()      //caracter de relleno: 0 y extensión maxima de la inserción
        << "/" << std::setw(2) << (tarjeta.caducidad().anno() % 100) << "\n" << std::endl;   //se divide el anno entre 100 para que solo aparezca los dos ultimos digitos

    return os;
}
