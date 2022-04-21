#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>
#include <cstring>

class Fecha{
    public:
        //Constantes
        static const int AnnoMinimo{1902};                  //si no son estaticos, da problemas con el operador de asigmacion (lo borra por defecto)
        static const int AnnoMaximo{2037};

        //Constructores
        explicit Fecha(int d = 0,int m = 0,int a = 0);      //constructor fecha de 3 parametros enteros
        Fecha(const char *cadena);                          //Constructor de conversion de fecha a cadena
        //Clase invalida para las excepciones
        class Invalida{             
        
            public:
               Invalida(const char *s);     //constructor invalida de 1 parametro tipo cadena
               const char * por_que() const;        //metodo observador por_que()    

            private:
                const char *str;            // parametro de tipo cadena
        };

        //observadores

        int dia() const noexcept;            
        int mes() const noexcept;
        int anno() const noexcept;

        //Operadores aritmeticos (tipo fecha implicita)
        Fecha operator ++ (int);                //postincremento
        Fecha operator -- (int);                //postincremento
        Fecha operator +(int d) const;
        Fecha operator -(int d) const;
        Fecha &operator += (int d);             //fecha +=entero
        Fecha &operator -= (int d);             //fecha -=entero
        Fecha &operator ++();                   //preincremento
        Fecha &operator --();                   //preincremento

        const char *cadena() const;
    private:
        
        bool test() const;                  //funcion booleana para comprobar si la fecha no cumple las normativas
        int diasMes() const;                //Funcion que devuelve los dias del mes dependiendo de cual sea.
        void actualizarFecha();             //Reajusta las fechas a la hora de realizar operaciones aritmeticas
        int dia_,mes_,anno_;
};

    //operadores logicos (tipo fecha explicita)
    bool operator == (const Fecha &fecha1, const Fecha &fecha2);    //if(fecha1 == fecha2) 
    bool operator != (const Fecha &fecha1, const Fecha &fecha2);    //if(fecha1 != fecha2)
    bool operator < (const Fecha &fecha1, const Fecha &fecha2);     //if(fecha1 < fecha2)
    bool operator > (const Fecha &fecha1, const Fecha &fecha2);     //if(fecha1 > fecha2)
    bool operator <= (const Fecha &fecha1, const Fecha &fecha2);    //if(fecha1 <= fecha2)
    bool operator >= (const Fecha &fecha1, const Fecha &fecha2);    //if(fecha1 >= fecha2)
    
    //entrada-salida

    std::ostream &operator << (std::ostream &os, const Fecha &fecha);
    std::istream &operator >> (std::istream &is, Fecha &fecha);
#endif //FECHA_HPP_