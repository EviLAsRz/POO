#include <iostream>

using namespace std;

class Binario {
	
	public:
		Binario (size_t n_ = 1);
		Binario(const Binario &b);
		Binario &operator = (const Binario &b);
		Binario &operator = (Binario &&b);
		unsigned operator[] (const unsigned index);
		Binario &operator ~ ();
		~Binario();

	private:
		static const size_t bits_elto = CHAR_BIT * sizeof(unsigned);
		size_t n;
		size_t m;
		unsigned *bits;
};

	// #cpp
	
	Binario::Binario (size_t n_ = 1):
		n(n_), m(n_ + bits_elto - 1), bits (new unsigned[n_]) {
		
		for (int i = 0; i < n_; ++i)
			bits[i] = 0;
	}

	Binario::Binario (Const Binario &b):
		n(b.n), m(b.m) {
		
		bits = new unsigned[b.n];

		for (int i = 0; i < n; ++i)
			bits[i] = b.bits[i];
	}

	Binario:: Binario & operator = (const Binario &b):
		n(b.n), m(b.m){
		
		if (this != &b) {
			this->n = b.n;
			this->m = b.m;
			delete [] this->bits;
			this->bits = new unsigned [n];

			for (int i = 0; i < n; ++1)
				this->bits[i] = b.bits[i];

		}
		return *this;
	}

	Binario::Binario &operator (Binario &&b):
		n(b.n), m(b.m), bits(b.bits){
		b.n = 0;
		b.m = 0;
		b.bits = nullptr;
	}

	Binario::unsigned operator [](const unsigned index) {
		
		if (index < 0 || index > n)
			throw std::invalid_argument("ERROR: OVERFLOW DEL VECTOR");
		
		return bits [index];
	}

	Binario::Binario operator ~ () {
		
		Binario aux(n);
		for (int i = 0; i < n; ++i)
			aux.bits[i] = 1;
		
		return aux;
	}

	Binario::~Binario () { delete [] bits; }
