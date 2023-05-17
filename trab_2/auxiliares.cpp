#include "auxiliares.hpp"
#include <iostream>

using namespace std;

//funções do gerador de inteiros pseudo-aleatorios
MeuGerador::MeuGerador():gerador{disp_aleat()}{};

//devolve um valo inteiro aleatorio entre i e f
int MeuGerador::operator() (int i, int f){
    uniform_int_distribution<int> distr(i,f);
    return distr(gerador); 
};

//checar se dois vetores são iguais
bool vetores_iguais(int *v, int *u) {
  int cont = 0;
  while (v[cont] != -1 and u[cont] != -1) {
    if (v[cont] != u[cont])
      return false;
    cont++;
  }

  if (v[cont] != u[cont])
    return false;

  return true;
}


void imprimir_vetor(int* v){
	int i = 0;

	while(v[i] != -1){
		cout << v[i++] << " ";
	}

	cout << "\n";
}