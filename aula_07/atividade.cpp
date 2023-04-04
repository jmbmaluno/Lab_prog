/*Implementar o Quicksort
 * Um baseado no particionamento de Lomuto 
 * Outro baseado no de Hoare (dois ponteiros)
 * */

#include <iostream>

using namespace std;

template <typename T>
void imprimir_vetor(T* v, int n){
	cout << "Vetor: ";
	for(int i = 0; i < n; ++i){
		cout << v[i] << " ";
	}

	cout << "\n";
}


template <typename T>
void trocar(T* v, int i, int j){
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}



template <typename T>
int particionar_lomuto(T* v, int i, int f){
	int j = i;

	for(int k = i+1; k <= f; k++){
		if (v[k] < v[i]){
			trocar(v,++j,k);
		}
	}

	trocar(v,j,i);
	
	return j;
}


template <typename T>
int particionar_hoare(T* v, int i, int f){
	int a = i;
	int b = f;

	while(a < b){

		while(a <= b and v[a] <= v[i]){++a;}

		while(v[b] > v[i]){++b;}

		if(a < b){trocar(v,a,b);}
	}
	
	//trocar(v,i,b);
	cout << "b: " << i << "\n";
	trocar(v,i,b);
	return b;
}

//Ordena um vetor de tipo T
//Recebe como parametro:
//Vetor de tipo T v
//Posição iniicial e final i e f
//tipo_do_particionamento:
//		se 0, então é o particionamento de Lomuto
//		se for qualquer outra coisa, então é Hoare
template <typename T>
void quicksort(T* v, int i, int f, int tipo_particionamento){
	int q;
	if (i < f){
		if (tipo_particionamento == 0) {q = particionar_lomuto(v,i,f);}

		else {q = particionar_hoare(v,i,f);}
							
		quicksort(v,i,q-1, tipo_particionamento);
		quicksort(v,q+1,f, tipo_particionamento);
	}
}


int main(){
	int v[] = {6,2,4,1};
	int v_copia[] =  {6,2,4,1};

	imprimir_vetor<int>(v,4);

	cout << "Depois de ordenar o vetor (particionamento de Lomuto):\n";

	quicksort<int>(v,0,3,0);

	imprimir_vetor<int>(v,4);
	
	cout << "Depois de ordenar o vetor (particionamento de Hoare):\n";

	quicksort<int>(v_copia,0,3,1);

	imprimir_vetor<int>(v_copia,4);
}
