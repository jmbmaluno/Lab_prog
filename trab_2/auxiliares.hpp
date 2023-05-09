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

#endif