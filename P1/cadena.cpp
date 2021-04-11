#include <iostream>
#include <cstring>
#include <stdexcept>
#include "cadena.hpp"
#include <cstdio>

using namespace std;

//constructor de clase cadena (recibe dos parametros (size_t y char) y devuelve una cadena)
Cadena::Cadena(size_t t, char c): tam_(t){

s_ = new char[tam_+1];             //tam +1 porque el ultimo caracter es '\0'
    for(size_t i=0;i<t;i++){
        s_[i]=c;
    }
    s_[tam_]='\0';
}

//constructor de clase cadena (recibe un parametro (const char *) y devuelve una cadena)
Cadena::Cadena(const char *s):tam_(strlen(s)){

s_ = new char[tam_ + 1];
strcpy(s_,s);
}

//constructor de copia (recibe una referencia constante de una cadena y la copia en otra)
Cadena::Cadena(const Cadena &cadena):tam_(cadena.tam_){

s_ = new char[tam_ +1];
strcpy(s_, cadena.s_);
}

//contructor de movimiento (recibe un parametro de tipo cadena por rvalor y lo copia en otra cadena, acomodando la cadena referenciada para ser borrada)
Cadena::Cadena(Cadena &&cadena): s_(cadena.s_), tam_(cadena.tam_){

    cadena.s_ = nullptr;    //vacio para dejarlo perfecto para ser eliminado
    cadena.tam_ = 0;        // tamanno a 0 para lo mismo
}

//constructor de substr (nos permite crear la cadena a partir de la diferencia (substr))

Cadena::Cadena(const Cadena &cadena, size_t emp, size_t t):tam_(t){

    if(emp > cadena.tam_ -1){                                           //si emp es mayor que el tamanno de la cadena (menos \0, lanza excepcion)
        throw std::out_of_range("En substr(): Indice fuera de rango");
    }
    s_ = new char[tam_ + 1];       //si no, entonces creamos una nueva cadena 
    size_t i, j = emp;          //j valdrá emp y nos servirá para inicializar la nueva cadena

    for(i = 0; i < tam_; i++){  //desde 0 hasta tam - 1, vamos asignando a s_ la cadena[0...emp]
        s_[i] = cadena[j];
        j++;
    }
    s_[tam_] = '\0';            //el ultimo valor de s_ será \0
}

//Destructor de clase cadena (libera memoria)
Cadena::~Cadena(){          
    delete [] s_;
}

//Metodo observador del tamanno de una cadena (const al ser observador)
size_t Cadena::length() const{                //devuelve tamanno de la cadena
    return tam_;
}

//Metodo observador de la cadena
const char *Cadena::c_str()const{             //devuelve la cadena
    return s_;
}

//Operador de asignacion que recibe una referencia constante a cadena(llamará al constructor de copia)
Cadena &Cadena::operator = (const Cadena &cadena){
    if(*this != cadena){                    //si las cadenas son iguales, pues devolvemos *this
        tam_ = cadena.tam_;                 //asignamos el tamanno
        delete[] s_;                        //free() la cadena anterior
        s_ = new char[tam_ + 1];            //creamos la cadena con el tamanno de la cadena
        strcpy(s_, cadena.s_);              //copiamos la cadena en s_
    }
    return *this;
    
}

//Operador de asignacion que recibe un puntero constante a una cadena (llamará al constructor de copia)
Cadena &Cadena::operator = (const char *cadena){
    
    tam_ = strlen(cadena);        //tamanno de la cadena implicita sera el tamanno de la cadena con la que se llama al operador
    delete[] s_;                  //libero memoria de la cadena implicita
    s_ = new char[tam_ + 1];      //declaro el nuevo tamanno de la cadena implicita
    strcpy(s_,cadena);            //la copio en la cadena implicita
    return *this;                       
}

//Operador de asignacion que recibe un rvalor (llamará al constructor de movimiento)
Cadena &Cadena::operator = (Cadena &&cadena){
    s_ = cadena.s_;             //copio ambos atributos en la cadena implicita
    tam_ = cadena.tam_;
    cadena.s_ = nullptr;        //preparamos la cadena para ser borrada por el destructor (puntero vacio + tamanno = 0)
    cadena.tam_ = 0;
    return *this;               
}

//Operador += (recibe una referencia constante a una cadena) y devuelve la cadena implicita concatenada
Cadena &Cadena::operator += (const Cadena &cadena){
    Cadena tmp{*this};                      //Cadena temporal = cadena implicita
    tam_ += cadena.tam_;                    //suma el total de los tamannos de ambas cadenas
    delete[] s_;                            //borro la cadena
    s_ = new char[tam_ + 1];                //crea la cadena con el tamanno de ambas
    strcpy(s_,tmp.s_);                      //copia la cadena temporal en s_   
    strcat(s_,cadena.s_);                   //concatena s_ con el valor de cadena.s_
    return *this;
}

