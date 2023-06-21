#ifndef MEDIR_TEMPO_H
#define MEDIR_TEMPO_H
#include <chrono>
#include "compactador.hpp"

using namespace std;
using namespace chrono;

//Medindo o tempo de um método do Compactador
double medir_tempo(void (Compactador::*acao)(), Compactador c){
    auto inicio = steady_clock::now();

	(c.*acao)();

	auto fim = steady_clock::now();

	duration<double> d = fim - inicio;

	return d.count();
}   

#endif