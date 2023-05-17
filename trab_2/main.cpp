/*
2° Trabalho - Lab de Prog
Algoritmos de forca bruta e kmp
João Marcos Brito Matias - 494952
*/

#include "algoritmos_busca.hpp"
#include "instancia_real.hpp"
#include "instancias.hpp"
#include "medir_tempo.hpp"
#include "auxiliares.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

int main(int narg, char *argv[]) {
	
  // Caso de tipo_instancia == A
  char letra_limite_aleatoria;
  int m;
  int n;
  int qtde_iteracoes;

  // Caso de tipo_instancia == R
  int x;
  int y;

	//Vetor dos padrões e dos textos
  const char *p;
  const char *t;

	//Vetores para marcar onde há ocorrência de P em T
  int *vetor_forca_bruta;
  int *vetor_kmp;

	//tempo total dos algoritmos
  double tempo_kmp = 0.0;
  double tempo_forca_bruta = 0.0;

	cout << "----TRABALHO 2----\n";
	cout << "----Lab de Prog----\n\n";

	
	//Caso de a instancia ser Aleatoria
  if (narg == 6 && argv[1][0] == 'A') {
		//preenchendo as variáveis
    letra_limite_aleatoria = argv[2][0];
    m = atoi(argv[3]);
    n = atoi(argv[4]);
    qtde_iteracoes = atoi(argv[5]);

		//Alocando os vetores
		try{
			vetor_forca_bruta = new int[n + 1];
		}
    catch(const bad_alloc &e){
			cerr << "Erro na alocação de memória do vetor de forca bruta\n";
			return 0;
		}
		try{
			vetor_kmp = new int[n + 1];	
		}
		catch(const bad_alloc &e){
			cerr << "Erro na alocação de memória do vetor kmp\n";
			return 0;
		}

		
    for (int i = 0; i < qtde_iteracoes; i++) {
			//Gerando os padrões e os textos aleatórios
      p = string_aleatoria(m, letra_limite_aleatoria);
      t = string_aleatoria(n, letra_limite_aleatoria);

			//medindo o tempo dos algoritmos
      tempo_forca_bruta += medir_tempo(forca_bruta, p, t, vetor_forca_bruta);
      tempo_kmp += medir_tempo(kmp, p, t, vetor_kmp);

			//Checando se os vetores que guardam as ocorrências são iguais	
      if (not vetores_iguais(vetor_forca_bruta, vetor_kmp)) {
        cerr << "Erro -> Os algoritmos de busca deram um resultado diferente\n";

				cout << "Vetor forca bruta: "; imprimir_vetor(vetor_forca_bruta);
				cout << "Vetor kmp: "; imprimir_vetor(vetor_kmp);
        return 0;
      }
			
    }
		
		cout << "Tipo de instancia escolhida: ";
		cout << "Aleatoria\n";
		cout << "Letra limite: " << letra_limite_aleatoria << "\n";
		cout << "Tamanho do padrão: " << m << "\n";
		cout << "Tamanho do texto: " << n << "\n";
		cout << "Quantidade de iterações: " << qtde_iteracoes << "\n\n";

		//Desalocando os vetores
	  delete[] vetor_forca_bruta;
	  delete[] vetor_kmp;
  }

	//Caso de instancias reais
  if (narg == 4 && argv[1][0] == 'R') {
		//preenchendo as variáveis
    x = atoi(argv[2]);
    y = atoi(argv[3]);
    t = Texto_Livros;
		int n = tamanho_string(t);

		//alocando o vetores
		try{
			vetor_forca_bruta = new int[n + 1];
		}
    catch(const bad_alloc &e){
			cerr << "Erro na alocação de memória do vetor de forca bruta\n";
			return 0;
		}
		try{
			vetor_kmp = new int[n + 1];	
		}
		catch(const bad_alloc &e){
			cerr << "Erro na alocação de memória do vetor kmp\n";
			return 0;
		}

		
    for (int i = x; i <= y; i++) {
			//pegando os padrões
      p = Padroes_Palavras[i];

			//medindo o tempo dos algoritmos
      tempo_forca_bruta += medir_tempo(forca_bruta, p, t, vetor_forca_bruta);
      tempo_kmp += medir_tempo(kmp, p, t, vetor_kmp);

			//checando se os vetores que guardam as ocorrência do padrão são iguais
      if (not vetores_iguais(vetor_forca_bruta, vetor_kmp)) {
        cerr << "Erro -> Os algoritmos de busca deram um resultado diferente\n";
        return 0;
      }
    }

		cout << "Tipo de instancia escolhida: ";
		cout << "Real\n";
		cout << "Posição do primeiro padrão: " << x << "\n";
		cout << "Posição do segundo padrão: " << y << "\n\n";

	//Desalocando os vetores
  delete[] vetor_forca_bruta;
  delete[] vetor_kmp;
  }  
	
  cout << "Tempo do algoritmo de forca bruta = " << tempo_forca_bruta << "\n";
  cout << "Tempo do algoritmo de kmp = " << tempo_kmp << "\n";

}