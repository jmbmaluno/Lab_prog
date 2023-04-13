#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

class MeuGerador{
	random_device disp_aleat;
	mt19937 gerador;

	public:

	MeuGerador(): gerador{disp_aleat()}{}

	int operator() (int i, int f) { 
		uniform_int_distribution distr(i,f); 
		return distr(gerador);
	}

};

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

	T *l, *m;
	
	l = new T[n1];
	m = new T[n2];

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
	
	delete[] l;
	delete[] m;
}

template <typename T>
void mergesort_original(T*v, int i, int f){

	if (i < f){
		int q = (i+f)/2;
		mergesort_original(v, i, q);
		mergesort_original(v, q+1, f);
		merge(v, i, q, f);
	}
}

template <typename T>
void mergesort(T*v, int n){
	mergesort_original(v,0,n-1);
}

//IMPLEMENTAÇÂO DO QUICKSORT E SUAS FUNÇÔES AUXILIARES
int pivo(int i, int f ){return i + f*0;}

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

template <typename T>
int particionar_lomuto_aleatorio(T* v, int i, int f, MeuGerador &g){
	int j = g(i,f);

	for(int k = i+1; k <= f; k++){
		if (v[k] < v[i]){
			trocar(v,++j,k);
		}
	}

	trocar(v,j,i);
	
	return j;
}

//QUICKSORT COM PONTO FIXO E ALEATORIO
template <typename T>
void quicksort_original_fixo(T* v, int i, int f){
	int q;
	if (i < f){
		q = particionar_lomuto(v,i,f);
							
		quicksort_original_fixo(v,i,q-1);
		quicksort_original_fixo(v,q+1,f);
		
	}
}

template <typename T>
void quicksort_fixo(T* v, int n){
	quicksort_original_fixo(v,0,n-1);
}

template <typename T>
void quicksort_original_aleatorio(T* v, int i, int f, MeuGerador &g){
	int q;
	if (i < f){
		q = particionar_lomuto_aleatorio(v,i,f,g);
							
		quicksort_original_aleatorio(v,i,q-1,g);
		quicksort_original_aleatorio(v,q+1,f,g);
	}
}

template <typename T>
void quicksort_aleatorio(T* v, int n, MeuGerador &g){
	quicksort_original_aleatorio(v,0,n-1,g);
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

template <typename T>
void introsort(T* v, int n){
	introsort_original(v,0,n-1, log(n) * 2);
}

template <typename T>
void introsort_original_insertion(T* v, int i, int f, int limite){
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
void introsort_insertion(T* v, int n){
	introsort_original_insertion(v,0,n-1, log(n) * 2);
}
//FUNCAO PARA RECEBER UMA ORDENAÇÂO E MEDIR O TEMPO DElA
//Vou ter que medir o tempo do quicksort aleatorio sem ser nessa função
//ele não se encaixa no ponteiro ordenacao
template <typename T>
double medir_tempo(void (*ordenacao) (T*, int), T* aux, int n){
	
	auto inicio = steady_clock::now();

	ordenacao(aux,n);

	auto fim = steady_clock::now();

	duration<double> d = fim - inicio;

	return d.count();
}

//GERANDO INSTANCIAS 

template <typename T>
void pior_caso(T* v, int i, int f){
	if(i < f){
		int k = pivo(i,f);

		trocar(v,i,k);

		pior_caso(v,i+1,f);
	}
	
}

template <typename T>
bool gerar_pior_caso (T *v, int n){
	T* aux;
	aux = new T[n];
	
	for(int i = 0; i < n; i++) aux[i] = i;

	pior_caso(aux,0,n);
	
	for(int i = 0; i < n; i++){
		v[aux[i]] = i+1;
	}

	delete[] aux;	

	return true;	
}

void instancia_pior_caso(int *v, int n){
	gerar_pior_caso<int>(v,n);
}

void instancia_aleatoria(int *v, int n, MeuGerador &g){
	for(int i = 0; i < n; i++) v[i] = g(0,n);
}

void instancia_ordem_crescente(int *v, int n){
	for(int i = 0; i < n; i++) v[i] = i;
}

void instancia_ordem_decrescente(int *v, int n){
	for(int i = 0; i < n; i++) v[i] = n-i;
}

//MAIN DO PROGRAMA
int main(int narg, char* arg[]){
	
	char tipo_instancia = arg[narg-3][0];
	int n = atoi(arg[narg-2]);
	int numero_instancias = atoi(arg[narg-1]);

	double tempo_heap = 0.0;
	double tempo_quick_fixo = 0.0;
	double tempo_quick_aleatorio = 0.0;
	double tempo_introsort = 0.0;
	double tempo_introsort_insertion = 0.0;
	
	int *v, *aux;
	v = new int[n];
	aux = new int[n];
	MeuGerador g;
	
	for(int i = 0; i < numero_instancias; ++i){
		if(tipo_instancia == 'A') instancia_aleatoria(v,n,g);
		if(tipo_instancia == 'C') instancia_ordem_crescente(v,n);
		if(tipo_instancia == 'D') instancia_ordem_decrescente(v,n);
		if(tipo_instancia == 'P') instancia_pior_caso(v,n);
		
		copiar(v,aux,n);
		tempo_heap += medir_tempo(heapsort,aux,n);

		copiar(v,aux,n);
		tempo_quick_fixo += medir_tempo(quicksort_fixo,aux,n);
		

		copiar(v,aux,n);
		tempo_introsort += medir_tempo(introsort,aux,n);

		copiar(v,aux,n);
		tempo_introsort_insertion += medir_tempo(introsort_insertion, aux, n);

		copiar(v,aux,n);
		auto inicio = steady_clock::now();
		quicksort_aleatorio(aux,n,g);
		auto fim = steady_clock::now();

		duration<double> d = fim-inicio;

		tempo_quick_aleatorio += d.count();	
	}

	
	cout << "MEDINDO TEMPO DAS ORDENAÇÕES";
	cout << "- Tipo de instancia: " << tipo_instancia << "\n";
	cout << "- Tamanho do vetor: " << n << "\n";
	cout << "- Número de instancias: " << numero_instancias << "\n\n";

	cout << "--> Tempos dos algoritmos \n";
	cout << "Heaposort: " << tempo_heap << "\n";
	cout << "Quicksort fixo: " << tempo_quick_fixo << "\n";
	cout << "Quicksort aleatorio: " << tempo_quick_aleatorio << "\n";
	cout << "Introsort sem insertion: " << tempo_introsort << "\n";
	cout << "Introsort com insertion: " << tempo_introsort_insertion << "\n";

	delete[] v;
	delete[] aux;
}
