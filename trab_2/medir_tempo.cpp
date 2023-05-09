#include "medir_tempo.hpp"
#include <chrono>

using namespace std;
using namespace chrono;

double medir_tempo(void (*busca_string) (const char *, const char *, int* ), const char * p, const char * t,  int* o){
	auto inicio = steady_clock::now();

	busca_string(p,t,o);

	auto fim = steady_clock::now();

	duration<double> d = fim - inicio;

	return d.count();
}