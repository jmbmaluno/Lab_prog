//Escreva em C++ um programa que leia números inteiros digitados pelo usuário, 
//armazenando-os em vetor alocado dinamicamente, 
//e que ao final imprima esses mesmos números em ordem crescente. 
//Um zero digitado pelo usuário indicará o fim da entrada (o zero não deve estar entre os números impressos ao final). 
//Não há limite conhecido para a quantidade dos números que serão digitados pelo usuário. 
//Sempre que o vetor no qual os números estiverem sendo armazenados ficar cheio, o programa deverá 
//(a) alocar outro vetor com o dobro do tamanho, 
//(b) copiar os números para o novo vetor e 
//(c) desalocar o vetor antigo. O primeiro vetor utilizado deve ter tamanho 1.


#include <iostream>
#include <new>
#include <sstream>
#include <string>

using namespace std;

struct ErrodeEntrada{const char* msg;};

int ler_int(const char * msg){
	cout << msg;
	
	int i;

	string linha; getline(cin,linha);

	istringstream origem(linha); origem >> i;

	if(origem.fail()) throw ErrodeEntrada{"ler_int: Entrada não é valida"};

	return i;
}

void copiar(int *v1, int *v2, int tam){
	int* aux_v2 = v2;

	for(int* aux = v1; aux != v1+tam; aux++){
		*aux_v2 = *aux;
		aux_v2++;
	}
}

void imprimir_vetor(int* v, int tam){

	cout << "Vetor: ";

	for(int* aux = v; aux != v+tam; aux++){
		cout << "[" << *aux << "] ";
	}

	cout << "\n";
}

//falta o tratamento de erros
int main(){

	int tam = 1;
	int i;
	int cont = 0;
	int* v1;

	try {
		v1 = new int[tam];
	}
	catch(const bad_alloc &e) {
		cout << "Erro na alocação de mémoria do vetor (" 
			<< e.what()
			<< ")\n";
		return -1;
	}

	while(i != 0){
		try{
			i = ler_int("Entre um valor: ");
		}
		catch (ErrodeEntrada &e){
			cout << "Erro -> " << e.msg << "\n";
			return -1;
		}

		if(i != 0){
			
			if(cont == tam){

				try{
					auto v2 = new int[tam*2];
					copiar(v1,v2,tam);
				
					delete[] v1;
					tam = tam*2;
					
					v1 = v2;
				}

				catch(const bad_alloc &e){
					cout << "Erro de alocacao de memoria do vetor(" 
						<< e.what()
						<<")\n";
					return -1;
				}
			}
		
			int j = cont-1;

			while(j >= 0 and v1[j] > i){
				int aux = v1[j];
				v1[j] = v1[j+1];
				v1[j+1] = aux;
				j--;
			}

			v1[j+1] = i;

			cont++;
		}
	}
	
	if(cont > 0) imprimir_vetor(v1,cont);

	delete[] v1;
}

