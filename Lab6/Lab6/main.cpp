#include <iostream>
#include <filesystem>
#include <fstream>
#include "NodoAve.h"
#include "Bitacora.h"
#include "AnalisisAves.h"

using namespace EIF201;

int main() {
    // Generar de forma segura la carpeta local donde se guardará el archivo
    std::filesystem::create_directory("datos");
    std::string ruta = "datos/anillamientos.txt";

    Bitacora bitacora(ruta);
    AnalisisAves analizador;

    std::cout << "========== PRUEBA 1: REGISTRO DE AVES ==========\n";
    // Insertamos aves utilizando el método de escritura de la bitácora
    bitacora.registrarAve("A-102", "Garza Tigre", 380.5, 'M', "2026-05-18");
    bitacora.registrarAve("A-103", "Colibri Rabitiche", 4.2, 'H', "2026-05-19");
    bitacora.registrarAve("A-104", "Garza Tigre", 415.0, 'X', "2026-05-19");
    bitacora.registrarAve("A-105", "Lapa Roja", 920.8, 'H', "2026-05-20");

    // Inyectamos líneas dañadas a propósito para forzar los descartes en la carga válida
    std::ofstream corruptor(ruta, std::ios::app);
    corruptor << ";Garza Invalida;;M;2026-05-20\n";     // Falta anillo y peso
    corruptor << "A-999;Lapa Azul;-10.0;Z;2026-05-20\n"; // Peso negativo y sexo erróneo
    corruptor.close();
    std::cout << "Registros creados en '" << ruta << "'.\n\n";

    std::cout << "========== PRUEBA 2: PROBAR MÉTODOS DE CARGA ==========\n";
    NodoAve* listaAves = nullptr;

    // 2.1 Probamos tu método modificado (cargarAve)
    std::cout << "Probando cargarAve()...\n";
    int cargadasAve = bitacora.cargarAve(listaAves);
    std::cout << "Aves cargadas con cargarAve(): " << cargadasAve << "\n";
    Bitacora::liberarLista(listaAves); // Limpiamos para la siguiente prueba
    listaAves = nullptr;

    // 2.2 Probamos tu nuevo método (cargarTodas)
    std::cout << "\nProbando cargarTodas()...\n";
    int cargadasTodas = bitacora.cargarTodas(listaAves);
    std::cout << "Aves cargadas con cargarTodas(): " << cargadasTodas << "\n";
    Bitacora::liberarLista(listaAves); // Limpiamos para la prueba definitiva
    listaAves = nullptr;

    // 2.3 Carga definitiva usando el filtro estricto (cargarAvesValidas)
    std::cout << "\nProbando cargarAvesValidas()...\n";
    bitacora.cargarAvesValidas(listaAves);
    std::cout << "-> Registros Válidos en memoria: " << bitacora.getValidas() << "\n";
    std::cout << "-> Registros Descartados del archivo: " << bitacora.getDescartadas() << "\n\n";

    std::cout << "========== PRUEBA 3: MÉTRICAS RECURSIVAS CONST ==========\n";
    std::cout << "Cantidad total de aves (recursivo): " << analizador.contar(listaAves) << "\n";
    std::cout << "Peso acumulado de la lista: " << analizador.sumaPesos(listaAves) << " g\n";

    std::string especie = "Garza Tigre";
    std::cout << "Frecuencia de '" << especie << "': " << analizador.contarEspecie(listaAves, especie) << "\n";
    std::cout << "¿Existe la 'Lapa Roja'?: " << (analizador.existeEspecie(listaAves, "Lapa Roja") ? "Sí" : "No") << "\n";

    NodoAve* masPesada = analizador.aveMasPesada(listaAves);
    if (masPesada != nullptr) {
        std::cout << "Ave más pesada: " << masPesada->especie << " (" << masPesada->peso << "g)\n\n";
    }

    std::cout << "========== PRUEBA 4: IMPRESIÓN CRONOLÓGICA RECURSIVA ==========\n";
    analizador.imprimirCronologico(listaAves);

    std::cout << "\n========== PRUEBA 5: IMPRESIÓN INVERSA RECURSIVA ==========\n";
    analizador.imprimirInverso(listaAves);

    std::cout << "\n========== LIMPIEZA OBLIGATORIA DE MEMORIA ==========\n";
    // Llamada al método estático según tu nueva firma (paso por valor)
    Bitacora::liberarLista(listaAves);

    // Como tu función ya no usa '*&', ponemos el puntero local a nullptr manualmente por seguridad
    listaAves = nullptr;

    std::cout << "Memoria liberada y puntero reseteado. Programa finalizado con éxito.\n";

    return 0;
}