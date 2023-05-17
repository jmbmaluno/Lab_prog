#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <random>
using namespace std;

class MeuGerador{
    random_device disp_aleat;
	mt19937 gerador;
	
	public:

	MeuGerador();

	//int numero()
	int operator() (int i, int f);
};


bool vetores_iguais(int *v, int *u);

void imprimir_vetor(int* v);

#endif