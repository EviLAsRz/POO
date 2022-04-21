#include <iostream>
#include "fecha.hpp"
#include <stdexcept>
#include <ctime>

Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anno_(a){
    time_t now;
    struct tm nowLocal;                 //Utilizado para obtener la fecha del sistema
    now = time(NULL);
    nowLocal = *localtime(&now);
    //comprueba que si alguno de los parametros son 0, proporciona la fecha del sistema
    if(dia_ == 0){
        dia_ = nowLocal.tm_mday;
        }
    if(mes_ == 0){
        mes_ = nowLocal.tm_mon+1;           
    }
    if(anno_ == 0){
        anno_ = nowLocal.tm_year + 1900;
    }
    actualizarFecha();
}

Fecha::Fecha(const char *cadena){           //Transforma cadena a formato normal de fecha

if(sscanf(cadena,"%d/%d/%d",&dia_,&mes_,&anno_) != 3){  //funcion interesante que permite leer datos desde una cadena y almacenarlos con un formato determinado
    throw Invalida("Formato invalido");
}else{
    time_t now;
    struct tm nowLocal;
    now = time(NULL);
    nowLocal = *localtime(&now);
    //comprueba que si alguno de los parametros son 0, proporciona la fecha del sistema
    if(dia_ == 0){
        dia_ = nowLocal.tm_mday;
        }
    if(mes_ == 0){
        mes_ = nowLocal.tm_mon+1;
    }
    if(anno_ == 0){
        anno_ = nowLocal.tm_year + 1900;
    }
}
    actualizarFecha();              //llamada a funcion que puede lanzar excepcion
}

int Fecha::diasMes() const{       //funcion que devuelve los dias maximos de cada mes
    try{
    if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12){
        return 31;
    }
    if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 1){
        return 30;
    }
    if (mes_ ==  2 && anno_% 4 == 0 &&(anno_ % 400 == 0 || anno_ % 100 != 0)){       //annos bisiestos, febrero tiene 29 dias
        return 29;
    }else return 28;

    throw Invalida("Fecha invalida");                           //lanza excepcion el mes no está comprendido entre 1 y 12
    } 
    catch (Fecha::Invalida e){                                  //recoge excepcion y la imprime en la salida de errores
        std::cerr<<e.por_que()<<std::endl;
    }
    return 0;
}

const char* Fecha::cadena() const{
    setlocale(LC_ALL,"es_ES.UTF-8");    //seleccionamos como local España, para poder referenciar las fechas en español
    static char* buffer = new char[40]; //creamos un "contenedor" para albergar la fecha completa

    tm f = {0};                         //establecemos la fecha del sistema
    f.tm_mday = dia_;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_ - 1900;

    mktime(&f);                         //devuelve el valor de la hora local del sistema
    strftime(buffer, 40, "%A %d de %B de %Y", &f);   //Formato: "Lunes 23 de Enero de 2020"
                                                    
    return buffer;
}

Fecha::Invalida::Invalida(const char *s): str{s}{
}

const char *Fecha::Invalida::por_que() const{
    return str;
}

void Fecha::actualizarFecha(){          //comprobaciones de fecha (lanzamiento de excepciones)

    if(dia_ > diasMes() || dia_ < 1){   //lo comparamos con la funcion diasMes() que contiene los dias de cada mes segun su numero
        throw Invalida("Dia invalido");
    }else if(mes_ > 12 || mes_ < 1){
        throw Invalida("Mes invalido");
    }else if(anno_ > AnnoMaximo || anno_ < AnnoMinimo){
        throw Invalida("Anno invalido");
    }
}

//metodos observadores
int Fecha::dia() const{
    return dia_;
}

int Fecha::mes() const{
    return mes_;
}

int Fecha::anno() const{
    return anno_;
}

Fecha Fecha::operator++(int){   //postincremento (fecha++)
    Fecha fecha = *this;
    *this +=1;
    return fecha;               //devolvemos la copia modificada (no devolvemos el objeto implicito)
}

