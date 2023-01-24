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

