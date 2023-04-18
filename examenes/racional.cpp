//1

#include <iostream>

using namespace std;

class Racional {
	public:
		Racional(unsigned int a = 0, unsigned int b = 1);
		Racional inv();
		//Operator +,-,* y /
		friend Racional operator + (const Racional &r1, const Racional &r2);
		friend Racional operator - (const Racional &r1, const Racional &r2);
		friend Racional operator * (const Racional &r1, const Racional &r2);
		friend Racional operator / (const Racional &r1, const Racional &r2);

		//Operator +,- signo
		friend Racional operator + (const Racional &r1);
		friend Racional operator - (const Racional &r1);

		//Operator ==, !=, <, <=, > y >=
		friend bool operator == (const Racional &r1, const Racional &r2);
		friend bool operator != (const Racional &r1, const Racional &r2);
		friend bool operator < (const Racional &r1, const Racional &r2);
		friend bool operator <= (const Racional &r1, const Racional &r2);
		friend bool operator > (const Racional &r1, const Racional &r2);
		friend bool operator >= (const Racional &r1, const Racional &r2);
		

	private:
		unsigned int a_;
		unsigned int b_;
		static int mcd (unsigned int a, unsigned int b) {
			return b ? mcd(b, a % b): a; 
		}
		static int mcm (unsigned int a, unsigned int b) {
			return a / mcd (a, b) * b;
		}
};

	//Implementaciones de los metodos.
	//Constructor
	Racional::Racional (unsigned int a = 0, unsigned int b = 1): a_(a), b_(b) {
		
		if (!b)
			throw std::invalid_argument("ERROR: TA COLAO");

		if(b < 0) {
			a_ *= -1;
			b_ *= -1;
		}
		
		int aux = mcd (a, b);
		
		if (aux != a && aux != b) {
			a_ /= aux;
			b_ /= aux;
		}
	}

	//Inv()
	Racional::Racional inv(){
	
		std::swap(a_,b_);
		return *this;
	}
	
	//Aritmeticos
	
	inline Racional operator +(const Racional &r) { return r; }
	inline Racional operator -(const Racional &r) { return r * -1; }
	inline Racional operator +(const Racional &r1, const Racional &r2) {
		return Racional (((r1.a_ * r2.b_) + (r1.b_ * r2.a_)), std::mcm(r1.a_, r2.b_));
	}
	
	inline Racional operator -(const Racional &r1, const Racional &r2) {
		return Racional (((r1.a_ * r2.b_) - (r1.b_ * r2.a_)), std::mcm (r1.a_, r2.b_));
	}

	inline Racional operator *(const Racional &r1, const Racional &r2) {
		return Racional ((r1.a_ * r2.a_),(r1.b_ * r2.b_));
	}

	inline Racional operator /(const Racional &r1, const Racional &r2) {
		return Racional ((r1.a_ * r2.b_),(r1_b * r2.a_));
	}

	inline bool operator == (const Racional &r1, const Racional &r2) {
		return (r1.a_ == r2.a_ && r1.b_ == r2.b_ ? true : false; );
	}

	inline bool operator > (const Racional &r1, const Racional &r2) {
		if (r1.b_ == r2.b_) {
			if (r1.a_ > r2.b_)
				return true;
			else
				return false;
		}else {
			if ((r1.a_ * r2.b_) - (r1.b_ * r2.a_) > 0)
				return true;
			else
				return false;
		}
	}
		
	inline bool operator < (const Racional &r1, const Racional &r2) { return r2 > r1; }
	
	inline bool operator >= (const Racional &r1, const Racional &r2) {
		return (r1 > r2 || r1 == r2);
	}
	
	inline bool operator <= (const Racional &r1, const Racional &r2) {
		return (r2 > r1 || r1 == r2);	
	}

	inline bool operator != (const Racional &r1, const Racional &r2) { return !(r1 == r2); }

//2

	class Doble {

		private:
			double d_;
	}

	//En principio, se puede dejar asi la clase puesto que cuenta con constructor por omision, copia, movimiento, operador de asignación, movimiento y destructor por defecto.
	//Nos sirve ya que nuestra clase posee un solo atributo de tipo double, un tipo simple, el cual no requiere ningún comportamiento especial (acceso a memoria).
	
//3

	class Fecha {
		int dia_, mes_, anno_;

		public:
			//
			long operator - (const Fecha &f1);
			
	}
	//Mejor la deficion dentro de la clase puesto que no tenemos forma de acceder a las variables privadas
	
	long operator - (const Fecha &f1, const Fecha &f2);

	long Fecha::operator - (const Fecha &f1) {
		return (dia_ - f.dia_ + 30 * (mes_ - f.mes_) + 365 * (anno_ - f.anno_));
	}

	//La sobrecarga del operador + suponiendo que vayamos a sumar fechas si sería conveniente ya que debemos de controlar que la suma de las fechas se realize entre los rangos correctos de las fechas
	

