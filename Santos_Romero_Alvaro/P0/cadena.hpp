#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iterator>

class Cadena{
    
    public:

    //Constructores
    explicit Cadena(size_t t = 0, char c = ' ');        //constructor de cadena declarado explicito para que no realice conversiones de forma implicita)
    Cadena(const Cadena& cadena, size_t i, size_t t);   //constructor de substr (parametros: puntero a cadena, dos size_t) devuelve el substr de una cadena
    Cadena(const Cadena &cadena);                       //constructor de copia
    Cadena(Cadena &&cadena);                            //constructor de movimiento   (referencia no constante ya que se modifica la cadena)
    Cadena(const char *s);                              //constructor de copia char *s
    ~Cadena();                                          //destructor 

    //funciones de clase
    size_t length() const;                            //Devuelve el tamanno

    //operadores de asignacion (siempre dentro de la clase)
    Cadena &operator = (const Cadena &cadena);  //cadena implicita = cadena
    Cadena &operator = (const char *cadena);    //cadena implicita = cadena version const char*
    Cadena &operator = (Cadena &&cadena); //Asignacion de movimiento
    //resto operadores clase
    Cadena &operator += (const Cadena &cadena); //cadena implicita += cadena
    
    //operadores de indice
    char &operator[] (size_t a);                //operador de indice estandar(no comprueba si el indice es valido)
    const char &operator[] (size_t a) const;    //version constante
    char &at(size_t a);                        //operador de indice que comprueba si el indice es valido
    const char &at(size_t a) const;            //version constante
    Cadena substr(size_t a, size_t b) const;  //devuelve la cadena comprendida entre a y end
    const char* c_str() const;                      //metodo conversor de cadena a char*

    //Iteradores

    typedef char *iterator;
    typedef const char *const_iterator;
    typedef std::reverse_iterator <iterator> reverse_iterator;
    typedef std::reverse_iterator <const_iterator> const_reverse_iterator;

    //Funciones de iteradores

    iterator begin(){return s_;}                                                        //begin
    const_iterator begin() const{return cbegin();}                                      //begin constante
    const_iterator cbegin() const{return s_;}                                           //cbegin constante
    reverse_iterator rbegin(){return reverse_iterator(end());}                          //rbegin
    const_reverse_iterator rbegin() const{return crbegin();}                            //rbegin constante
    const_reverse_iterator crbegin() const{return const_reverse_iterator(end());}       //crbegin constante

    iterator end(){return s_ + tam_;}                                                   //end
    const_iterator end() const{return cend();}                                          //end constante
    const_iterator cend() const{return s_ + tam_;}                                      //cend constante
    reverse_iterator rend(){return reverse_iterator(begin());}                          //rend
    const_reverse_iterator rend() const{return crend();}                                //rend constante
    const_reverse_iterator crend() const{return const_reverse_iterator(begin());}       //crend constante

    private:

        //atributos de la clase
        char *s_;
        size_t tam_;
};

//Operadores aritmeticos y logicos

Cadena operator + (const Cadena &cadena1, const Cadena &cadena2);   //cadena1 + cadena2
bool  operator == (const Cadena &cadena1, const Cadena &cadena2);   //cadena1 == cadena2
bool  operator != (const Cadena &cadena1, const Cadena &cadena2);   //cadena1 != cadena2
bool  operator < (const Cadena &cadena1, const Cadena &cadena2);    //cadena1 < cadena2
bool  operator > (const Cadena &cadena1, const Cadena &cadena2);    //cadena1 > cadena2
bool  operator <= (const Cadena &cadena1, const Cadena &cadena2);   //cadena1 <= cadena2
bool  operator >= (const Cadena &cadena1, const Cadena &cadena2);   //cadena1 >= cadena2

std::ostream &operator << (std::ostream &os, const Cadena &cadena);
std::istream &operator >> (std::istream &is, Cadena &cadena);
#endif //CADENA_HPP_

