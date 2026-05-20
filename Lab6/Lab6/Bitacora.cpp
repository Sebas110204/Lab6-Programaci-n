#include "Bitacora.h"
#include <fstream>
#include <sstream>

namespace EIF201 {

    // Constructor: Inicializa la ruta y limpia los contadores de la bitácora
    Bitacora::Bitacora(const std::string& ruta) : ruta_(ruta), validas_(0), descartadas_(0) {}

    // Escribe un ave al final del archivo de texto (modo append)
    bool Bitacora::registrarAve(const std::string& anillo, const std::string& especie, double peso, char sexo, const std::string& fecha) {
        std::ofstream archivo(ruta_, std::ios::app);
        if (!archivo.is_open()) return false;

        archivo << anillo << ";" << especie << ";" << peso << ";" << sexo << ";" << fecha << "\n";
        archivo.close();
        return true;
    }

    // Carga todas las líneas asumiendo formato correcto (Método: cargarAve)
    int Bitacora::cargarAve(NodoAve*& cabeza) {
        cabeza = nullptr;
        std::ifstream archivo(ruta_);
        if (!archivo.is_open()) return 0;

        std::string linea;
        int contador = 0;
        NodoAve* cola = nullptr;

        while (std::getline(archivo, linea)) {
            if (linea.empty()) continue;

            std::stringstream ss(linea);
            std::string anillo, especie, pesoStr, sexoStr, fecha;

            if (std::getline(ss, anillo, ';') &&
                std::getline(ss, especie, ';') &&
                std::getline(ss, pesoStr, ';') &&
                std::getline(ss, sexoStr, ';') &&
                std::getline(ss, fecha)) {

                double peso = 0.0;
                try { peso = std::stod(pesoStr); }
                catch (...) {}
                char sexo = sexoStr.empty() ? 'X' : sexoStr[0];

                // Usa tu constructor explícito de 5 parámetros
                NodoAve* nuevo = new NodoAve(anillo, especie, peso, sexo, fecha);

                if (cabeza == nullptr) {
                    cabeza = nuevo;
                    cola = nuevo;
                }
                else {
                    cola->siguiente = nuevo;
                    cola = nuevo;
                }
                contador++;
            }
        }
        archivo.close();
        return contador;
    }

    // Nuevo método añadido en tu .h (cargarTodas)
    // Implementamos una lectura secuencial completa estándar
    int Bitacora::cargarTodas(NodoAve*& cabeza) {
        return cargarAve(cabeza);
    }

    // Carga defensiva: Filtra y descarta registros corruptos actualizando contadores
    int Bitacora::cargarAvesValidas(NodoAve*& cabeza) {
        cabeza = nullptr;
        std::ifstream archivo(ruta_);
        if (!archivo.is_open()) return 0;

        std::string linea;
        NodoAve* cola = nullptr;

        while (std::getline(archivo, linea)) {
            if (linea.empty()) {
                descartadas_++;
                continue;
            }

            std::stringstream ss(linea);
            std::string anillo, especie, pesoStr, sexoStr, fecha;

            bool extraido = std::getline(ss, anillo, ';') &&
                std::getline(ss, especie, ';') &&
                std::getline(ss, pesoStr, ';') &&
                std::getline(ss, sexoStr, ';') &&
                std::getline(ss, fecha);

            if (!extraido || anillo.empty() || especie.empty() || pesoStr.empty() || sexoStr.empty() || fecha.empty()) {
                descartadas_++;
                continue;
            }

            // Validación de peso decimal estrictamente positivo
            double peso = -1.0;
            try {
                size_t pos;
                peso = std::stod(pesoStr, &pos);
                if (pos != pesoStr.length() || peso <= 0) {
                    descartadas_++;
                    continue;
                }
            }
            catch (...) {
                descartadas_++;
                continue;
            }

            // Validación estricta del sexo
            if (sexoStr.length() != 1) {
                descartadas_++;
                continue;
            }
            char sexo = sexoStr[0];
            if (sexo != 'M' && sexo != 'H' && sexo != 'X') {
                descartadas_++;
                continue;
            }

            // Invocación a tu constructor explícito si pasó las pruebas
            NodoAve* nuevo = new NodoAve(anillo, especie, peso, sexo, fecha);

            if (cabeza == nullptr) {
                cabeza = nuevo;
                cola = nuevo;
            }
            else {
                cola->siguiente = nuevo;
                cola = nuevo;
            }
            validas_++;
        }
        archivo.close();
        return validas_;
    }

    int Bitacora::getValidas() const {
        return validas_;
    }

    int Bitacora::getDescartadas() const {
        return descartadas_;
    }

    // Función estática utilitaria ajustada a tu firma exacta (Puntero por valor: NodoAve* cabeza)
    void Bitacora::liberarLista(NodoAve* cabeza) {
        NodoAve* actual = cabeza;
        while (actual != nullptr) {
            NodoAve* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
}