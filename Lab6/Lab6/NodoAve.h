#ifndef EIF201_NODOAVE_H
#define EIF201_NODOAVE_H

#include <string>

namespace EIF201 {

	struct NodoAve {
		std::string anillo;
		std::string especie;
		double        peso;
		char          sexo;
		std::string  fecha;
		NodoAve* siguiente;

		NodoAve(const std::string& anillo_,
			const std::string& especie_,
			double peso_,
			char sexo_,
			const std::string& fecha_)
			:anillo(anillo_), especie(especie_), peso(peso_),
			sexo(sexo_), fecha(fecha_), siguiente(nullptr) {}

	};

}// namespace EIF201

#endif // EIF201_NODOAVE_H
