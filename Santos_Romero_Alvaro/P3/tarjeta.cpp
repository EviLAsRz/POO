#include "tarjeta.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cctype>

bool luhn(const Cadena &numero);    //se declara la funcion luhn de luhn.cpp

//CLASE NUMERO

Numero::Numero(const Cadena &numero): numero_(longitud(numero)){

    if (std::count_if(numero_.begin(), numero_.end(), static_cast<int(*)(int)>(std::isdigit)) != numero_.length()){
        //se comprueba si en la cadena existe caracteres distintos de numeros
        //para ello, se utiliza static_cast, para convertir los caracteres a numero, y luego con isdigit se comprueba si es un numero
        //y que no sea distinto del tamaño del numero

        throw Incorrecto(Razon::DIGITOS);
    }

    if(!luhn(numero_)){
        throw Incorrecto(Razon::NO_VALIDO); //se comprueba que el ultimo digito es de control
    }
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

Tarjeta::Tarjeta(const Numero &numero, Usuario &usuario, const Fecha &fecha_cad):numero_(numero), usuario_(&usuario), fecha_cad_(fecha_cad), activa_(true){

    if(fecha_cad_ < Fecha()){       //si la fecha de la tarjeta es menor que la fecha actual, significa que ha caducado

        throw Caducada(fecha_cad_);
    }

    const char *n = numero;

    tipo_ = Tipo::OTRO; //por defecto, si no cumple ninguna condicion de abajo, sera del tipo OTRO

    if((n[0] == '3' && n[1] == '4') || (n[0] == '3' && n[1] == '7')){   //si empieza por 34 o por 37

        tipo_ = Tipo::AmericanExpress;
    }

    if((n[0] == '3' && n[1] != '4') || (n[0] == '3' && n[1] != '7')){   //si empieza por 3, salvo 34 o 37

        tipo_ = Tipo::JCB;
    }

    if(n[0] == '4'){   //si empieza por 4

        tipo_ = Tipo::VISA;
    }

    if(n[0] == '5'){   //si empieza por 5

        tipo_ = Tipo::Mastercard;
    }

    if(n[0] == '6'){   //si empieza por 6

        tipo_ = Tipo::Maestro;
    }

    usuario.es_titular_de(*this); //usuario al que pertenece la tarjeta es el usuario con que se crea el objeto tarjeta
}

Tarjeta::~Tarjeta(){

    if(Usuario *u = const_cast<Usuario*>(usuario_)){    //si el usuario coincide, se desvincula de la tarjeta
        u->no_es_titular_de(*this);
    }
}

bool Tarjeta::activa(bool valor){   //cambiar el estado de la tarjeta
    activa_ = valor;
    return activa_;
}

void Tarjeta::anula_titular(){

    usuario_ = nullptr;     //puntero a usuario = 0;
}

bool operator <(const Tarjeta &a, const Tarjeta &b){
    return a.numero() < b.numero(); //devuelve true si es menor a que b
}

bool operator >(const Tarjeta &a, const Tarjeta &b){
    return b.numero() < a.numero(); //devuelve true si es menor b que a
}
std::ostream &operator <<(std::ostream &os, const Tarjeta::Tipo& tipo){

    switch(tipo){ //dependiendo del tipo, se introduce uno y otro
        
        case Tarjeta::VISA: os << "VISA";break;
        case Tarjeta::Mastercard: os << "Mastercard";break;
        case Tarjeta::Maestro: os << "Maestro";break;
        case Tarjeta::JCB: os << "JCB";break;
        case Tarjeta::AmericanExpress: os << "AmericanExpress";break;
        case Tarjeta::OTRO: os << "OTRO";break;
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
