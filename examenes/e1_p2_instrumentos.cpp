#include <iostream>


class Instrumento {
//
 	public:
		virtual string tipo () const { return "instrumento."; }
}

class Cuerda : public Instrumento {

	public:
		Cuerda (std::string n): Instrumento(n){}

		std::string tipo () const { return "cuerda"; }

}

//al ser tipo() virtual, si lo llamamos desde un objeto cuerda nos devolvera cuerda

//codigo ejemplo

int main() {

	Instrumento *pi = new Cuerda("Violin");
	pi->tocar(); // nombre(violin) tipo(cuerda)
	//si no estuviera sobrecargado virtualmente, tipo devolveria instrumento
	delete pi;
}

// ejercicio 2020

//Podemos mejorar el programa si ponemos clase como virtual y las implementamos en cada clase de instrumento.

