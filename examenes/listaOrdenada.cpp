#include <iostream>
#include <algorithm>

class ListaOrdenada : public List<double> {

	public:
		typedef list<double> const_iterator;
		ListaOrdenada();
		void insertar(double e);
		const_iterator buscar(double e) const;
		const_iterator begin() const;
		const_iterator end() const;

	private:
		//
};
	

	//ListaOrdenada como especializacion ya que una listaOrdenada va a funcionar minimo igual que una lista estandar.
	

ListaOrdenada::const_iterator ListaOrdenada::begin() const { return cbegin(); }
ListaOrdenada::const_iterator ListaOrdenada::end() const { return cend(); }

ListaOrdenada::insertar(double e) {
	
	auto it = list<double>.begin();

	while (it != list<double>.end() && e > *it)
		it ++;

	insert(it, e);
}

ListaOrdenada::const_iterator ListaOrdenada::buscar(double e) const{

	const_iterator it = cbegin();

	for (auto i = 0; i != cend(); i++){
		if (e == i)
			it = i;
	}
	return it;
}

size_t ListaOrdenada::contar(double e) const {
	
	return std::count_if(begin(), end(), [=](double val) {return val == e; });

}
