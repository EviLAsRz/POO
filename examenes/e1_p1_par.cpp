#include <iostream>

template <class T1, class T2>

class Par{

	public:
		Par(): prime(T1()), segun(T2()) {}
		Par(const T1 &p, const T2 &s) : prime(p), segun(s) {}
		T1 primero() const {return prime; }
		T1 &primero() {return prime; }
		T2 segundo() const {return segun; }
		T2 &segundo() {return segun; }

	protected:
		T1 prime;
		T2 segun;

};

std::ostream operator << (std::ostream &os, const Par<P1,P2>& par){

	os << "Primero" << par.primero() << std::endl;
	os << "Segundo" << par.segundo() << std::endl;
	return os;
}

Class Racional : public Par<int, int> {
	
	public:
		Racional(int num, int dem): Par(num, dem);
};

Racional operator + (Const Racional &r1, const Racional &r2) {

	return Racional(r1.primero() * r2.segundo() + r2.primero() * r1.segundo(), r1.segundo() * r2.segundo());

}

Class Complejo : public Par <double, double> {
	
	public:
		Complejo(Double real, double img): Par(real, img){}
		Complejo operator += (const Complejo &c);
};

Complejo::Complejo operator +=(const Complejo &c){
	this->primero() += c.primero();
	this->segundo() += c.segundo();
	return Complejo (this->primero(), this->segundo());
}

