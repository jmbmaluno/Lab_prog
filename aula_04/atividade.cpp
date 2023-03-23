//Escreva uma classe Fila que sirva como fila de double's
//Permitindo:
//(1) Enfilar, (2) Consultar o primeiro elemento
//(3) Desenfilar e (4) Consultar se vazia
//
//A Classe deve permitir uma quantidade indefinidamente grande de
//elementos
//
//Os elementos devem ser guardados num vetor alocado dinamicamente
//Deve ser substituido por uoutro com o dobro do tamahho caso fique cheio
//
//A classe deve construir um construtor para fazer a alocação inicial
//E um distrutor para fazer a desalocação final
//
//Por fim, escreva uma função main que sirva para o usuário constrolar a fila.


#include <iostream>
#include <new>

using namespace std;

struct FilaVazia{};

class Fila {
	double *v;
	int tam_v;
	int inicio;
	int fim;

	public:

	Fila() {
		tam_v = 2;
		v = new double[tam_v];
		inicio = 0;
		fim = 0;
	}

	~Fila(){
		delete[] v;
	}

	void enfilar(double x){
		//Aqui eu devo copiar o vetor para outro maior
		//if(fim == inicio-1 || (inicio == 0 and fim == tam_v-1)) throw FilaVazia{};

		if(fim == inicio-1 || (inicio == 0 && fim == tam_v-1)){
			double *aux = new double[tam_v*2];
			int i = 0;
			
			//coloando todos os elementos do antigo vetor para o novo
			while(inicio != fim){
				aux[i++] = v[inicio++];

				if(inicio == tam_v) inicio = 0;

			}
			
			//colocando os indexadores inicio e fim nos locais corretos do novo vetor
			inicio = 0; fim = tam_v-1;

			//atualizando o tamanho do vetor;
			tam_v = tam_v*2;

			//deletando a memoria reservada do antigo vetor e fazendo o ponteiro apontar para o novo
			delete[] v;
			v = aux;
		}

		v[fim++] = x;

		if (fim == tam_v) fim = 0;
	}

	double primeiro_elemento(){
		return v[inicio];
	}

	double desenfilar(){
		if(inicio == fim) throw FilaVazia{};

		double t = v[inicio++];

		if(inicio == tam_v) inicio = 0;

		return t;
	}

	bool vazia(){
		return (inicio == fim);
	}

	void imprimir_fila(){
		int i = inicio;
		cout << "Fila: "; 

		while(i != fim){
			cout << v[i++] << " ";

			if(i == tam_v) i = 0;
		}

		cout << "\n";

	}

};


int main(){
	try
	{
		Fila f;

		f.enfilar(1.0);
		f.enfilar(2.0);
		f.enfilar(3.0);

		f.imprimir_fila();

		f.desenfilar();
		f.desenfilar();
		f.desenfilar();
		f.desenfilar();
	}

	catch(FilaVazia &e){
		cout << "Erro ao desenfilar - Fila está vazia\n";
	}

	catch(const bad_alloc &e){
		cout << "Falta de mémoria ao alocar vetor (" << e.what() << ")\n";
	}
}
