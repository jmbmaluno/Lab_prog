#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

//Funções utéis para todos as funções de ordenação
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
void copiar(T* v, T* u, int n){
	for( int i = 0; i < n; ++i){
		u[i] = v[i];
	}	
}

//IMPLEMENTAÇÂO DO QUICKSORT - ALGORITMO QUADRÀTICO
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


//IMPLEMENTAÇÂO DO HEAPSORT E SUAS FUNÇÔES AUXILIARES
template <typename T>
void heapify(T *v, int n, int i){
	int maior = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if(l < n && v[l] > v[maior]) maior = l;

	if(r < n && v[l] > v[maior]) maior = r;

	if(maior != i){
		trocar(v, i, maior);
		heapify(v, n, maior);
	}
}

template <typename T>
void heapsort(T *v, int n){

	for (int i = n/2 -1; i >=0; i--) heapify(v,n,i);

	for (int i = n-1; i >= 0; i--){
		trocar(v,0,i);
		heapify(v,i,0);
	}
}

//IMPLEMENTAÇÂO DO MERGESORT E SUAS FUNÇÔES AUXILIARES
template <typename T>
void merge (T *v, int i, int p, int f){
	int n1 = p - i + 1;
	int n2 = f - p;

	int l[n1], m[n2];

	for (int x = 0; x < n1; x++) l[x] = v[i + x];
	for (int y = 0; y < n2; y++) m[y] = v[p + 1 + y];

	int x,y,k;

	x = 0;
	y = 0;
	k = i;

	while( x < n1 && y < n2){
		if (l[x] <= m[y]){
			v[k] = l[x];
			x++;
		}

		else {
			v[k] = m[y];
			y++;	
		}

		k++;
	}

	while(x < n1){
		v[k++] = l[x++];
	}

	while(y < n2){
		v[k++] = m[y++];
	}

}

template <typename T>
void mergesort_original(T*v, int i, int f){

	if (i < f){
		
		if (f-i+1 <= 100){
			insertionsort(v,i,f);
		}

		else{
		cout << "vim até aqui\n";
			int q = (i+f)/2;
			mergesort_original(v, i, q);
			mergesort_original(v, q+1, f);
			merge(v, i, q, f);
		}
	}
}

template <typename T>
void mergesort(T*v, int n){
	mergesort_original(v,0,n-1);
}

//IMPLEMENTAÇÂO DO QUICKSORT E SUAS FUNÇÔES AUXILIARES
int pivo(int i, int f){ return i;}

template <typename T>
int particionar_lomuto(T* v, int i, int f){
	int j = pivo(i,f);

	for(int k = i+1; k <= f; k++){
		if (v[k] < v[i]){
			trocar(v,++j,k);
		}
	}

	trocar(v,j,i);
	
	return j;
}

//quicksort modificado com insertionsort
template <typename T>
void quicksort_original(T* v, int i, int f){
	int q;
	if (i < f){

		if(f-i+1 <= 100){
			insertionsort(v,i,f);
		}

		else{
			q = particionar_lomuto(v,i,f);
								
			quicksort_original(v,i,q-1);
			quicksort_original(v,q+1,f);
		}
	}
}

template <typename T>
void quicksort(T* v, int n){
	quicksort_original(v,0,n-1);
}


//IMPLEMENTAÇÂO DO INTROSORT
int log(int n){
	int cont = 0;

	while((n >> 1) != 0){
		cont = cont + 1;
		n = (n >> 1);
	}

	return cont;
}

template <typename T>
void introsort_original(T* v, int i, int f, int limite){
	int q;
	if (i < f){
	
		if(f-i+1 <= 100){
			insertionsort(v,i,f);
		}

		else{
			if(limite  == 0){
				mergesort_original(v,i,f);
			}

			else{
				q = particionar_lomuto(v,i,f);
									
				introsort_original(v,i,q-1,limite-1);
				introsort_original(v,q+1,f,limite-1);
			}
		}
	}
}

template <typename T>
void introsort(T* v, int n){
	introsort_original(v,0,n-1, log(n) * 2);
}



//FUNCAO PARA RECEBER UMA ORDENAÇÂO E MEDIR O TEMPO DElA
template <typename T>
double medir_tempo(void (*ordenacao) (T*, int), T* v, T* aux, int n){
	
	copiar(v,aux,n);

	auto inicio = steady_clock::now();

	ordenacao(aux,n);

	auto fim = steady_clock::now();

	duration<double> d = fim - inicio;

	return d.count();
}

//Gerando instancia de pior caso para Pivo
template <typename T>
bool gerar_pior_caso (T *v, int n){
	
}

//MAIN DO PROGRAMA
int main(){
	int v[] = {1,2,3,4};
	int *u;
	u = new int[4];
	
	cout << "Quicksort: ";
	cout << medir_tempo(quicksort,v,u,4) << " segundos \n";	

	cout << "heapsort: ";
	cout << medir_tempo(heapsort,v,u,4) << " segundos \n";	
	
	cout << "introsort: ";
	cout << medir_tempo(introsort,v,u,4) << "segundos \n";

	delete[] u;
}