//Operador + (recibe dos referencias constantes a una cadena), las suma y devuelve otra cadena con la concatenacion
Cadena operator + (const Cadena &cadena1, const Cadena &cadena2){
    Cadena tmp{cadena1};                //asignamos a una cadena temporal la cadena1
    tmp += cadena2;                     //operador += que nos devolverá las cadenas ya concatenadas
    return tmp;
}

//operador == (devuelve true si son iguales)
bool operator == (const Cadena &cadena1, const Cadena &cadena2){
    return strcmp(cadena1.c_str(),cadena2.c_str()) == 0;
    
}

//operador != (devuelve true si son diferentes)
bool operator != (const Cadena &cadena1, const Cadena &cadena2){
    return !(cadena1 == cadena2);
}

//operador < (devuelve true si strcmp es menor que 0
bool operator < (const Cadena &cadena1, const Cadena &cadena2){
    return strcmp(cadena1.c_str(), cadena2.c_str())  < 0;
}

//operador > (cambiamos de posicion la cadena para aprovechar el operador <)
bool operator > (const Cadena &cadena1, const Cadena &cadena2){
    return (cadena2 < cadena1);
}

//operador <= (si son iguales o si es menor)
bool operator <= (const Cadena &cadena1, const Cadena &cadena2){
    return (cadena1 == cadena2 || cadena1 < cadena2);
}

//operador >= (si son iguales o si es mayor)
bool operator >= (const Cadena &cadena1, const Cadena &cadena2){
    return (cadena1 == cadena2 || cadena1 > cadena2);
}

//operador de indice (este no comprueba si sale del rango)
char &Cadena::operator[] (size_t a){
    return s_[a];                      //devuelve el caracter de la posicion
}

//operador de indice version constante
const char &Cadena::operator[] (size_t a) const{
    return s_[a];                      //version constante
}

//funcion que devuelve el caracter concreto en una cadena (si comprueba si sale de rango)
char &Cadena::at (size_t a){
    if(a < tam_){
        return s_[a];          //si a es menor que el tamanno de la cadena, devuelvo el caracter apuntado por el indice
    }else{
        throw std::out_of_range("En Cadena::at(): Indice fuera de rango de la cadena.");
    }
}

//version constante
const char &Cadena::at (size_t a) const{   //version constante
    if(a < tam_){
        return s_[a];
    }else{
        throw std::out_of_range("En Cadena::at() const: Indice fuera de rango de la cadena.");
    }
}

//funcion substr (recibe dos tamannos)
Cadena Cadena::substr(size_t a, size_t b) const{
    
    size_t l = a + b;                           //creamos una variable para contener el tamanno total (hay que tener en cuenta que este no puede ser mayor que el tamanno de la cadena)
    //si l es mayor o igual que el tamanno de la cadena, o a mayor que el tamanno de la cadena o que l sea menor que a, lanza excepcion
    if(length() < l || length() <= a || a >= l){ 
        throw std::out_of_range("En Cadena::substr(): indices de la cadena fuera de rango.");
    }
    
    return Cadena(*this, a, b);                 
}

std::ostream &operator << (std::ostream &os, const Cadena &cadena){

    os << cadena.c_str();               //cadena.c_str() devuelve el valor de la cadena a os
    return os;
}

/*
 std::istream &operator >> (std::istream &is,Cadena &cadena){

     int i = 0;
     char *cad = new char[32];
     char c;

     while(isspace(is.get()) != 0 && i < 32){       //isspace devolverá 0 si is.get() lee un espacio en blanco
         i++;                                       //i tendra el numero de caracteres distintos de espacio en blanco
     }

    is.unget();
    i = 0;

    while(!isspace(is.peek()) && i < 32 && is.good()){
        c = is.get();
        cad[i++] = c;
    }
    cad[i] = '\0';

    cadena = Cadena(cad);
    delete[] cad;
    return is;
 }
*/
 std::istream &operator >> (std::istream &is,Cadena &cadena){

     int i = 0;
     char *cad = new char[32];
     char c;

    //desde i = 0 hasta que el caracter de la cadena no sea 0 y que i sea menor que 32
    for(i = 0;isspace(is.get()) != 0 && i < 32; i++);       //funcion isspace devuelve 0 si el caracter no es un espacio

    is.unget(); //desleemos el ultimo caracter (\0)
    i = 0;

    //desde i = 0 hasta que 
    for(i = 0; !isspace(is.peek()) && i < 32 && is.good();i++){ //mientras que el siguente caracter no sea espacio 
        c = is.get();
        cad[i] = c;
    }
    cad[i] = '\0';

    cadena = Cadena(cad);
    delete[] cad;
    return is;
 }