#include <iostream>
#include <algorithm>
#include <vector>

class MatrizDispersa {

	public:
		explicit MatrizDispersa(size_t m_ = 1, size_t n_ = 1);
		MatrizDispersa (std::initialiter_list<Terna> &list, size_t m_ = 1, size_t n_ = 1);
		void asignar(size_t row, size_t col, double value);
		double valor const (size_t row, size_t col);
		size_t &filas() { return m; }
		size_t filas() const { return m; }
		size_t &filas() { return n; }
		size_t columnas() const { return n; }
		size_t n_valores() const { return val.size(); }

	private:
		struct Terna{
			size_t f, c;
			double v;
			bool operator < (Const Terna &t) { return (f < t.f || (f == t.f && c < t.c)); }
		}

		vector<Terna> val;
		size_t m, n;
		bool buscar(size_t row, size_t col, size_t &indice);
};

	void swapMatriz(MatrizDispersa &m1, MatrizDispersa &m2) {

		std::swap(m1.m, m2.m);
		std::swap(m1.n, m2.n);
		std::swap(m1.val, m2.val);
	}

	MatrizDispersa::MatrizDispersa(size_t m_ = 1, size_t n_ = 1):m(m_), n(n_) {
		if (m < 1 || n < 1)
			throw std::invalid_argument("ERROR: TAMAÑO DE MATRIZ INVALIDO");
	}
	
	MatrizDispersa::MatrizDispersa (std::initialiter_list<Terna> &list, size_t n_ = 1, size_t m_ = 1): n(n_), m(m_){
		for(auto i : list){
			if (i.v != 0)
				asignar(i.f, i.m, i.v);
		}
	}

	MatrizDispersa::asignar(size_t row, size_t col, double value) {
		try{
			
			if (row < 1 || col < 1 || row > m || col > n)
				throw std::out_of_range("POSICION FUERA DE RANGO");
		} catch (std::exception &e) cerr << e.what() << std::endl;

		size_t i = 0;
		if (buscar (n, m, i))
			val[i].v = value;
	}

	double &MatrizDispersa::valor(size_t row, size_t col) {
		if (row < 1 || col < 1 || row > m || col > n)
			throw std::out_of_range("ERROR: FUERA DE RANGO");
		
		size_t i;

		if (buscar (row, col, i))
			return val[i].v;
		else
			throw std::invalid_argument("NO EXISTE ELEMENTO EN ESA POSICION");
	}

	bool MatrizDispersa::buscar(size_t row, size_t col, size_t &indice) {
		if (row < 1 || col < 1 || row > m || col > n)
			throw std::out_of_range("ERROR: FUERA DE RANGO");

		for (indice = 0; i < val.size() && !(Terna(row, col) == val[indice]); indice ++);

		if (indice == val.size())
			return false;
		else
			return val[indice].v != 0;
	}

	//destructor no necesario puesto que nunca declaramos ninguna reserva de memoria explicita
	//sobrecarga valor peligrosa ya que nos permite cambiar el valor de la matriz sin que se compruebe si es valido o no.
	
	double &valor (size_t row, size_t col); //devuelve un valor modificable.