Fecha &Fecha::operator++(){     //preincremento (++fecha)
    
    *this += 1;
    return *this;               //devolvemos el objeto implicito modificado (en preincremento si se modifica)
}

Fecha Fecha::operator--(int){   //postincremento (fecha--)
    Fecha fecha = *this;
    *this += -1;
    return fecha;
}

Fecha &Fecha::operator--(){     //preincremento (--fecha)
    *this += -1;
    return *this;
}

Fecha &Fecha::operator += (int d){ //operador +=, fecha+=d;
    
    if(d!=0){                   //hay que comprobar que si el entero no es 0, entonces generamos la fecha a partir de la fecha del sistema,sumando el entero (que sera dias)
       tm f = {0};
    f.tm_mday = dia_ + d;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_ - 1900; 

    mktime(&f);

    anno_ = f.tm_year + 1900;
    mes_ = f.tm_mon + 1;
    dia_ = f.tm_mday;
    actualizarFecha();          //llamada a la funcion que comprueba si la fecha es correcta

    }
    return *this;
}

//a partir del operador +=, podemos crear facilmente algunos de ellos
Fecha &Fecha::operator -= (int d){ //operador -=, fecha-=d;
    *this += -d;            //lo indicamos así para reutilizar el operador += y no tener que escribir codigo redundante
    return *this;
}

Fecha Fecha::operator +(int d) const{
    Fecha fecha = *this;
    fecha += d;
    return fecha;
}

Fecha Fecha::operator -(int d) const{
    Fecha fecha = *this;
    fecha += -d;            //lo mismo que con operador -=
    return fecha;
}

bool operator == (const Fecha &fecha1, const Fecha &fecha2){    //operador ==, fecha1 == fecha2;
    return(fecha1.anno() == fecha2.anno() && fecha1.mes() == fecha2.mes() && fecha1.dia() == fecha2.dia());
}

bool operator != (const Fecha &fecha1, const Fecha &fecha2){    //operador !=, fecha1 != fecha2;
    return !(fecha1 == fecha2);         //devolverá lo contrario que el operador ==, si uno es verdadero, el otro será falso por deficion
}

bool operator < (const Fecha &fecha1, const Fecha &fecha2){     //operador <, fecha1 < fecha2;
    return (fecha2 > fecha1);           //cambiamos de posicion las fechas para reutilizar el operador >
}

bool operator > (const Fecha &fecha1, const Fecha &fecha2){     //operador >, fecha1 >f echa2;
    if(fecha1.anno() > fecha2.anno()){
        return 1;
    }else if (fecha1.anno() == fecha2.anno() && fecha1.mes() > fecha2.mes()){
        return 1;
    }else if(fecha1.anno() == fecha2.anno() && fecha1.mes() == fecha2.mes() && fecha1.dia() > fecha2.dia()){
        return 1;
    }else return 0;
}

bool operator <= (const Fecha &fecha1, const Fecha &fecha2){    //operador <=, fecha1 <= fecha2;
    return (fecha1 < fecha2 || fecha1 == fecha2);
}

bool operator >= (const Fecha &fecha1, const Fecha &fecha2){    //operador >=, fecha1 >= fecha2;
    return (fecha1 > fecha2 || fecha1 == fecha2);
}

std::ostream &operator << (std::ostream &os, const Fecha &fecha){
    
    os << fecha.cadena();                                       
    return os;  
}

std::istream &operator >> (std::istream &is, Fecha &fecha){
    
    char *cad = new char[11];
    is.getline(cad,11);         //11 bytes por el formato ("dd/mm/aaaa\0")
    
    try{
        fecha = cad;     //asignamos a fecha la cadena
    }catch (Fecha::Invalida e)  //recogida de excepciones
    {
        is.setstate(std::ios_base::failbit);    //indicamos con el bit de operacion de entrada activo que ha fallado la lectura de los caracteres
        throw e;                                // lazamos excepcion
        delete[] cad;                           //liberamos la memoria
    }
        delete[] cad;                           //liberamos la memoria si no falla
    return is;                                  //devolvemos el flujo
}