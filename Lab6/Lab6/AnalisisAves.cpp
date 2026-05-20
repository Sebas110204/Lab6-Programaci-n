#include "AnalisisAves.h"
#include <iostream>

namespace EIF201 {

    // Cuenta el total de nodos de forma recursiva
    int AnalisisAves::contar(NodoAve* cab) const {
        if (cab == nullptr) return 0;
        return 1 + contar(cab->siguiente);
    }

    // Calcula recursivamente la sumatoria de todos los pesos
    double AnalisisAves::sumaPesos(NodoAve* cab) const {
        if (cab == nullptr) return 0.0;
        return cab->peso + sumaPesos(cab->siguiente);
    }

    // Cuenta cuántas aves pertenecen a una especie específica
    int AnalisisAves::contarEspecie(NodoAve* cab, const std::string& especie) const {
        if (cab == nullptr) return 0;
        int coincidencia = (cab->especie == especie) ? 1 : 0;
        return coincidencia + contarEspecie(cab->siguiente, especie);
    }

    // Evalúa si existe al menos un ave de la especie dada (salida temprana)
    bool AnalisisAves::existeEspecie(NodoAve* cab, const std::string& especie) const {
        if (cab == nullptr) return false;
        if (cab->especie == especie) return true;
        return existeEspecie(cab->siguiente, especie);
    }

    // Auxiliar privado: Compara secuencialmente el nodo actual con el candidato máximo
    NodoAve* AnalisisAves::maxAux(NodoAve* cab, NodoAve* mejor) const {
        if (cab == nullptr) return mejor;
        if (cab->peso > mejor->peso) {
            mejor = cab;
        }
        return maxAux(cab->siguiente, mejor);
    }

    // Método público para iniciar la búsqueda del ave con mayor peso
    NodoAve* AnalisisAves::aveMasPesada(NodoAve* cab) const {
        if (cab == nullptr) return nullptr;
        return maxAux(cab, cab);
    }

    // Imprime en orden cronológico natural (Primero procesa, luego recurre)
    void AnalisisAves::imprimirCronologico(NodoAve* cab) const {
        if (cab == nullptr) return;
        std::cout << "[Anillo: " << cab->anillo
            << " | Especie: " << cab->especie
            << " | Peso: " << cab->peso << "g"
            << " | Sexo: " << cab->sexo
            << " | Fecha: " << cab->fecha << "]\n";
        imprimirCronologico(cab->siguiente);
    }

    // Auxiliar privado: Imprime en orden inverso usando la pila de llamadas del procesador
    void AnalisisAves::imprimirInversoAux(NodoAve* cab) const {
        if (cab == nullptr) return;
        imprimirInversoAux(cab->siguiente); // Primero va hasta el final de la lista
        std::cout << "[Anillo: " << cab->anillo
            << " | Especie: " << cab->especie
            << " | Peso: " << cab->peso << "g"
            << " | Sexo: " << cab->sexo
            << " | Fecha: " << cab->fecha << "]\n"; // Imprime al regresar
    }

    // Método público wrapper que invoca al asistente de impresión inversa
    void AnalisisAves::imprimirInverso(NodoAve* cab) const {
        imprimirInversoAux(cab);
    }
}