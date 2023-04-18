#include <iostream>

class Complejo {

	public:
		Complejo(double r_ = 0, double i_ = 0);
		double real() const{ return r; }
		double &real() { return r; }
		double img() const{ return i; }
		double &img() { return i; }
		Complejo operator - ();

	private:
		double r;
		double i;
};

	Complejo operator *(const Complejo &c1, const Complejo &c2);
	Complejo operator +(const Complejo &c1, const Complejo &c2);
	bool operator ==(const Complejo &c1, const Complejo &c2);
	bool operator !=(const Complejo &c1, const Complejo &c2);

	//cpp
	
	Complejo::Complejo(double r_ = 0, double i_ = 0):r(r_), i(i_) {};
	
	Complejo operator *(const Complejo &c1, const Complejo &c2) {
		
		return Complejo(((c1.real() * c2.real()) - (c1.img() * c2.img())), ((c1.real() * c2.img()) + (c1.img() * c2.real())));
	}

	Complejo operator +(const Complejo &c1, const Complejo &c2) {
		return Complejo ((c1.real() + c2.real()), (c1.img() + c2.img()));
	}
	
	bool operator == (const Complejo &c1, const Complejo &c2) {
		return (c1.real() == c2.real() && c1.img() == c2.img());
	}

	bool operator !=(const Complejo &c1, const Complejo &c2) {return !(c1 == c2); }

	Complejo::Complejo operator - () { return Complejo (-r, -i); }

