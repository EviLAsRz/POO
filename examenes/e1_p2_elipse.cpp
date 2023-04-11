#include <iostream>

class FiguraPlana {

	public:
		FiguraPlana(double rx, double ry): rx_(rx), ry_(ry) {}
		double radio_x const () { return rx_; }
		double radio_y const () { return ry_; }
		void escala (const double &fx, const double &fy) {
			rx_ *= fx;
			ry_ *= fy;
		}
		
		virtual void dibuja () = 0; //metodo virtual
	private:
		double rx_, ry_;
};

class Circunferencia : public Elipse {
	
	public:
		Cincunferencia (double r): Elipse(r, r){}
		double radio() const { return this.radio_x(); }

		void dibuja () override{ std::cout << "Dibujando circunferencia..." << std::endl; }
	private:

};

class Elipse : public FiguraPlana {
	public:
		Elipse(double rx, double ry): FiguraPlana(rx, ry) {}
		void dibuja () override{ std::cout << "Dibujando elipse..." << std::endl; }


}
