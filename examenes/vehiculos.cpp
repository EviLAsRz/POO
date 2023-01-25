#include <iostream>

class Vehiculo {
	
	public:
		Vehiculo(std::string FechaFabric): FechaFabric_(FechaFabric){};
		string FechaFabricacion() const { return FechaFabric_; }
		virtual void imprimirDatosVehiculo() = 0;
	private:
		std::string FechaFabric_;

};

class Turismo : public Vehiculo {
	
	public:
		Turismo(std::string FechaFabric, size_t maxP): Vehiculo(FechaFabric), maxP_(maxP) {};
		void imprimirDatosVehiculo () override{
			std::cout << "Tipo de vehiculo: Turismo." << std::endl;
			std::cout << "Fecha fabricacion: " << this->FechaFabricacion() << std::endl;
			std::cout << "Maximo de pasajeros: " << maxP_ << std::endl;
		}
	private:
		size_t maxP_;
};

class Camion : public Vehiculo {

	public:
		Camion(std::string FechaFabric, size_t MaxPeso): Vehiculo(FechaFabric), MaxPeso_(MaxPeso) {};
		void imprimirDatosVehiculo () override{
			std::cout << "Tipo de vehiculo: Camion." << std::endl;
			std::cout << "Fecha fabricacion: " << this->FechaFabricacion() << std::endl;
			std::cout << "Maximo de peso: " << maxPeso_ << std::endl;
		}

	private:
		size_t maxPeso_;
};

	//2
	
	void ClasificarVehiculos (std::vector<Vehiculo*> vectorVehiculo) {
		vector<Turismo*> vectorTurismo;
		vector<Camion*> vectorCamion;

		auto itTurismo = vectorTurismo.begin();
		auto itCamion = vectorCamion.begin();
		
		int i = 0;
		for (auto iterador = vectorVehiculo.begin(); iterador != vectorVehiculo.end(); iterador ++, i++) {
			if (Turismo *temp = dynamic_cast<Turismo*> vectorVehiculo[i]){
				vectorTurismo.insert(itTurismo, vectorVehiculo[i]);
				vectorVehiculo.erase[it];
				itTurismo ++;
			}else {
				vectorCamion.insert(itCamion, vectorCamion[i]);
				vectorVehiculo.erase[it];
				itCamion ++;
			}
		}
	}
