#ifndef EIF201_ANALISISAVES_H
#define EIF201_ANALISISAVES_H


#include "NodoAve.h"
#include <string>

namespace EIF201 {
	class AnalisisAves {
	private:
		//Auxiliar para imprimirInverso con sangria opcional.
		void imprimirInversoAux(NodoAve* cab) const;

		//Auxiliar para aveMasPesada: rastrea el maximo encontrado.
		NodoAve* maxAux(NodoAve* cab, NodoAve* mejor) const;

	public:

		AnalisisAves() = default;

		int    contar(NodoAve* cab) const;
		double sumaPesos(NodoAve* cab) const;
		int   contarEspecie(NodoAve* cab, const std::string& especie) const;
		bool existeEspecie(NodoAve* cab, const std::string& especie) const;
		NodoAve* aveMasPesada(NodoAve* cab) const;
		void imprimirCronologico(NodoAve* cab) const;
		void imprimirInverso(NodoAve* cab) const;
	};
}// namespace EIF201
#endif // EIF201_ANALISISAVES_H

