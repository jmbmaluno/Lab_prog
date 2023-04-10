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
void insertionsort(T*v, int p, int q){
	int chave;
	int j;

	for(int i = p+1; i <= q; ++i){
		chave = v[i];
		j = i-1;

		while(j >= p and v[j] > chave){
			trocar(v,j,j+1);
			--j;
		}

		v[j+1] = chave;
	
	}
}


template <typename T>
void quicksort(T* v, int i, int f){
	int q;
	if (i < f){

		if(f-i+1 <= 100){
			insertionsort(v,i,f);
		}

		else{
			q = particionar_lomuto(v,i,f);
								
			quicksort(v,i,q-1);
			quicksort(v,q+1,f);
		}
	}
}

template <typename T>
void combinar(T* v, int i, int p, int f){
	int n1 = p-i +1;
	int n2 = f - p;

	auto l = new T[n1+1];
	auto r = new T[n2+1];

	for(int i = 0; i < n1; i++){
		l[i] = v[p+i];
	}

	for(int j = 0; j < n2; j++){
		r[j] = v[p+j-1];
	}

	l[n1] = 1000000;
	r[n2] = 1000000;

	int q = 0;
	int j = 0;

	for(int k = i; k <= f; ++k){
		if (l[q] <= r[j]){
			v[k] = l[q++];
		}
		else{
			v[k] = r[j++];
		}
	} 
}


template <typename T>
void mergesort(T* v, int i, int f){
	if(i < f){
		int p = (f+i)/2 + 1;

		mergesort(v,i,p-1);
		mergesort(v,p,f);
		combinar(v,i,p,f);
	}
}

int main(){
	int v[] = {6,2,4,1};

	imprimir_vetor<int>(v,4);

	cout << "Depois de ordenar o vetor (particionamento de Lomuto):\n";

	//quicksort<int>(v,0,3);
	mergesort<int>(v,0,3);

	imprimir_vetor<int>(v,4);
	
}
