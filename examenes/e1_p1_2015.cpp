#include <iostream>

using namespace std;

class Vector {
	
	public:
		Vector (size_t n_, double datos_ = 0);
		Vector (std::initialiter_list<double> &list);
		Vector &(const Vector &v);
		Vector &(Vector &&v);

		double &at(int posicion);
		~Vector();
	private:
		size_t n;
		double * datos;

};

	Vector::Vector (size_t n_, double datos_ = 0):n(n_) {
		if (n < 1)
			throw std::invalid_argument("ERROR: VECTOR INVALIDO");

		datos = new double [n];
		for(int i = 0; i < n; ++i)
			datos[i] = datos_;
	}

	Vector::Vector (std::initialiter_list<double> &list): n(list.size()){
		datos = new double [n];
		auto it = list.begin();
		for(size_t i = 0; i != list.end(); i++, it++)
			datos[i] = *it; 
	}

	Vector::~Vector(){ delete [] datos; }

	Vector::Vector(const Vector &v): n(v.n){
		
		datos = new double [n];
		for(int i = 0; i < n; i++)
			datos[i] = v.datos[i];
	}

	Vector::Vector(Vector &&v): n(v.n), datos(v.datos) {
		v.n = 0;
		v.datos = nullptr;
	}

	Vector:: double &at(int posicion){
		if (posicion > n || posicion <= 0 )
			throw std::out_of_range("ERROR: POSICION FUERA DEL RANGO DEL VECTOR");
		
		return datos[posicion];			
	}

	//Ej 2
	

	class Doble {
		
		public:
			Doble(double d): d_(d) {};
			Operator double () { return d_; }
			Doble &operator = (Const Doble &d) {
				d_ = d.d_;
				return *this;
			}

		private:
			double d_;

	}
